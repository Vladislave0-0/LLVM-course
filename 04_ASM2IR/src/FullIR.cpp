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
  auto voidTy = Type::getVoidTy(context);
  auto int64Ty = Type::getInt64Ty(context);
  auto int32PtrTy = Type::getInt32Ty(context)->getPointerTo();

  auto *SwitchTableTy = ArrayType::get(builder.getInt32Ty(), 3);
  auto &SwitchTable = globals.emplace_back(std::make_unique<GlobalVariable>(
      *IRModule, SwitchTableTy, true, GlobalValue::PrivateLinkage,
      ConstantArray::get(SwitchTableTy, {builder.getInt32(-16711936),
                                         builder.getInt32(-16776961),
                                         builder.getInt32(-65536)}),
      "switch.table.app"));

  SwitchTable->setUnnamedAddr(GlobalValue::UnnamedAddr::Local);
  SwitchTable->setAlignment(Align(4));

  FunctionType *FuncType = FunctionType::get(voidTy, false);
  Function *AppFunc =
      Function::Create(FuncType, Function::ExternalLinkage, appName, *IRModule);

  auto *simFlush = printSimFlush();
  auto *simPutPixel = printSimPutPixel();
  auto *simRand = printSimRand();

  std::unordered_map<uint32_t, BasicBlock *> BBMap;
  for (auto &BB : parser.basic_blocks) {
    BBMap[parser.bb2pc.at(BB)] = BasicBlock::Create(context, BB, AppFunc);
  }

  uint32_t pc = 0;

  builder.SetInsertPoint(BBMap[0]);
  ArrayType *regFileType = ArrayType::get(int64Ty, CPU::reg_size);
  Value *reg_file = builder.CreateAlloca(regFileType);

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
  auto *simFlush = execModule->getFunction(simFlushName);
  auto *simRand = execModule->getFunction(simRandName);
  auto *simPutPixel = execModule->getFunction(simPutPixelName);

  LLVMInitializeNativeTarget();
  LLVMInitializeNativeAsmPrinter();

  ExecutionEngine *ee = EngineBuilder(std::move(execModule)).create();
  ee->InstallLazyFunctionCreator([&](const std::string &fnName) -> void * {
    if (fnName == simFlushName) {
      return reinterpret_cast<void *>(simFlush);
    } else if (fnName == simRandName) {
      return reinterpret_cast<void *>(simRand);
    } else if (fnName == simPutPixelName) {
      return reinterpret_cast<void *>(simPutPixel);
    }

    return nullptr;
  });
  ee->finalizeObject();

  simInit();
  CPU::setCPU(&cpu);

  ArrayRef<GenericValue> noargs;
  ee->runFunction(app, noargs);

  simExit();
}

} // namespace asm2ir
