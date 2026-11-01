#ifndef RUNTIME_H
#define RUNTIME_H

#include <llvm/IR/InstrTypes.h>
#include <llvm/IR/Module.h>

#if LLVM_VERSION_MAJOR >= 9 && LLVM_VERSION_MAJOR < 11
  using RtFnT = llvm::Value *;
#else
  using RtFnT = llvm::FunctionCallee;
#endif

/// Runtime functions
struct Runtime {
    Runtime(llvm::Module &M);

    RtFnT _print{};
    RtFnT _branch{};
    RtFnT _bb{};
    RtFnT _start_logging{};
    RtFnT _goal{};
    RtFnT _initialize{};
    RtFnT _track_heap_alloc{};
};

#endif
