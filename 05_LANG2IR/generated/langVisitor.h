
// Generated from lang.g4 by ANTLR 4.13.1

#pragma once


#include "antlr4-runtime.h"
#include "langParser.h"



/**
 * This class defines an abstract visitor for a parse tree
 * produced by langParser.
 */
class  langVisitor : public antlr4::tree::AbstractParseTreeVisitor {
public:

  /**
   * Visit parse trees produced by langParser.
   */
    virtual std::any visitProgram(langParser::ProgramContext *context) = 0;

    virtual std::any visitFuncList(langParser::FuncListContext *context) = 0;

    virtual std::any visitFuncInit(langParser::FuncInitContext *context) = 0;

    virtual std::any visitArgList(langParser::ArgListContext *context) = 0;

    virtual std::any visitStatements(langParser::StatementsContext *context) = 0;

    virtual std::any visitStatement(langParser::StatementContext *context) = 0;

    virtual std::any visitVarInit(langParser::VarInitContext *context) = 0;

    virtual std::any visitArrInit(langParser::ArrInitContext *context) = 0;

    virtual std::any visitAssignment(langParser::AssignmentContext *context) = 0;

    virtual std::any visitIfStatement(langParser::IfStatementContext *context) = 0;

    virtual std::any visitElseStatement(langParser::ElseStatementContext *context) = 0;

    virtual std::any visitWhileStatement(langParser::WhileStatementContext *context) = 0;

    virtual std::any visitCall(langParser::CallContext *context) = 0;

    virtual std::any visitCallArgList(langParser::CallArgListContext *context) = 0;

    virtual std::any visitReturnStatement(langParser::ReturnStatementContext *context) = 0;

    virtual std::any visitArray(langParser::ArrayContext *context) = 0;

    virtual std::any visitExpr(langParser::ExprContext *context) = 0;


};

