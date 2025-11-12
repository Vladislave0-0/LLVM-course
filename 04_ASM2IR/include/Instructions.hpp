#pragma once

#include <cstdint>
#include <string>
#include <unordered_map>

namespace asm2ir {

struct Instruction final {
  enum {
#define ISA(Opcode, Name, SkipArgs, ReadArgs, WriteArgs, Execute, IRGen)       \
  Name = Opcode,
#include "ISA.hpp"
#undef ISA
  };

  uint64_t opcode;
  long long rd;
  long long r1;
  long long r2imm;
  long long r3Imm;
  long long r4Imm;
};

struct InstructionInfo final {
  std::unordered_map<std::string, uint64_t> str2op;
  std::unordered_map<uint64_t, std::string> op2str;

  uint64_t getOpCode(const std::string &instrName) const {
    auto instrRec = str2op.find(instrName);
    if (instrRec == str2op.end())
      return 0;

    return str2op.find(instrName)->second;
  }

  void prepareInfo() {
#define ISA(Opcode, Name, SkipArgs, ReadArgs, WriteArgs, Execute,              \
            IRGenExecute)                                                      \
  str2op[#Name] = Opcode;                                                      \
  op2str[Opcode] = #Name;
#include "ISA.hpp"
#undef ISA
  }
};

} // namespace asm2ir