#pragma once
#include <string>
#include <vector>

namespace asm2ir {

// Типы операндов.
enum class OperandType { REGISTER, IMMEDIATE, LABEL, MEMORY };

// Структура операнда.
struct Operand {
  OperandType type;
  std::string value;
};

// Структура инструкции.
struct Instruction {
  std::string opcode;
  std::vector<Operand> operands;
  size_t line_number;
};

} // namespace asm2ir
