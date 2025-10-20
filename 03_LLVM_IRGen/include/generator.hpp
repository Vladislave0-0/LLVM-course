#pragma once

#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>

using namespace llvm;

namespace LLVM_IRGen {
class Generator final {
  LLVMContext context;
  std::unique_ptr<Module> IRModule;
  IRBuilder<> builder;

  const std::string_view appName = "app";
  const std::string_view simPutPixelName = "simPutPixel";
  const std::string_view simFlushName = "simFlush";
  const std::string_view simRandName = "simRand";

  Function *printSimPutPixel();
  Function *printSimFlush();
  Function *printSimRand();

public:
  Generator(const std::string moduleID = "app.c")
      : context(), IRModule(std::make_unique<Module>(moduleID, context)),
        builder(context) {}

  void generation();
  void dump(const std::string &filename = "app.ll");
  bool verifyModule_();
  void interpretation();
};
} // namespace LLVM_IRGen
