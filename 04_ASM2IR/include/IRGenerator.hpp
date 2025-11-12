// #pragma once

// #include "bin.h"
// #include "cpu.h"
// #include "llvm/IR/LLVMContext.h"
// #include "llvm/IR/Module.h"

// struct ExtIR {
//   llvm::LLVMContext context;
//   llvm::Module *module;
//   llvm::Function *mainFunc;
//   llvm::GlobalVariable *regFile;
//   llvm::Type *voidType;
//   llvm::Type *int32Type;

//   void buildIR(Binary &Bin);
//   void dumpIR();
//   bool verifyIR();
//   void executeIR(CPU &Cpu);
// };
