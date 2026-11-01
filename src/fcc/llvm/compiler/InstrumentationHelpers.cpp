#include "llvm/IR/BasicBlock.h"

#include "InstrumentationHelpers.h"

using namespace llvm;

  MDNode* get_bbid_instrumentation(Instruction* instr) {
    return instr->getMetadata("bf_bbid");
  }

  ConstantInt* get_bbid_constantint(Instruction* instr) {
    return cast<ConstantInt>(cast<ValueAsMetadata>(get_bbid_instrumentation(instr)->getOperand(0))->getValue());
  }

  uint32_t get_bbid(Instruction* instr) {
    return get_bbid_constantint(instr)->getZExtValue();
  }

  uint32_t get_bbid_from_bb(BasicBlock& bb) {
    Instruction* instr = &(*(bb.getFirstInsertionPt()));
    return get_bbid(instr);
  }

std::string get_module_id_from_instr(Instruction* instr) {
    llvm::MDNode* metadataNode = instr->getMetadata("module_id");
    llvm::Metadata* metadata = metadataNode->getOperand(0).get();
    auto* mdString = llvm::dyn_cast<llvm::MDString>(metadata);
    return mdString->getString().str();
}

std::string get_module_id_from_bb(BasicBlock& bb) {
    Instruction* instr = &(*(bb.getFirstInsertionPt()));
    return get_module_id_from_instr(instr);
}