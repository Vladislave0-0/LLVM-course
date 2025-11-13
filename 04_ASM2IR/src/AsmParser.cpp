#include "../include/AsmParser.hpp"
#include "../include/Instructions.hpp"

#include <fstream>
#include <iostream>

namespace asm2ir {
bool AsmParser::parse() {
  std::ifstream file{filename};

  if (!file.is_open()) {
    std::cout << std::string("Can't open " + filename) << std::endl;
    return false;
  }

  instrs_info.prepareInfo();

  if (!searchBBs(file))
    return false;

  // Возврат каретки.
  file.clear();
  file.seekg(0, std::ios::beg);

  if (!readInstructions(file))
    return false;

  return true;
}

bool AsmParser::searchBBs(std::ifstream &input) {
  std::string name;
  std::string arg;

  uint64_t pc = 0;
  uint64_t opcode = 0;

  while (input >> name) {
    opcode = instrs_info.getOpCode(name);

    // std::cout << "[DEBUG] Processing instruction: " << name << std::endl;

    switch (opcode) {
    default:
      if (bb2pc.find(name) != bb2pc.end()) {
        std::cout << std::string("Repetition of label: " + name);
        return false;
      }

      if (pc2bb.find(pc) != pc2bb.end()) {
        std::cout << std::string("2 labels can't be on the one PC: " + name +
                                 " and " + pc2bb[pc]);
        return false;
      }

      bb2pc[name] = pc;
      basic_blocks.emplace_back(name);
      pc2bb[pc] = name;

      continue;

#define ISA(Opcode, Name, SkipArgs, ReadArgs, WriteArgs, Execute,              \
            IRGenExecute)                                                      \
  case (Opcode):                                                               \
    SkipArgs;                                                                  \
    break;
#include "../include/ISA.hpp"
#undef ISA
    }

    ++pc;
  }

  return true;
}

bool AsmParser::readInstructions(std::ifstream &input) {
  std::string name;
  std::string arg;

  uint64_t opcode = 0;

  while (input >> name) {
    opcode = instrs_info.getOpCode(name);
    Instruction I;
    I.opcode = opcode;

    switch (opcode) {
    default:
      if (bb2pc.find(name) != bb2pc.end())
        continue;

      std::cout << std::string("Wrong Opcode for " + name);
      return false;

#define ISA(Opcode, Name, SkipArgs, ReadArgs, WriteArgs, Execute,              \
            IRGenExecute)                                                      \
  case (Opcode):                                                               \
    ReadArgs;                                                                  \
    break;
#include "../include/ISA.hpp"
#undef ISA
    }

    instructions.push_back(I);
  }

  return true;
}

} // namespace asm2ir
