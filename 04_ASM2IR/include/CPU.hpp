#pragma once

#include <cstdint>

extern "C" {
int simRand();
void simPutPixel(int x, int y, int argb);
void simFlush();
}

namespace asm2ir {

struct CPU final {
  static constexpr uint64_t reg_size = 64;
  int64_t reg_file[reg_size] = {};
  uint32_t pc;
  uint32_t next_pc;
  bool run = true;
  static CPU *cpu;

  void dumpCPU() const;

  static void setCPU(CPU *cpu_) { cpu = cpu_; }

#define ISA(Opcode, Name, SkipArgs, ReadArgs, WriteArgs, Execute,              \
            IRGenExecute)                                                      \
  static void do_##Name(int64_t rd, int64_t r1, int64_t r2imm,                 \
                        int64_t r3imm) {                                       \
    Execute;                                                                   \
  }
#include "ISA.hpp"
#undef ISA
};

} // namespace asm2ir
