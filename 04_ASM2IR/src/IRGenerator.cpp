// src/IRGenerator.cpp
#include "../include/IRGenerator.hpp"
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Verifier.h>
#include <llvm/Support/raw_ostream.h>

using namespace llvm;

namespace asm2ir {

IRGenerator::IRGenerator() {
  context = new LLVMContext();
  module = new Module("asm_program", *context);

  // Создаём функцию app.
  FunctionType *funcType = FunctionType::get(Type::getVoidTy(*context), false);
  mainFunction =
      Function::Create(funcType, Function::ExternalLinkage, "app", module);

  // Первый базовый блок.
  currentBB = BasicBlock::Create(*context, "entry", mainFunction);

  ArrayType *regArrayType = ArrayType::get(Type::getInt32Ty(*context), 32);
  Value *regArray = new AllocaInst(regArrayType, 0, "registers", currentBB);

  // Инициализируем регистры нулями.
  IRBuilder<> builder(currentBB);
  Value *zero = ConstantInt::get(Type::getInt32Ty(*context), 0);

  for (int i = 0; i < 32; ++i) {
    Value *idxs[] = {ConstantInt::get(Type::getInt64Ty(*context), 0),
                     ConstantInt::get(Type::getInt64Ty(*context), i)};
    Value *ptr = builder.CreateGEP(regArrayType, regArray, idxs, "reg_ptr");
    builder.CreateStore(zero, ptr);
  }

  // Заполнить вектор регистров
  for (int i = 0; i < 32; ++i) {
    Value *idxs[] = {ConstantInt::get(Type::getInt64Ty(*context), 0),
                     ConstantInt::get(Type::getInt64Ty(*context), i)};
    Value *ptr = builder.CreateGEP(regArrayType, regArray, idxs, "reg_ptr");
    registers.push_back(ptr);
  }
}

IRGenerator::~IRGenerator() {
  delete module;
  delete context;
}

void IRGenerator::generate(
    const std::vector<Instruction> &instructions,
    const std::unordered_map<std::string, size_t> &labels) {
  IRBuilder<> builder(currentBB);

  // Создадим базовые блоки для всех меток.
  for (const auto &label : labels) {
    std::string blockName = "label_" + label.first;
    BasicBlock *bb = BasicBlock::Create(*context, blockName, mainFunction);
    labelBlocks[label.first] = bb;
  }

  // Генерируем код для каждоый инструкции.
  for (const auto &instr : instructions) {
    if (instr.opcode == "ADD") {
      generateAdd(instr);
    } else if (instr.opcode == "ADDi") {
      generateAddi(instr);
    } else if (instr.opcode == "MOV") {
      generateMov(instr);
    } else if (instr.opcode == "MOVi") {
      generateMov(instr);
    } else if (instr.opcode == "BRANCH") {
      generateBranch(instr);
      // После безусловного перехода создаем новый базовый блок
      currentBB = BasicBlock::Create(*context, "after_branch", mainFunction);
      builder.SetInsertPoint(currentBB);
    } else if (instr.opcode == "BR_COND") {
      generateBrCond(instr);
      // После условного перехода создаем новый базовый блок
      currentBB = BasicBlock::Create(*context, "after_br_cond", mainFunction);
      builder.SetInsertPoint(currentBB);
    }

    // Здесь будут другие инструкции
  }

  if (!currentBB->getTerminator())
    builder.CreateRetVoid();

  verifyModule(*module, &errs());
}

Value *IRGenerator::getOperandValue(const Operand &operand) {
  IRBuilder<> builder(currentBB);

  if (operand.type == OperandType::REGISTER) {
    int regNum = std::stoi(operand.value);
    if (regNum >= 0 && regNum < 32) {
      Value *regPtr = registers[regNum];
      return builder.CreateLoad(Type::getInt32Ty(*context), regPtr);
    }
  } else if (operand.type == OperandType::IMMEDIATE) {
    int32_t immValue = parseImmediate(operand.value);
    return ConstantInt::get(Type::getInt32Ty(*context), immValue);
  }

  return ConstantInt::get(Type::getInt32Ty(*context), 0);
}

int32_t IRGenerator::parseImmediate(const std::string &value) {
  try {
    return std::stoi(value);
  } catch (...) {
    return 0;
  }
}

void IRGenerator::generateAdd(const Instruction &instr) {
  if (instr.operands.size() < 3)
    return;

  IRBuilder<> builder(currentBB);

  Value *src1 = getOperandValue(instr.operands[1]);
  Value *src2 = getOperandValue(instr.operands[2]);
  Value *result = builder.CreateAdd(src1, src2, "add_result");

  int dstReg = std::stoi(instr.operands[0].value);
  if (dstReg >= 0 && dstReg < 32) {
    builder.CreateStore(result, registers[dstReg]);
  }
}

void IRGenerator::generateAddi(const Instruction &instr) {
  if (instr.operands.size() < 3)
    return;

  IRBuilder<> builder(currentBB);

  Value *src = getOperandValue(instr.operands[1]);
  Value *imm = getOperandValue(instr.operands[2]);
  Value *result = builder.CreateAdd(src, imm, "addi_result");

  int dstReg = std::stoi(instr.operands[0].value);
  if (dstReg >= 0 && dstReg < 32) {
    builder.CreateStore(result, registers[dstReg]);
  }
}

void IRGenerator::generateMov(const Instruction &instr) {
  if (instr.operands.size() < 2)
    return;

  IRBuilder<> builder(currentBB);

  Value *src = getOperandValue(instr.operands[1]);

  int dstReg = std::stoi(instr.operands[0].value);
  if (dstReg >= 0 && dstReg < 32) {
    builder.CreateStore(src, registers[dstReg]);
  }
}

void IRGenerator::generateBranch(const Instruction &instr) {
  if (instr.operands.empty())
    return;

  IRBuilder<> builder(currentBB);

  std::string labelName = instr.operands[0].value;
  auto it = labelBlocks.find(labelName);
  if (it != labelBlocks.end()) {
    builder.CreateBr(it->second);
  }
}

void IRGenerator::generateBrCond(const Instruction &instr) {
  if (instr.operands.size() < 3)
    return;

  IRBuilder<> builder(currentBB);

  Value *cond = getOperandValue(instr.operands[0]);
  cond = builder.CreateICmpNE(
      cond, ConstantInt::get(Type::getInt32Ty(*context), 0), "to_bool");

  std::string trueLabel = instr.operands[1].value;
  std::string falseLabel = instr.operands[2].value;

  BasicBlock *trueBB = labelBlocks[trueLabel];
  BasicBlock *falseBB = labelBlocks[falseLabel];

  builder.CreateCondBr(cond, trueBB, falseBB);
}

void IRGenerator::writeToFile(const std::string &filename) {
  std::error_code EC;
  raw_fd_ostream dest(filename, EC);

  if (EC) {
    errs() << "Error opening file: " << EC.message() << "\n";
    return;
  }

  module->print(dest, nullptr);
  dest.flush();
}

} // namespace asm2ir