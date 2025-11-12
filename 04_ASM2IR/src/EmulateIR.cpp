#include "../include/EmulateIR.hpp"

#include <llvm/ExecutionEngine/ExecutionEngine.h>
#include <llvm/ExecutionEngine/GenericValue.h>
#include <llvm/Transforms/Utils/Cloning.h>

extern "C" {
void simInit();
void simExit();
}

namespace asm2ir {

using namespace llvm;

void EmulateIRGenerator::buildIR(const AsmParser &parser) {
  auto voidTy = Type::getVoidTy(context);
  auto i64Ty = Type::getInt64Ty(context);

  ArrayType *regFileType = ArrayType::get(i64Ty, CPU::reg_size);
  IRModule->getOrInsertGlobal("reg_file", regFileType);
  reg_file = IRModule->getNamedGlobal("reg_file");
  // if (!reg_file->hasInitializer())
  //   reg_file->setInitializer(ConstantAggregateZero::get(regFileType));

  FunctionType *funcTy = FunctionType::get(voidTy, false);
  Function *appFunc =
      Function::Create(funcTy, Function::ExternalLinkage, appName, *IRModule);

  std::vector<Type *> paramTypes = {i64Ty, i64Ty, i64Ty, i64Ty};
  FunctionType *doFuncType = FunctionType::get(voidTy, paramTypes, false);

#define ISA(Opcode, Name, SkipArgs, ReadArgs, WriteArgs, Execute,              \
            IRGenExecute)                                                      \
  Function *Callee##Name = Function::Create(                                   \
      doFuncType, Function::ExternalLinkage, "do_" #Name, IRModule.get());
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
    Value *arg1 = builder.getInt64(static_cast<uint64_t>(I.rd));
    Value *arg2 = builder.getInt64(static_cast<uint64_t>(I.r1));
    Value *arg3 = builder.getInt64(static_cast<uint64_t>(I.r2imm));
    Value *arg4 = builder.getInt64(static_cast<uint64_t>(I.r3imm));
    Value *args[] = {arg1, arg2, arg3, arg4};

    switch (I.opcode) {
#define ISA(Opcode, Name, SkipArgs, ReadArgs, WriteArgs, Execute,              \
            IRGenExecute)                                                      \
  case (Opcode):                                                               \
    builder.CreateCall(Callee##Name, args);                                    \
    break;
#include "../include/ISA.hpp"
#undef ISA

    default:
      break;
    }

    ++pc;
    auto BB = BBMap.find(pc);

    switch (I.opcode) {
    case Instruction::BR_COND:
      arg1 = builder.CreateConstGEP2_32(regFileType, reg_file, 0,
                                        static_cast<unsigned>(I.rd));
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

  ee->addGlobalMapping(reg_file, (void *)cpu.reg_file);
  ee->finalizeObject();

  CPU::setCPU(&cpu);
  simInit();

  ArrayRef<GenericValue> noargs;
  ee->runFunction(app, noargs);

  simExit();
}

} // namespace asm2ir
