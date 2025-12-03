#pragma once

#include "../generated/langBaseVisitor.h"
#include "../generated/langLexer.h"
#include "../generated/langParser.h"
#include <any>

using namespace antlr4;

namespace lang2ir {

struct LangVisitor : public langBaseVisitor {
  // Программа
  std::any visitProg(langParser::ProgContext *ctx) override;

  // Сложение двух чисел
  std::any visitAdd(langParser::AddContext *ctx) override;

  // Одно число
  std::any visitSingleNum(langParser::SingleNumContext *ctx) override;
};

} // namespace lang2ir
