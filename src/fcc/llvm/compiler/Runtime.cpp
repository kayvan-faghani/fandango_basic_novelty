#include <llvm/IR/IRBuilder.h>
#include "llvm/IR/DerivedTypes.h"

#include "Runtime.h"

using namespace llvm;

namespace {

template <typename... ArgsTy>
RtFnT import(llvm::Module &M, llvm::StringRef name, llvm::Type *ret,
              ArgsTy... args) {
#if LLVM_VERSION_MAJOR >= 9 && LLVM_VERSION_MAJOR < 11
  return M.getOrInsertFunction(name, ret, args...).getCallee();
#else
  return M.getOrInsertFunction(name, ret, args...);
#endif
}

} // namespace

Runtime::Runtime(Module &M) {
  IRBuilder<> IRB(M.getContext());
  auto *ptrT = PointerType::get(IRB.getInt8Ty(), 0);
  auto *int8T = IRB.getInt8Ty();
  auto *int16T = IRB.getInt16Ty();
  auto *int32T = IRB.getInt32Ty();
  auto *int64T = IRB.getInt64Ty();
  auto *int64PtrT = PointerType::get(IRB.getInt64Ty(), 0);

  auto *voidT = IRB.getVoidTy();

  _print = import(M, "_runtime_print", voidT, ptrT);
  _branch = import(M, "_runtime_branch", voidT, int32T);
  _bb =  import(M, "_runtime_bb", voidT, ptrT, int32T); // char* moduleIdentifier, uint32 bbid
  _start_logging = import(M, "_runtime_start_logging", voidT);
  _goal = import(M, "_runtime_goal", voidT);
  _initialize = import(M, "_runtime_initialize", voidT, ptrT, int64PtrT, int32T);
  _track_heap_alloc = import(M, "_runtime_track_heap_alloc", voidT, int32T);
}
