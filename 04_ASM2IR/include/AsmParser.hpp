#pragma once

#include "Instructions.hpp"

#include <vector>

namespace asm2ir {

struct AsmParser final {
  std::string filename;

  std::vector<Instruction> instructions;
  InstructionInfo instrs_info;
  std::vector<std::string> basic_blocks;
  std::unordered_map<std::string, uint64_t> bb2pc;
  std::unordered_map<uint64_t, std::string> pc2bb;

  AsmParser(const std::string &filename) : filename(filename) {};

  bool parse();
  bool searchBBs(std::istream &input);
  bool readInstructions(std::istream &input);
};

} // namespace asm2ir
