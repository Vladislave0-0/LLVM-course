#pragma once

#include "IRGenerator.hpp"

namespace asm2ir {
class FullIRGenerator final : public IRGenerator {
  std::vector<std::unique_ptr<GlobalVariable>> globals;

public:
  void buildIR(const AsmParser &parser) override;
  void execute(CPU &cpu) override;
};
} // namespace asm2ir
