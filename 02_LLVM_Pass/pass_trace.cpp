#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Verifier.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"

using namespace llvm;

struct MyInstrPass : public PassInfoMixin<MyInstrPass> {

  bool isFuncLogger(StringRef name) { return name == "useLogger"; }

  bool insertUseLogger(IRBuilder<> &builder, Instruction &instruction,
                       Instruction *instrUse, FunctionCallee &useLogFunc) {
    for (auto &instrUseOperand : instrUse->operands()) {
      Value *operand = instrUseOperand.get();

      if (auto *operandLikeInstr = dyn_cast<Instruction>(operand)) {
        builder.SetInsertPoint(&instruction);

        Value *userOpName =
            builder.CreateGlobalStringPtr(instruction.getOpcodeName());

        if (isa<PHINode>(operandLikeInstr)) {
          insertUseLogger(builder, instruction, operandLikeInstr, useLogFunc);
        } else {
          Value *useOpName =
              builder.CreateGlobalStringPtr(operandLikeInstr->getOpcodeName());

          builder.CreateCall(useLogFunc, {userOpName, useOpName});
        }
      }
    }

    return true;
  }

  PreservedAnalyses run(Module &module, ModuleAnalysisManager &AM) {
    LLVMContext &context = module.getContext();
    IRBuilder<> builder(context);
    Type *voidTy = Type::getVoidTy(context);
    Type *int8PtrTy = Type::getInt8Ty(context)->getPointerTo();

    ArrayRef<Type *> paramTypes = {int8PtrTy, int8PtrTy};
    FunctionType *logFuncType = FunctionType::get(voidTy, paramTypes, false);
    FunctionCallee useLogFunc =
        module.getOrInsertFunction("useLogger", logFuncType);

    bool change = false;
    for (auto &function : module) {
      if (isFuncLogger(function.getName()) || function.isDeclaration())
        continue;

      for (auto &basicBlock : function) {
        for (auto &instruction : basicBlock) {
          if (isa<PHINode>(&instruction))
            continue;

          bool instrChange =
              insertUseLogger(builder, instruction, &instruction, useLogFunc);

          change = change ? change : instrChange;
        }
      }
    }

    return change ? PreservedAnalyses::none() : PreservedAnalyses::all();
  }
};

PassPluginLibraryInfo getPassPluginInfo() {
  const auto callback = [](PassBuilder &PB) {
    PB.registerOptimizerLastEPCallback([](ModulePassManager &MPM, auto) {
      MPM.addPass(MyInstrPass{});
      return true;
    });
  };

  return {LLVM_PLUGIN_API_VERSION, "TracePlugin", "0.0.1", callback};
};

extern "C" LLVM_ATTRIBUTE_WEAK PassPluginLibraryInfo llvmGetPassPluginInfo() {
  return getPassPluginInfo();
}
