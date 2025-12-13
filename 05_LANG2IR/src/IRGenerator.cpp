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

void IRGenerator::execute() {
  std::unique_ptr<Module> execModule = CloneModule(*IRModule);
  auto *app = execModule->getFunction(appName);
  if (!app) {
    std::cerr << "[Execution] Undefined reference to `app`\n";
    return;
  }

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
  auto *funcTy = llvm::FunctionType::get(voidTy, {i32Ty, i32Ty, i32Ty}, false);

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
  auto *funcTy = llvm::FunctionType::get(i32Ty, {}, false);

  return llvm::Function::Create(funcTy, llvm::GlobalValue::ExternalLinkage,
                                simRandName, *IRModule);
}

antlrcpp::Any IRGenerator::visitProgram(langParser::ProgramContext *ctx) {
  printSimFlush();
  printSimPutPixel();
  printSimRand();

  visitFuncList(ctx->funcList());

  return nullptr;
}

Value *IRGenerator::registerVariable(const std::string &name) {
  if (varList.back().find(name) != varList.back().end())
    throw std::runtime_error("[Error] Redeclaration of `var " + name + "`\n");

  auto *currBB = builder.GetInsertBlock();
  auto &entryBB = currFunc->getEntryBlock();

  builder.SetInsertPoint(&entryBB, entryBB.begin());

  auto ptr = builder.CreateAlloca(i32Ty);
  varList.back()[name] = ptr;
  builder.SetInsertPoint(currBB);

  return ptr;
}

Value *IRGenerator::searchVar(const std::string &name) {
  for (auto it = varList.rbegin(), end = varList.rend(); it != end; ++it) {
    if (auto find = it->find(name); find != it->end())
      return find->second;
  }

  throw std::runtime_error("[Error] Variable `" + name +
                           "` was not declared in this scope\n");
}

Value *IRGenerator::registerArray(const std::string &name, int x, int y) {
  if (arrList.back().find(name) != arrList.back().end())
    throw std::runtime_error("Redeclaration of `arr " + name + "`\n");

  auto *currBB = builder.GetInsertBlock();
  auto &entryBB = currFunc->getEntryBlock();

  builder.SetInsertPoint(&entryBB, entryBB.begin());

  ArrayType *ArrTy = ArrayType::get(ArrayType::get(i32Ty, y), x);
  auto ptr = builder.CreateAlloca(ArrTy);

  arrList.back()[name] = std::pair{(Value *)ptr, ArrTy};
  builder.SetInsertPoint(currBB);

  return ptr;
}

std::pair<Value *, ArrayType *>
IRGenerator::searchArray(const std::string &name) {
  for (auto it = arrList.rbegin(), end = arrList.rend(); it != end; ++it) {
    if (auto find = it->find(name); find != it->end())
      return find->second;
  }

  throw std::runtime_error("[Error] Array `" + name +
                           "` was not declared in this scope\n");
}

antlrcpp::Any IRGenerator::visitFuncInit(langParser::FuncInitContext *ctx) {
  std::string funcName = ctx->NAME()->getText();

  funcList.emplace_back(funcName);
  varList.emplace_back();
  arrList.emplace_back();

  size_t argsNum = ctx->argList() ? ctx->argList()->NAME().size() : 0;
  std::vector<Type *> argsTy(argsNum, i32Ty);

  FunctionType *funcTy = FunctionType::get(i32Ty, argsTy, false);
  Function *func = llvm::Function::Create(
      funcTy, llvm::GlobalValue::ExternalLinkage, funcName, *IRModule);

  BasicBlock *entryBB = BasicBlock::Create(context, "entry", func);
  builder.SetInsertPoint(entryBB);
  currFunc = func;

  for (size_t arg = 0; arg < argsNum; ++arg) {
    auto ptr = registerVariable(ctx->argList()->NAME()[arg]->getText());
    builder.CreateStore(func->getArg(arg), ptr);
  }

  visitStatements(ctx->statements());

  varList.pop_back();
  arrList.pop_back();

  return nullptr;
}

antlrcpp::Any IRGenerator::visitCall(langParser::CallContext *ctx) {
  auto funcName = ctx->NAME()->getText();
  Function *func = IRModule->getFunction(funcName);

  if (!func) {
    throw std::runtime_error("[Error] Function `" + funcName +
                             "` was not declared in this scope\n");
  }

  int callArgSize = ctx->callArgList() ? ctx->callArgList()->expr().size() : 0;

  std::string str = callArgSize > 0 ? "int" : "";
  for (int i = 1; i < callArgSize; ++i)
    str += ", int";

  if (callArgSize != func->arg_size()) {
    throw std::runtime_error("[Error] No matching function for call to `" +
                             funcName + "(" + str + ")`\n");
  }

  std::vector<Value *> args;
  args.reserve(callArgSize);
  for (size_t i = 0; i < callArgSize; ++i) {
    auto *val =
        std::any_cast<Value *>(visitExpr(ctx->callArgList()->expr()[i]));
    args.push_back(val);
  }

  return (Value *)builder.CreateCall(func, args);
}

