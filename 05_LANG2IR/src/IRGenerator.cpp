#include "../include/IRGenerator.hpp"
#include <llvm-18/llvm/ExecutionEngine/ExecutionEngine.h>
#include <llvm-18/llvm/ExecutionEngine/GenericValue.h>
#include <llvm-18/llvm/Transforms/Utils/Cloning.h>

namespace lang2ir {

extern "C" {
void simInit();
void simExit();
int simRand();
void simPutPixel(int x, int y, int argb);
void simFlush();
}

// void IRGenerator::buildIR(langParser &parser) {
  // FunctionType *FuncType = FunctionType::get(Type::getVoidTy(context),
  // false); Function *AppFunc =
  //     Function::Create(FuncType, Function::ExternalLinkage, appName,
  //     *IRModule);

  // printSimFlush();
  // printSimPutPixel();
  // printSimRand();

  // auto tree = parser.prog();
  // int result = std::any_cast<int>(this->visit(tree));
  // std::cout << result << std::endl;

//   return;
// }

void IRGenerator::execute() {
  std::unique_ptr<Module> execModule = CloneModule(*IRModule);
  auto *app = execModule->getFunction(appName);

  execModule->getFunction(simFlushName);
  execModule->getFunction(simRandName);
  execModule->getFunction(simPutPixelName);

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

  ArrayRef<GenericValue> noArgs;
  ee->runFunction(app, noArgs);

  simExit();
}

llvm::Function *IRGenerator::printSimPutPixel() {
  auto *voidTy = llvm::Type::getVoidTy(context);
  auto *i32 = llvm::Type::getInt32Ty(context);
  auto *funcTy = llvm::FunctionType::get(voidTy, {i32, i32, i32}, false);

  return llvm::Function::Create(funcTy, llvm::GlobalValue::ExternalLinkage,
                                simPutPixelName, *IRModule);
}

llvm::Function *IRGenerator::printSimFlush() {
  auto *voidTy = llvm::Type::getVoidTy(context);
  auto *funcTy = llvm::FunctionType::get(voidTy, {}, false);

  return llvm::Function::Create(funcTy, llvm::GlobalValue::ExternalLinkage,
                                simFlushName, *IRModule);
}

llvm::Function *IRGenerator::printSimRand() {
  auto *i32 = llvm::Type::getInt32Ty(context);
  auto *funcTy = llvm::FunctionType::get(i32, {}, false);

  return llvm::Function::Create(funcTy, llvm::GlobalValue::ExternalLinkage,
                                simRandName, *IRModule);
}

// antlrcpp::Any IRGenerator::visitProgram(langParser::ProgrammContext *ctx) {
//   printSimFlush();
//   printSimPutPixel();
//   printSimRand();

//   visitStatements(ctx->funcInit());

//   visitFuncInit(langParser::FuncInitContext *ctx)

//   return nullptr;
// }

//   antlrcpp::Any visitStatements(langParser::StatementsContext *ctx) {
//     for (auto statement: ctx->statement()) {
//       visitStatement(statement);
//     }
//     return nullptr;
//   }

} // namespace lang2ir
