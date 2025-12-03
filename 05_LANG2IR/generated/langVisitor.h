
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
    virtual std::any visitProg(langParser::ProgContext *context) = 0;

    virtual std::any visitAdd(langParser::AddContext *context) = 0;

    virtual std::any visitSingleNum(langParser::SingleNumContext *context) = 0;


};

