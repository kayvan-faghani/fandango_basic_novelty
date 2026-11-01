#include <filesystem>
#include <iostream>
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/PassManager.h"
#include "llvm/IR/DebugInfo.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Transforms/Utils/ModuleUtils.h"

#include "Runtime.h"
#include "InstrumentationHelpers.h"

using namespace llvm;

namespace {

struct InstrumentationPass : public PassInfoMixin<InstrumentationPass> {
private:
  Runtime *m_rt;
  Module* m_M;
  uint32_t m_cur_bbid = 0;
  enum InstrumentationType {BBId};

public:
  void instrumentBasicBlockHits(Instruction *before_where, ConstantInt* bbid, GlobalVariable* module_bb_hitcount_array) {
    IRBuilder<> builder(before_where);
    Type *arrayElementType = Type::getInt64Ty(before_where->getContext());
    Value *gep = builder.CreateGEP(arrayElementType, module_bb_hitcount_array, {bbid});
    LoadInst *oldCtr = builder.CreateLoad(arrayElementType, gep);
    Value *newCtr = builder.CreateAdd(oldCtr, ConstantInt::get(arrayElementType, 1));
    builder.CreateStore(newCtr, gep);
  }

  ConstantInt* set_metadata(Instruction* instr, InstrumentationType it) {
    LLVMContext& ctx = m_M->getContext();
    uint32_t id;
    StringRef kind;

    switch (it) {
      case BBId:
        kind = "bf_bbid";
        id = m_cur_bbid++;
        break;
      default:
        std::cout << "not implemented set_metadata" << std::endl;
        break;
    }

    ConstantInt* _id = ConstantInt::get(IntegerType::getInt32Ty(ctx), id); 
    auto meta_id = MDNode::get(ctx, ConstantAsMetadata::get(_id));
    instr->setMetadata(kind, meta_id);
    return _id;
  }

void set_module_identifier_metadata(Instruction* instr) {
    if (!instr) return;
    StringRef id = "module_id";

    BasicBlock* bb = instr->getParent();
    Function* f = bb->getParent();
    Module* m = f->getParent();
    std::string moduleName = std::filesystem::canonical(m->getSourceFileName()).string();
    StringRef value = moduleName;

    llvm::LLVMContext& context = instr->getContext();
    llvm::MDString* mdValue = llvm::MDString::get(context, value);
    llvm::MDNode* mdNode = llvm::MDNode::get(context, mdValue);
    instr->setMetadata(id, mdNode);
}


  bool isStaticallyLinkedLibCFunction(Function *f) {
    // Must match functions implemented in llvm/mylibc/mylibc.c
    std::set<std::string> functions = {
        //"memcmp", "strcmp", "strncmp", "strchr", "memchr", "strcasecmp", "strncasecmp"
    };
    return (functions.find(f->getName().str()) != functions.end());
}

void copyMetadata(llvm::Instruction* src, llvm::Instruction* dest) {
  llvm::SmallVector<std::pair<unsigned, llvm::MDNode*>, 8> MDs;
  src->getAllMetadataOtherThanDebugLoc(MDs);
  for (const auto& metadataPair : MDs) {
      unsigned kind = metadataPair.first;
      llvm::MDNode* metadataNode = metadataPair.second;
      dest->setMetadata(kind, metadataNode);
  }
}

GlobalVariable* addGlobalBBHitCountArray(Module &M, uint32_t bb_count) {
  Type *Int64Ty = Type::getInt64Ty(M.getContext());
  ArrayType *ArrayTy = ArrayType::get(Int64Ty, bb_count);

  Constant *zero = Constant::getNullValue(Int64Ty);
  Constant *arrayInitializer = ConstantArray::get(ArrayTy, std::vector<Constant*>(bb_count, zero));

  GlobalVariable *globalVar = new GlobalVariable(
      M,
      ArrayTy,
      false,
      GlobalValue::ExternalLinkage,
      arrayInitializer,
      "bbid_hits_" + std::filesystem::canonical(M.getSourceFileName()).string()  // Name of the global variable
  );

  // Optionally, set the alignment (e.g., to 8 bytes for uint64_t)
  globalVar->setAlignment(Align(8));

  errs() << "Added global bbid hit table: " << *globalVar << "\n";

  return globalVar;
}


