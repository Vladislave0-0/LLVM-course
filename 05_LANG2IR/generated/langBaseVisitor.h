
// Generated from lang.g4 by ANTLR 4.13.1

#pragma once


#include "antlr4-runtime.h"
#include "langVisitor.h"


/**
 * This class provides an empty implementation of langVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class  langBaseVisitor : public langVisitor {
public:

  virtual std::any visitProgram(langParser::ProgramContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFuncList(langParser::FuncListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFuncInit(langParser::FuncInitContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitArgList(langParser::ArgListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStatements(langParser::StatementsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStatement(langParser::StatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitVarInit(langParser::VarInitContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitArrInit(langParser::ArrInitContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAssignment(langParser::AssignmentContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitIfStatement(langParser::IfStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitElseStatement(langParser::ElseStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitWhileStatement(langParser::WhileStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCall(langParser::CallContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCallArgList(langParser::CallArgListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitReturnStatement(langParser::ReturnStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitArray(langParser::ArrayContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitExpr(langParser::ExprContext *ctx) override {
    return visitChildren(ctx);
  }


};

