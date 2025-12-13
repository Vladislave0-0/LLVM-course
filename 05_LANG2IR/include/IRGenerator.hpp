#pragma once

#include "../generated/langBaseVisitor.h"
#include "../generated/langParser.h"

#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>

namespace lang2ir {

using namespace llvm;
using namespace antlr4;

class IRGenerator final : public langBaseVisitor {
  const std::string_view moduleName = "LANG2IR";

  LLVMContext context;
  std::unique_ptr<Module> IRModule;
  IRBuilder<> builder;

  std::vector<std::map<std::string, Value *>> varList;
  std::vector<std::map<std::string, std::pair<Value *, ArrayType *>>> arrList;
  std::vector<std::string> funcList;

  Function *currFunc;

  Function *printSimPutPixel();
  Function *printSimFlush();
  Function *printSimRand();

  const std::string_view appName = "app";
  const std::string_view simPutPixelName = "simPutPixel";
  const std::string_view simFlushName = "simFlush";
  const std::string_view simRandName = "simRand";

  Type *i32Ty;

public:
  IRGenerator()
      : context(), IRModule(std::make_unique<Module>(moduleName, context)),
        builder(context), varList(1), arrList(1), funcList(1) {
    i32Ty = llvm::Type::getInt32Ty(context);
  }

  std::unique_ptr<Module> &getIRModule() { return IRModule; }

  ~IRGenerator() = default;

  void buildIR(langParser &parser);
  void execute();

public:
  antlrcpp::Any visitProgram(langParser::ProgramContext *ctx) override;
  antlrcpp::Any visitFuncList(langParser::FuncListContext *ctx) override;
  antlrcpp::Any visitFuncInit(langParser::FuncInitContext *ctx) override;
  antlrcpp::Any visitStatements(langParser::StatementsContext *ctx) override;
  antlrcpp::Any visitStatement(langParser::StatementContext *ctx) override;

  antlrcpp::Any visitVarInit(langParser::VarInitContext *ctx) override;
  antlrcpp::Any visitArrInit(langParser::ArrInitContext *ctx) override;
  antlrcpp::Any visitAssignment(langParser::AssignmentContext *ctx) override;
  antlrcpp::Any visitIfStatement(langParser::IfStatementContext *ctx) override;
  antlrcpp::Any
  visitElseStatement(langParser::ElseStatementContext *ctx) override;
  antlrcpp::Any
  visitWhileStatement(langParser::WhileStatementContext *ctx) override;
  antlrcpp::Any visitCall(langParser::CallContext *ctx) override;
  antlrcpp::Any
  visitReturnStatement(langParser::ReturnStatementContext *ctx) override;
  antlrcpp::Any visitExpr(langParser::ExprContext *ctx) override;
  antlrcpp::Any visitArray(langParser::ArrayContext *ctx) override;

  Value *registerVariable(const std::string &name);
  Value *searchVar(const std::string &name);
  Value *registerArray(const std::string &name, int x, int y);
  std::pair<Value *, ArrayType *> searchArray(const std::string &name);
};

} // namespace lang2ir
