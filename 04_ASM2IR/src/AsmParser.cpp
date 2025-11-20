#include "../include/AsmParser.hpp"

#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <sstream>

namespace asm2ir {

// Удаление пробелов в начале и конце строки.
static inline void trim(std::string &s) {
  s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
            return !std::isspace(ch);
          }));
  s.erase(std::find_if(s.rbegin(), s.rend(),
                       [](unsigned char ch) { return !std::isspace(ch); })
              .base(),
          s.end());
}

// Удаление комментариев.
static inline std::string removeComments(const std::string &line) {
  size_t commentPos = line.find(';');

  if (commentPos != std::string::npos)
    return line.substr(0, commentPos);

  return line;
}

static std::vector<std::string>
readAndFilterTokens(const std::string &filename) {
  std::ifstream file{filename};
  std::vector<std::string> tokens;

  if (!file.is_open())
    return tokens;

  std::string line;
  while (std::getline(file, line)) {
    line = removeComments(line);
    trim(line);

    // Пропуск пустых строк.
    if (line.empty())
      continue;

    // Разбиваем строку на токены.
    std::istringstream iss(line);
    std::string token;
    while (iss >> token)
      tokens.push_back(token);
  }

  return tokens;
}

bool AsmParser::parse() {
  auto tokens = readAndFilterTokens(filename);

  if (tokens.empty()) {
    std::cout << "Can't open or file is empty: " + filename << std::endl;
    return false;
  }

  instrs_info.prepareInfo();

  std::stringstream tokenStream;
  for (const auto &token : tokens)
    tokenStream << token << " ";

  if (!searchBBs(tokenStream))
    return false;

  // Сброс потока и возврат каретки.
  tokenStream.clear();
  tokenStream.seekg(0);

  if (!readInstructions(tokenStream))
    return false;

  return true;
}

bool AsmParser::searchBBs(std::istream &input) {
  std::string name;
  std::string arg;

  uint64_t pc = 0;
  uint64_t opcode = 0;

  while (input >> name) {
    opcode = instrs_info.getOpCode(name);

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

bool AsmParser::readInstructions(std::istream &input) {
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
