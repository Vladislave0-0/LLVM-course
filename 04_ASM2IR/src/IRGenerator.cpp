#include "../include/IRGenerator.hpp"

namespace asm2ir {

Function *IRGenerator::printSimPutPixel() {
  auto *voidTy = Type::getVoidTy(context);
  auto *i32 = Type::getInt32Ty(context);
  auto *funcTy = FunctionType::get(voidTy, {i32, i32, i32}, false);

  return Function::Create(funcTy, Function::ExternalLinkage, simPutPixelName,
                          *IRModule);
}

Function *IRGenerator::printSimFlush() {
  auto *voidTy = Type::getVoidTy(context);
  auto *funcTy = FunctionType::get(voidTy, {}, false);

  return Function::Create(funcTy, Function::ExternalLinkage, simFlushName,
                          *IRModule);
}

Function *IRGenerator::printSimRand() {
  auto *i32 = Type::getInt32Ty(context);
  auto *funcTy = FunctionType::get(i32, {}, false);

  return Function::Create(funcTy, Function::ExternalLinkage, simRandName,
                          *IRModule);
}

Function *IRGenerator::printDumpReg() {
  auto *i64 = Type::getInt64Ty(context);
  FunctionType *funcTy =
      FunctionType::get(builder.getVoidTy(), {i64, i64}, false);

  return Function::Create(funcTy, Function::ExternalLinkage, dumpRegName,
                          *IRModule);
}

} // namespace asm2ir
