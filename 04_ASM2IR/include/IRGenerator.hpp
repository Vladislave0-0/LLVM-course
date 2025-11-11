#pragma once
#include "Instructions.hpp"
#include <string>
#include <unordered_map>

namespace llvm {
class LLVMContext;
class Module;
class Function;
class BasicBlock;
class Value;
} // namespace llvm

namespace asm2ir {

class IRGenerator {
  llvm::LLVMContext *context;
  llvm::Module *module;

  llvm::BasicBlock *currentBB;
  llvm::Function *mainFunction;

  std::vector<llvm::Value *> registers;

  // Маппинг меток на базовые блоки.
  std::unordered_map<std::string, llvm::BasicBlock *> labelBlocks;

  void generateAdd(const Instruction &instr);
  void generateAddi(const Instruction &instr);
  void generateMov(const Instruction &instr);
  void generateBranch(const Instruction &instr);
  void generateBrCond(const Instruction &instr);

  // Вспомогательные функции
  llvm::Value *getOperandValue(const Operand &operand);
  int32_t parseImmediate(const std::string &value);

public:
  IRGenerator();
  ~IRGenerator();

  void generate(const std::vector<Instruction> &instructions,
                const std::unordered_map<std::string, size_t> &labels);

  void writeToFile(const std::string &filename);
};

} // namespace asm2ir