antlrcpp::Any IRGenerator::visitArray(langParser::ArrayContext *ctx) {
  auto *x = std::any_cast<Value *>(visitExpr(ctx->expr()[0]));
  auto *y = std::any_cast<Value *>(visitExpr(ctx->expr()[1]));

  auto [ArrPtr, ArrType] = searchArray(ctx->NAME()->getText());
  return ArrPtr
             ? builder.CreateGEP(ArrType, ArrPtr, {builder.getInt32(0), x, y})
             : nullptr;
}

antlrcpp::Any IRGenerator::visitExpr(langParser::ExprContext *ctx) {
  // Двумерный массив: NAME '[' expr ']' '[' expr ']'
  if (ctx->array()) {
    auto ptr = std::any_cast<llvm::Value *>(visitArray(ctx->array()));
    return ptr ? (Value *)builder.CreateLoad(i32Ty, ptr, "array_load")
               : nullptr;
  }

  // Переменная: NAME
  if (ctx->NAME()) {
    auto ptr = searchVar(ctx->NAME()->getText());
    return ptr ? (Value *)(builder.CreateLoad(i32Ty, ptr, "load")) : nullptr;
  }

  // Вызов функции: NAME '(' callArgList? ')'
  if (ctx->call())
    return visitCall(ctx->call());

  // Число: INT
  if (ctx->INT())
    return (Value *)(builder.getInt32(std::stoi(ctx->INT()->getText())));

  // Унарный минус: '-' expr
  if (ctx->children.size() >= 1 && ctx->children[0]->getText() == "-")
    return builder.CreateNeg(std::any_cast<llvm::Value *>(visit(ctx->expr(0))));

  // Скобки: '(' expr ')'
  if (ctx->children.size() >= 3 && ctx->children[0]->getText() == "(" &&
      ctx->children[2]->getText() == ")") {
    return visit(ctx->expr(0));
  }

  // Бинарные операции
  if (ctx->children.size() >= 3) {
    llvm::Value *lhs = std::any_cast<llvm::Value *>(visit(ctx->expr(0)));
    llvm::Value *rhs = std::any_cast<llvm::Value *>(visit(ctx->expr(1)));

    std::string op = ctx->children[1]->getText();

    if (op == "+")
      return builder.CreateAdd(lhs, rhs, "add");
    if (op == "-")
      return builder.CreateSub(lhs, rhs, "sub");
    if (op == "*")
      return builder.CreateMul(lhs, rhs, "mul");
    if (op == "/")
      return builder.CreateSDiv(lhs, rhs, "div");
    if (op == "%")
      return builder.CreateSRem(lhs, rhs, "rem");
    if (op == "==")
      return builder.CreateICmpEQ(lhs, rhs, "eq");
    if (op == "!=")
      return builder.CreateICmpNE(lhs, rhs, "ne");
    if (op == "<")
      return builder.CreateICmpSLT(lhs, rhs, "lt");
    if (op == "<=")
      return builder.CreateICmpSLE(lhs, rhs, "le");
    if (op == ">")
      return builder.CreateICmpSGT(lhs, rhs, "gt");
    if (op == ">=")
      return builder.CreateICmpSGE(lhs, rhs, "ge");
  }

  return nullptr;
}

antlrcpp::Any IRGenerator::visitVarInit(langParser::VarInitContext *ctx) {
  std::string name = ctx->NAME()->getText();

  auto ptr = registerVariable(name);
  builder.CreateStore(std::any_cast<Value *>(visitExpr(ctx->expr())), ptr);

  return ptr;
}

antlrcpp::Any IRGenerator::visitArrInit(langParser::ArrInitContext *ctx) {
  std::string name = ctx->NAME()->getText();

  int x = std::stoi(ctx->INT()[0]->getText());
  int y = std::stoi(ctx->INT()[1]->getText());

  return registerArray(name, x, y);
}

antlrcpp::Any IRGenerator::visitAssignment(langParser::AssignmentContext *ctx) {
  Value *ptr = nullptr;

  if (ctx->NAME()) {
    ptr = searchVar(ctx->NAME()->getText());
  } else {
    ptr = std::any_cast<Value *>(visitArray(ctx->array()));
  }

  builder.CreateStore(std::any_cast<Value *>(visitExpr(ctx->expr())), ptr);

  return nullptr;
}