  PreservedAnalyses run(Module &M, ModuleAnalysisManager &MAM) {
    m_rt = new Runtime(M);
    m_M = &M;

    // Replacement of libc functions with instrumented mylibc functions. (currently unused)
    for (auto &F : M) {
      if (isStaticallyLinkedLibCFunction(&F)) {
        auto name = F.getName();
        F.setName("__my_" + name);
      }
    }

    unsigned functionCount = M.size();
    unsigned ctr = 0;

    uint32_t count_bb_in_module = 0;
    for (auto &F : M) {
      count_bb_in_module += F.size();
    }
    GlobalVariable* module_bb_hitcount_array = addGlobalBBHitCountArray(M, count_bb_in_module);

    std::vector<Type*> initArgTypes = {
      PointerType::get(Type::getInt8Ty(M.getContext()), 0), // for module identifier
      PointerType::get(Type::getInt64Ty(M.getContext()), 0), // type for module_bb_hitcount_array (pointer to uint64_t)
      Type::getInt32Ty(M.getContext()) // type for count_bb_in_module (uint32_t)
    };

    // Put the "moduleIdentifier" string in the module, without IRBuilder (which would attach it to a BB).
    std::string moduleIdentifier = M.getSourceFileName();
    std::filesystem::path absModuleIdentifier = std::filesystem::canonical(moduleIdentifier); // absolute + removes dots
    llvm::errs() << "DBG moduleIdentifier: " << absModuleIdentifier << "\n";
    Constant *globalStringConstant = ConstantDataArray::getString(M.getContext(), absModuleIdentifier.string(), true);
    GlobalVariable *moduleIdentifierPtr = new GlobalVariable(
        M,
        globalStringConstant->getType(),
        true,
        GlobalValue::ExternalLinkage,
        globalStringConstant,
        "module_identifier_" + absModuleIdentifier.string() // must be unique across modules
    );

    // initArgs: the arguments to pass to _runtime_initialize
    std::vector<Value*> initArgs = {
        moduleIdentifierPtr, 
        module_bb_hitcount_array, // the global variable (pointer to uint64_t)
        ConstantInt::get(Type::getInt32Ty(M.getContext()), count_bb_in_module)
    };

    getOrCreateSanitizerCtorAndInitFunctions(
      M,
      "__runtime_ctor",
      "_runtime_initialize",
      initArgTypes,
      initArgs,
      // From https://github.com/llvm-mirror/llvm/blob/master/lib/Transforms/Instrumentation/MemorySanitizer.cpp#L597
      // This callback is invoked when the functions are created the first
      // time. Hook them into the global ctors list in that case:
      [&](Function *Ctor, FunctionCallee) {
          appendToGlobalCtors(M, Ctor, 0);
      }
    );

    for (auto &F : M) {
      if (F.getName() == "__runtime_ctor"){
        // Skip the constructor function
        // (a) It's added by getOrCreateSanitizerCtorAndInitFunctions, i.e., after `count_bb_in_module` was
        //     calculated, for the bb hit count array, so it would be an OOB write if we instrumented it.
        // (b) It is not interesting anyway, as we added it.
        continue;
      }

      errs() << "Processing function " << F.getName() << " (" << ++ctr << "/" << functionCount << ")\n";
      errs() << "[*] Instrumenting\n";
      for (auto &BB : F) {
        // BBID instrumentation
        Instruction* instr = &(*(BB.getFirstInsertionPt()));
        set_module_identifier_metadata(instr);
        set_metadata(instr, BBId);
        uint32_t bbid = get_bbid_from_bb(BB);
        instrumentBasicBlockHits(instr, get_bbid_constantint(instr), module_bb_hitcount_array);

        // "mem" instrumentation
        for (Instruction& I: BB) {
          // CallBase handles both InvokeInst, CallInst.
          if (auto *CI = dyn_cast<CallBase>(&I)) {
            llvm::Function *calledFunction = CI->getCalledFunction();
            if (calledFunction && !calledFunction->isIntrinsic()) {
              if (calledFunction->hasName()) {
                if (calledFunction->getName() == "malloc") {
                  IRBuilder<> builder(CI->getNextNode());
                  auto bytes = builder.CreateTrunc(CI->getArgOperand(0), Type::getInt32Ty(M.getContext()));
                  builder.CreateCall(m_rt->_track_heap_alloc, {bytes});
                }
                else if (calledFunction->getName() == "calloc") {
                  IRBuilder<> builder(CI->getNextNode());
                  auto bytes = builder.CreateTrunc(builder.CreateMul(CI->getArgOperand(0), CI->getArgOperand(1)),  Type::getInt32Ty(M.getContext()));
                  builder.CreateCall(m_rt->_track_heap_alloc, {bytes});
                }
              }
            }
          }
        }

        // Instrumentation is inserted at the first insertion point,
        // so meta data is now attached to the second instruction.
        // We fix this here, so the analysis pass can find the meta data.
        Instruction* new_first_instr = &(*(BB.getFirstInsertionPt()));
        copyMetadata(instr, new_first_instr);
      }
    }

    return PreservedAnalyses::none();
  }
};

} // end anonymous namespace

extern "C" ::llvm::PassPluginLibraryInfo LLVM_ATTRIBUTE_WEAK
llvmGetPassPluginInfo() {
  return {LLVM_PLUGIN_API_VERSION, "InstrumentationPass", "v0.1",
          [](PassBuilder &PB) {
            // registerOptimizerLastEPCallback runs the instrumentation pass last in the pipeline, so
            // no new (uninstrumented) BBs are added / meta data is not changed, etc.
            #if LLVM_VERSION_MAJOR < 12 // llvm-11 is broken
            PB.registerOptimizerLastEPCallback([](ModulePassManager &MPM) {  // for llvm-11
            #elif LLVM_VERSION_MAJOR <= 19
            PB.registerOptimizerLastEPCallback ([](ModulePassManager &MPM, OptimizationLevel Level) { // for llvm-14
            #else
            PB.registerOptimizerLastEPCallback ([](ModulePassManager &MPM, OptimizationLevel Level, ThinOrFullLTOPhase Phase) { // for llvm-20
            #endif
              MPM.addPass(InstrumentationPass());
            });

            // Named registration for explicit invocation
            // i.e., loaded via opt

            // PB.registerPipelineParsingCallback(
            //   [](StringRef Name, ModulePassManager &MPM,
            //       ArrayRef<PassBuilder::PipelineElement>) {
            //     if (Name == "instrumentation-pass") {
            //       MPM.addPass(InstrumentationPass());
            //       return true;
            //     }
            //     return false;
            // });

          }};
}