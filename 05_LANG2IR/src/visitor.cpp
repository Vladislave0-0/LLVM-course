#include "../include/visitor.hpp"

namespace lang2ir {

std::any LangVisitor::visitProg(langParser::ProgContext *ctx) {
  return visit(ctx->expr());
}

std::any LangVisitor::visitAdd(langParser::AddContext *ctx) {
  int left = std::stoi(ctx->left->getText());
  int right = std::stoi(ctx->right->getText());
  return left + right;
}

std::any LangVisitor::visitSingleNum(langParser::SingleNumContext *ctx) {
  return std::stoi(ctx->NUM()->getText());
}

} // namespace lang2ir
