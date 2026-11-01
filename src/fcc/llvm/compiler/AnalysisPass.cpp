#include <iostream>
#include <fstream>
#include <iomanip>
#include <filesystem>

#include "llvm/IR/Module.h"
#include "llvm/IR/PassManager.h"
#include "llvm/IR/DebugInfoMetadata.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"
#include "llvm/Support/Path.h"
#include "llvm/Support/FileSystem.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Transforms/Utils/ModuleUtils.h"

#include "InstrumentationHelpers.h"

// This pass runs on the wllvm-generated .bc of the binary.

#include "json.hpp"
using njson = nlohmann::json;

using namespace llvm;

namespace {

struct AnalysisPass : public PassInfoMixin<AnalysisPass> {
private:
  Module* m_M;
  uint32_t m_cur_bbid = 0;
  uint32_t m_cur_brid = 0;
  njson j_bb_to_dbg;
  enum InstrumentationType {BBId, BrId};

public:
  void serialize_json(njson& j, std::string output_file_name)  {
    errs() << "Serializing json to " << output_file_name << "\n";
    std::ofstream o(output_file_name);
    o << std::setw(4) << j << std::endl;
  }

  PreservedAnalyses run(Module &M, ModuleAnalysisManager &MAM) {
    m_M = &M;

    std::string moduleName = M.getModuleIdentifier();
    errs() << "module identifier: " << moduleName << "\n";
    std::filesystem::path filePath(moduleName);
    std::filesystem::path dirPath = filePath.parent_path(); // output directory
    std::map<llvm::Function*, std::string> f_to_name; 
    uint32_t goal = 0;
    unsigned functionCount = M.size();
    njson cfg;

    for (auto &F : M) {
      if (F.hasName() && F.getName().find("__runtime_ctor") == 0) { // startswith, e.g. __runtime_ctor.2
        // Skip the constructor functions, see InstrumentationPass.cpp for details.
        errs() << "Skipping __runtime_ctor\n";
        continue;
      }

      std::string module_of_function;
      for (auto &BB : F) {
        std::string module_id = get_module_id_from_bb(BB);
        module_of_function = module_id;
        std::string bbid = std::to_string(get_bbid_from_bb(BB));
        std::string fname;
        if (F.hasName()) fname = F.getName().str();
        else assert(false);

        // *** Get debug information ***
        for (Instruction& I: BB) {
          if (const DILocation *Loc = I.getDebugLoc()) {
            unsigned Line = Loc->getLine();
            unsigned Col = Loc->getColumn();
            StringRef FileName = Loc->getFilename();
            StringRef DirName = Loc->getDirectory();
            SmallString<256> AbsPath;
            if (llvm::sys::path::is_absolute(FileName)) {
                AbsPath = FileName;
            } else {
                AbsPath = DirName;
                llvm::sys::path::append(AbsPath, FileName);
            }        
            // Normalize the path
            llvm::sys::fs::make_absolute(AbsPath);
            llvm::sys::path::remove_dots(AbsPath, /*remove_dot_dot=*/true);
            std::string s;
            llvm::raw_string_ostream llvm_s(s);
            llvm_s << AbsPath << ":" << Line << ":" << Col;
            j_bb_to_dbg[module_id][bbid].push_back(llvm_s.str());
          }
        }

        // *** Get control-flow graph ***
        cfg[module_of_function][fname][bbid]["successors"] = njson::array();
        cfg[module_of_function][fname][bbid]["callees"] = njson::array();

        Instruction* terminator = BB.getTerminator();
        // All terminator instructions:
        // ret, br, switch, indirectbr, invoke, callbr, resume, catchswitch, catchret, cleanupret, unreachable
        if (auto *BI = dyn_cast<BranchInst>(terminator)) {
          for (int i = 0; i < BI->getNumSuccessors(); i++) {
            BasicBlock& _BB = *(BI->getSuccessor(i));
            uint32_t successor_bbid = get_bbid_from_bb(_BB);
            std::string successor_module = get_module_id_from_bb(_BB);
            cfg[module_of_function][fname][bbid]["successors"].push_back({successor_module, std::to_string(successor_bbid)});
          }
        } else if (auto *SI = dyn_cast<SwitchInst>(terminator)) {
          BasicBlock& _BB = *(SI->getDefaultDest());
          uint32_t default_bbid = get_bbid_from_bb(_BB);
          std::string default_module = get_module_id_from_bb(_BB);
          cfg[module_of_function][fname][bbid]["successors"].push_back({default_module, std::to_string(default_bbid)});

          for (auto &caseIt : SI->cases()) {
            BasicBlock& _BB = *(caseIt.getCaseSuccessor());
            uint32_t case_bbid = get_bbid_from_bb(_BB);
            std::string case_module = get_module_id_from_bb(_BB);
            cfg[module_of_function][fname][bbid]["successors"].push_back({case_module, std::to_string(case_bbid)});
          }
        } else if (auto *II = dyn_cast<InvokeInst>(terminator)){
            BasicBlock& normal_BB = *(II->getNormalDest());
            BasicBlock& exception_BB = *(II->getUnwindDest());
            uint32_t normalDestBBID = get_bbid_from_bb(normal_BB);
            std::string normal_module = get_module_id_from_bb(normal_BB);
            uint32_t exceptionDestBBID = get_bbid_from_bb(exception_BB);
            std::string exception_module = get_module_id_from_bb(exception_BB);
            cfg[module_of_function][fname][bbid]["successors"].push_back({normal_module, std::to_string(normalDestBBID)});
            cfg[module_of_function][fname][bbid]["successors"].push_back({exception_module, std::to_string(exceptionDestBBID)});
            cfg[module_of_function][fname][bbid]["terminatorIsInvokeInst"] = true;
        }

        for (Instruction& I: BB) {
          // CallBase handles both InvokeInst, CallInst.
          if (auto *CI = dyn_cast<CallBase>(&I)) {
            Value *calledValue = CI->getCalledOperand();

            llvm::Function *calledFunction = CI->getCalledFunction();
            if (calledFunction && !calledFunction->isIntrinsic()) {
              std::string callee_name;
              if (calledFunction->hasName()) callee_name = calledFunction->getName().str();
              else assert(false);
              if (callee_name.find("_runtime_") != 0 && callee_name.find("__runtime_") != 0) {
                // Don't log calls to our instrumentation runtime.
                std::string module_of_callee;
                llvm::BasicBlock& firstBB = calledFunction->front();
                if (calledFunction->isDeclaration()) {
                  // e.g., linked against libc
                  errs() << "calledFunction (external): " << callee_name << "\n";
                  module_of_callee = "__external__";
                }
                else {
                  module_of_callee = get_module_id_from_bb(firstBB);
                }
                cfg[module_of_function][fname][bbid]["callees"].push_back({module_of_callee, callee_name});
              }
            } // else: call target is indirect
          } 
        }
      }
    }


    for (auto& [module_name, functions] : cfg.items()) {
      std::cout << "Module: " << module_name << std::endl;
      // Replace "/" in moduleName, e.g., src/a.c will be serialized as ".cfg/src@a.c.json"
      std::string output_name = module_name;
      for (char& ch : output_name) {
          if (ch == '/') {
              ch = '@';
          }
      }
      serialize_json(cfg[module_name], (dirPath / (".cfg/" + output_name + ".json")).string());
    }


    serialize_json(j_bb_to_dbg, (dirPath / ".bb_to_dbg.json").string());
    return PreservedAnalyses::all();
  }
};

} // end anonymous namespace

extern "C" ::llvm::PassPluginLibraryInfo LLVM_ATTRIBUTE_WEAK
llvmGetPassPluginInfo() {
  return {LLVM_PLUGIN_API_VERSION, "AnalysisPass", "v0.1",
          [](PassBuilder &PB) {
            // Named registration for explicit invocation
            // i.e., loaded via opt

            PB.registerPipelineParsingCallback(
              [](StringRef Name, ModulePassManager &MPM,
                  ArrayRef<PassBuilder::PipelineElement>) {
                if (Name == "analysis-pass") {
                  MPM.addPass(AnalysisPass());
                  return true;
                }
                return false;
            });
          }};
}