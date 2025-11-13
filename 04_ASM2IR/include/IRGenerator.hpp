#pragma once

#include "AsmParser.hpp"
#include "CPU.hpp"

#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>

namespace asm2ir {

using namespace llvm;

class IRGenerator {
  const std::string_view moduleName = "ASM2IR";

protected:
  LLVMContext context;
  std::unique_ptr<Module> IRModule;
  IRBuilder<> builder;

  Function *printSimPutPixel();
  Function *printSimFlush();
  Function *printSimRand();
  Function *printDumpReg();

  const std::string_view appName = "app";
  const std::string_view simPutPixelName = "simPutPixel";
  const std::string_view simFlushName = "simFlush";
  const std::string_view simRandName = "simRand";
  const std::string_view dumpRegName = "dumpReg";

public:
  IRGenerator()
      : context(), IRModule(std::make_unique<Module>(moduleName, context)),
        builder(context) {}

  std::unique_ptr<Module> &getIRModule() {
    return IRModule;
  }

  virtual ~IRGenerator() = default;

  virtual void buildIR(const AsmParser &parser) = 0;

  virtual void execute(CPU &cpu) = 0;
};

} // namespace asm2ir
