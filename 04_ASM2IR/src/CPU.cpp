#include "../include/CPU.hpp"
#include <iostream>

namespace asm2ir {

CPU *CPU::cpu;

void CPU::dumpCPU() const {
  std::cout << "pc: " << std::hex << pc << '\n';
  std::cout << "next_pc: " << next_pc << '\n';

  for (uint32_t reg = 0; reg < reg_size; ++reg)
    std::cout << "x" << reg << ": " << reg_file[reg] << '\n';

  std::cout << '\n';
}

} // namespace asm2ir
