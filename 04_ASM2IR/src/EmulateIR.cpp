#include "../include/EmulateIR.hpp"
#include "Instructions.hpp"

#include <llvm/ExecutionEngine/ExecutionEngine.h>
#include <llvm/ExecutionEngine/GenericValue.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Verifier.h>
#include <llvm/Transforms/Utils/Cloning.h>

extern "C" {
void simInit();
void simExit();
}

namespace asm2ir {

using namespace llvm;

void EmulateIRGenerator::buildIR(const AsmParser &parser) {
  auto voidTy = Type::getVoidTy(context);
  auto i64Ty = Type::getInt32Ty(context);

  ArrayType *regFileType = ArrayType::get(i64Ty, CPU::reg_size);
  IRModule->getOrInsertGlobal("reg_file", regFileType);
  auto regFile = IRModule->getNamedGlobal("reg_file");

  FunctionType *funcTy = FunctionType::get(voidTy, false);
  Function *appFunc =
      Function::Create(funcTy, Function::ExternalLinkage, appName, *IRModule);

  // Functions types
  FunctionType *voidFuncTy = FunctionType::get(voidTy, false);
  ArrayRef<Type *> int64x4Types = {i64Ty, i64Ty, i64Ty, i64Ty};
  FunctionType *int64x4FuncType =
      FunctionType::get(voidTy, int64x4Types, false);

  // Functions
#define ISA(Opcode, Name, SkipArgs, ReadArgs, WriteArgs, Execute,              \
            IRGenExecute)                                                      \
  FunctionCallee Callee##Name =                                                \
      IRModule->getOrInsertFunction("do_" #Name, int64x4FuncType);
#include "../include/ISA.hpp"
#undef ISA

  std::unordered_map<uint32_t, BasicBlock *> BBMap;
  for (auto &BB : parser.basic_blocks) {
    // std::cout << "Add bb at pc = " << parser.bb2pc.at(BB)
    //           << " with name = " << BB << '\n';
    BBMap[parser.bb2pc.at(BB)] = BasicBlock::Create(context, BB, appFunc);
  }

  uint32_t pc = 0;
  builder.SetInsertPoint(BBMap[0]);
  for (const Instruction &I : parser.instructions) {
    // std::cout << "IN IR GEN: instr name = "
    //           << parser.instrs_info.op2str.at(I.opcode) << '\n';
    // std::cout << "IN IR GEN: rs2imm = " << I.rs2imm << '\n';
    Value *arg1 = builder.getInt32(I.rd);
    Value *arg2 = builder.getInt32(I.r1);
    Value *arg3 = builder.getInt32(I.r2imm);
    Value *arg4 = builder.getInt32(I.r3imm);
    Value *args[] = {arg1, arg2, arg3, arg4};
    switch (I.opcode) {
    default:
      break;
#define ISA(Opcode, Name, SkipArgs, ReadArgs, WriteArgs, Execute,              \
            IRGenExecute)                                                      \
  case (Opcode):                                                               \
    builder.CreateCall(Callee##Name, args);                                    \
    break;
#include "../include/ISA.hpp"
#undef ISA
    }
    ++pc;
    auto BB = BBMap.find(pc);

    switch (I.opcode) {
    case Instruction::BR_COND:
      arg1 = builder.CreateConstGEP2_32(regFileType, regFile, 0, I.rd);
      arg2 = builder.CreateTrunc(builder.CreateLoad(i64Ty, arg1),
                                 builder.getInt1Ty());
      if (BB != BBMap.end())
        builder.CreateCondBr(arg2, BBMap[I.r2imm], BB->second);

      break;

    case Instruction::BRANCH:
      builder.CreateBr(BBMap[I.r2imm]);
      break;

    case Instruction::EXIT:
      builder.CreateRetVoid();
      break;

    default:
      if (BB != BBMap.end())
        builder.CreateBr(BB->second);

      break;
    }

    if (BB != BBMap.end())
      builder.SetInsertPoint(BB->second);
  }
}

void EmulateIRGenerator::execute(CPU &cpu) {
  IRModule->dump();
  auto execModule = CloneModule(*IRModule);
  auto *app = execModule->getFunction(appName);

  LLVMInitializeNativeTarget();
  LLVMInitializeNativeAsmPrinter();

  ExecutionEngine *ee = EngineBuilder(std::move(execModule)).create();
  ee->InstallLazyFunctionCreator([](const std::string &fnName) -> void * {
#define ISA(Opcode, Name, SkipArgs, ReadArgs, WriteArgs, Execute,              \
            IRGenExecute)                                                      \
  if (fnName == "do_" #Name)                                                   \
    return reinterpret_cast<void *>(CPU::do_##Name);
#include "../include/ISA.hpp"
#undef ISA
    return nullptr;
  });

  ee->finalizeObject();

  CPU::setCPU(&cpu);
  simInit();

  ArrayRef<GenericValue> noargs;
  ee->runFunction(app, noargs);

  simExit();
}

} // namespace asm2ir
