#pragma once

#include <cinttypes>
#include <iostream>

extern "C" {
int simRand();
void simPutPixel(int x, int y, int argb);
void simFlush();
}

namespace asm2ir {
struct CPU final {
  static constexpr uint64_t reg_size = 64;
  uint32_t reg_file[reg_size] = {};
  uint32_t pc;
  uint32_t next_pc;
  bool run = true;
  static CPU *cpu;

  void dumpCPU() const;

  static void setCPU(CPU *cpu_) { cpu = cpu_; }

#define ISA(Opcode, Name, SkipArgs, ReadArgs, WriteArgs, Execute,              \
            IRGenExecute)                                                      \
  static void do_##Name(long long rd, long long r1, long long r2imm,           \
                        long long r3imm) {                                     \
    Execute;                                                                   \
  }
#include "ISA.hpp"
#undef ISA
};
} // namespace asm2ir