antlrcpp::Any
IRGenerator::visitElseStatement(langParser::ElseStatementContext *ctx) {
  varList.push_back(varList.back());
  arrList.push_back(arrList.back());

  visitStatements(ctx->statements());

  auto *afterElseBodyBB = BasicBlock::Create(context, "afterElseBB", currFunc);
  builder.CreateBr(afterElseBodyBB);
  builder.SetInsertPoint(afterElseBodyBB);

  varList.pop_back();
  arrList.pop_back();

  return nullptr;
}

antlrcpp::Any
IRGenerator::visitIfStatement(langParser::IfStatementContext *ctx) {
  varList.push_back(varList.back());
  arrList.push_back(arrList.back());

  auto *ifCondBB = BasicBlock::Create(context, "ifCondBB", currFunc);
  auto *ifBodyBB = BasicBlock::Create(context, "ifBodyBB", currFunc);

  std::string afterIfBodyBBname =
      ctx->elseStatement() ? "elseBodyBB" : "afterIfBB";
  auto *afterIfBodyBB =
      BasicBlock::Create(context, afterIfBodyBBname, currFunc);

  builder.CreateBr(ifCondBB);
  builder.SetInsertPoint(ifCondBB);

  auto condition = builder.CreateTrunc(
      std::any_cast<Value *>(visitExpr(ctx->expr())), builder.getInt1Ty());

  builder.CreateCondBr(condition, ifBodyBB, afterIfBodyBB);
  builder.SetInsertPoint(ifBodyBB);
  visitStatements(ctx->statements());

  builder.CreateBr(afterIfBodyBB);
  builder.SetInsertPoint(afterIfBodyBB);

  varList.pop_back();
  arrList.pop_back();

  if (ctx->elseStatement())
    return visitElseStatement(ctx->elseStatement());

  return nullptr;
}

antlrcpp::Any
IRGenerator::visitWhileStatement(langParser::WhileStatementContext *ctx) {
  varList.push_back(varList.back());
  arrList.push_back(arrList.back());

  auto *whileCondBB = BasicBlock::Create(context, "whileCondBB", currFunc);
  auto *whileBodyBB = BasicBlock::Create(context, "whileBodyBB", currFunc);
  auto *afterWhileBodyBB =
      BasicBlock::Create(context, "afterWhileBB", currFunc);

  builder.CreateBr(whileCondBB);
  builder.SetInsertPoint(whileCondBB);

  auto condition = builder.CreateTrunc(
      std::any_cast<Value *>(visitExpr(ctx->expr())), builder.getInt1Ty());

  builder.CreateCondBr(condition, whileBodyBB, afterWhileBodyBB);
  builder.SetInsertPoint(whileBodyBB);
  visitStatements(ctx->statements());

  builder.CreateBr(whileCondBB);
  builder.SetInsertPoint(afterWhileBodyBB);

  varList.pop_back();
  arrList.pop_back();

  return nullptr;
}

antlrcpp::Any
IRGenerator::visitReturnStatement(langParser::ReturnStatementContext *ctx) {
  builder.CreateRet(std::any_cast<Value *>(visitExpr(ctx->expr())));

  return nullptr;
}

antlrcpp::Any IRGenerator::visitStatement(langParser::StatementContext *ctx) {
  if (ctx->varInit()) {
    return visitVarInit(ctx->varInit());
  } else if (ctx->arrInit()) {
    return visitArrInit(ctx->arrInit());
  } else if (ctx->assignment()) {
    return visitAssignment(ctx->assignment());
  } else if (ctx->ifStatement()) {
    return visitIfStatement(ctx->ifStatement());
  } else if (ctx->whileStatement()) {
    return visitWhileStatement(ctx->whileStatement());
  } else if (ctx->call()) {
    return visitCall(ctx->call());
  } else if (ctx->returnStatement()) {
    return visitReturnStatement(ctx->returnStatement());
  }

  return nullptr;
}

antlrcpp::Any IRGenerator::visitStatements(langParser::StatementsContext *ctx) {
  for (auto statement : ctx->statement())
    visitStatement(statement);

  return nullptr;
}

antlrcpp::Any IRGenerator::visitFuncList(langParser::FuncListContext *ctx) {
  for (auto func : ctx->funcInit()) {
    bool funcExist = false;
    for (size_t i = 0; i < funcList.size(); ++i) {
      if (funcList[i] == func->NAME()->getText()) {
        funcExist = true;
        break;
      }
    }

    if (funcExist) {
      throw std::runtime_error("[Error] Redefinition of function `" +
                               func->NAME()->getText() + "`\n");
    }

    visitFuncInit(func);
  }

  return nullptr;
}

} // namespace lang2ir
