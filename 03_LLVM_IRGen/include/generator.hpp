#pragma once

#include "llvm/ExecutionEngine/ExecutionEngine.h"
#include "llvm/ExecutionEngine/GenericValue.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Verifier.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/Support/raw_ostream.h"
#include <memory>
#include <string_view>

using namespace llvm;

namespace LLVM_IRGen {
class Generator final {
  LLVMContext context;
  std::unique_ptr<Module> IRModule;
  IRBuilder<> builder;

  const std::string_view appName = "app";
  const std::string_view simRandName = "simRand";
  const std::string_view simFlushName = "simFlush";
  const std::string_view simPutPixelName = "simPutPixel";

  Function *printSimFlush();
  Function *printSimRand();
  Function *printSimPutPixel();

public:
  Generator(const std::string moduleID)
      : context(), IRModule(std::make_unique<Module>(moduleID, context)),
        builder(context) {}

  void generation();
  void interpretation();
  void dump();
};

} // namespace LLVM_IRGen
