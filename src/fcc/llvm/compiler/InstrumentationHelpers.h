#ifndef INSTRUMENTATION_HELPERS_H
#define INSTRUMENTATION_HELPERS_H

#include <string>

#include "llvm/IR/Instruction.h"  // For llvm::Instruction
#include "llvm/IR/Metadata.h"     // For llvm::MDNode
#include "llvm/IR/Constants.h"    // For llvm::ConstantInt

using namespace llvm;

MDNode* get_bbid_instrumentation(Instruction* instr);
ConstantInt* get_bbid_constantint(Instruction* instr);
uint32_t get_bbid(Instruction* instr);
uint32_t get_bbid_from_bb(BasicBlock& bb);
std::string get_module_id_from_bb(BasicBlock& bb);
std::string get_module_id_from_instr(Instruction* instr);
MDNode* get_brid_instrumentation(Instruction* instr);
ConstantInt* get_brid_constantint(Instruction* instr);

#endif // INSTRUMENTATION_HELPERS_H