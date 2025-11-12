#pragma once

#include "Instructions.hpp"

#include <string>
#include <unordered_map>
#include <vector>

namespace asm2ir {

class AsmParser {
  std::string filename;

  std::vector<Instruction> instructions;
  InstructionInfo instrs_info;
  std::vector<std::string> basic_blocks;
  std::unordered_map<std::string, uint64_t> bb2pc;
  std::unordered_map<uint64_t, std::string> pc2bb;

public:
  AsmParser(const std::string &filename) : filename(filename) {};

  bool parse();
  bool searchBBs(std::ifstream &input);
  bool readInstructions(std::ifstream &input);

  const std::vector<Instruction> &getInstructions() const;
};

} // namespace asm2ir
