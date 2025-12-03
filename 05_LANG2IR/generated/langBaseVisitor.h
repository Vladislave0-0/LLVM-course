
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

  virtual std::any visitProg(langParser::ProgContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAdd(langParser::AddContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSingleNum(langParser::SingleNumContext *ctx) override {
    return visitChildren(ctx);
  }


};

