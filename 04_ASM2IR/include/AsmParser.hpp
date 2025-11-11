#pragma once
#include "Instructions.hpp"
#include <string>
#include <unordered_map>
#include <vector>

namespace asm2ir {

class AsmParser {
  std::string filename;
  std::vector<Instruction> instructions;
  std::unordered_map<std::string, size_t> labels;

  void processLine(const std::string &line, size_t line_number);
  void tokenizeLine(const std::string &line, std::vector<std::string> &tokens);

public:
  AsmParser(const std::string &filename) : filename(filename) {};

  bool parse();

  const std::vector<Instruction> &getInstructions() const;
  const std::unordered_map<std::string, size_t> &getLabels() const;
};

} // namespace asm2ir
