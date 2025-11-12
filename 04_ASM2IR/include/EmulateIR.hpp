#pragma once

#include "IRGenerator.hpp"

namespace asm2ir {

struct EmulateIRGenerator final : public IRGenerator {
  void buildIR(const AsmParser &parser) override;
  void execute(CPU &cpu) override;
  GlobalVariable *reg_file;
};

} // namespace asm2ir
