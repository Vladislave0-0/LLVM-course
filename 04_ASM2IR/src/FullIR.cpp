#include "../include/FullIR.hpp"
#include "../include/AsmParser.hpp"
#include "CPU.hpp"
#include <llvm-18/llvm/ExecutionEngine/ExecutionEngine.h>
#include <llvm-18/llvm/ExecutionEngine/GenericValue.h>
#include <llvm-18/llvm/IR/Verifier.h>
#include <llvm-18/llvm/Transforms/Utils/Cloning.h>

namespace asm2ir {

extern "C" {
void simInit();
void simExit();
}

void FullIRGenerator::buildIR(const AsmParser &parser) {
  auto i64Ty = Type::getInt64Ty(context);

  ArrayType *regFileType = ArrayType::get(i64Ty, CPU::reg_size);
  IRModule->getOrInsertGlobal("reg_file", regFileType);
  reg_file = IRModule->getNamedGlobal("reg_file");

  FunctionType *FuncType = FunctionType::get(Type::getVoidTy(context), false);
  Function *AppFunc =
      Function::Create(FuncType, Function::ExternalLinkage, appName, *IRModule);

  auto *simFlush = printSimFlush();
  auto *simPutPixel = printSimPutPixel();
  auto *simRand = printSimRand();
  auto *dumpReg = printDumpReg();

  std::unordered_map<uint32_t, BasicBlock *> BBMap;
  for (auto &BB : parser.basic_blocks)
    BBMap[parser.bb2pc.at(BB)] = BasicBlock::Create(context, BB, AppFunc);

  uint32_t pc = 0;

  builder.SetInsertPoint(BBMap[0]);
  for (const Instruction &I : parser.instructions) {
    switch (I.opcode) {
    default:
      break;
#define ISA(Opcode_, Name_, SkipArgs_, ReadArgs_, WriteArgs_, Execute_,        \
            IRGenExecute_)                                                     \
  case (Opcode_):                                                              \
    IRGenExecute_;                                                             \
    break;
#include "../include/ISA.hpp"
#undef ISA
    }

    ++pc;
  }
}

void FullIRGenerator::execute(CPU &cpu) {
  auto execModule = CloneModule(*IRModule);
  auto *app = execModule->getFunction(appName);
  execModule->getFunction(simFlushName);
  execModule->getFunction(simRandName);
  execModule->getFunction(dumpRegName);
  execModule->getFunction(simPutPixelName);

  LLVMInitializeNativeTarget();
  LLVMInitializeNativeAsmPrinter();

  ExecutionEngine *ee = EngineBuilder(std::move(execModule)).create();
  ee->InstallLazyFunctionCreator([&](const std::string &fnName) -> void * {
    if (fnName == simFlushName) {
      return reinterpret_cast<void *>(simFlush);
    } else if (fnName == simRandName) {
      return reinterpret_cast<void *>(simRand);
    } else if (fnName == dumpRegName) {
      return reinterpret_cast<void *>(dumpReg);
    } else if (fnName == simPutPixelName) {
      return reinterpret_cast<void *>(simPutPixel);
    }

    return nullptr;
  });

  ee->addGlobalMapping(reg_file, (void *)cpu.reg_file);
  ee->finalizeObject();

  simInit();
  CPU::setCPU(&cpu);

  ArrayRef<GenericValue> noargs;
  ee->runFunction(app, noargs);

  simExit();
}

} // namespace asm2ir
