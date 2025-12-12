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

  Function *printSimPutPixel();
  Function *printSimFlush();
  Function *printSimRand();

  const std::string_view appName = "app";
  const std::string_view simPutPixelName = "simPutPixel";
  const std::string_view simFlushName = "simFlush";
  const std::string_view simRandName = "simRand";

public:
  IRGenerator()
      : context(), IRModule(std::make_unique<Module>(moduleName, context)),
        builder(context) {}

  std::unique_ptr<Module> &getIRModule() { return IRModule; }

  ~IRGenerator() = default;

  void buildIR(langParser &parser);
  void execute();

public:
  // antlrcpp::Any visitProgram(langParser::ProgramContext *ctx) override;
  // antlrcpp::Any visitStatements(langParser::StatementsContext *ctx) {



};

} // namespace lang2ir
