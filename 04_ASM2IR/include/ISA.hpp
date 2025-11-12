// ISA arguments format:
// - Opcode
// - Name
// - SkipArgs: string -> 0 [ifstream InputFile]
// - ReadArgs: string -> args [ifstream InputFile, Instr I, map BBName2PC]
// - WriteArgs: args -> string [stringstream Stream, Instr I, map PC2BBName]
// - Execute: args -> EXECUTION [uint32_t rd, uint32_t r1, uint32_t r2imm, CPU
// *C]
// - IRGenExecute = args -> IR [IRBuilder builder, regFileType regFile, Instr I,
//                            map BBMap, uint32_t PC, GraphicalFuncs]

// ISA(Opcode_, Name_, SkipArgs_, ReadArgs_, WriteArgs_, Execute_,
// IRGenExecute_)

//=================================SkipArgs=====================================
#define SKIP_3ARGS                                                             \
  { input >> arg >> arg >> arg; }

#define SKIP_2ARGS                                                             \
  { input >> arg >> arg; }

#define SKIP_1ARGS                                                             \
  { input >> arg; }
//==============================================================================

//=================================ReadArgs=====================================
#define READ_REG(Reg)                                                          \
  {                                                                            \
    input >> arg;                                                              \
    I.Reg = std::stoi(arg.substr(1));                                          \
  }

#define READ_IMM                                                               \
  {                                                                            \
    input >> arg;                                                              \
    I.r2imm = std::stoi(arg);                                                  \
  }

#define READ_LABEL                                                             \
  {                                                                            \
    input >> arg;                                                              \
    std::cout << "<label>: arg = " << arg << std::endl;                        \
    if (bb2pc.find(arg) == bb2pc.end())                                        \
      return true;                                                             \
                                                                               \
    std::cout << "r2imm = " << bb2pc[arg] << '\n';                             \
    I.r2imm = bb2pc[arg];                                                      \
  }

#define READ_3REGS {READ_REG(rd) READ_REG(r1) READ_REG(r2imm)}
#define READ_2REGS_IMM {READ_REG(rd) READ_REG(r1) READ_IMM}
#define READ_2REGS {READ_REG(rd) READ_REG(r1)}
#define READ_REG_LABEL {READ_REG(rd) READ_LABEL}
#define READ_REG_IMM {READ_REG(rd) READ_IMM}
//==============================================================================

//=================================WriteArgs=====================================
#define WRITE_REG(Reg)                                                         \
  { stream << " x" << I.Reg; }

#define WRITE_IMM                                                              \
  { stream << " " << I.r2imm; }

#define WRITE_LABEL                                                            \
  { stream << " " << pc2bb[I.r2imm]; }

#define WRITE_3REGS {WRITE_REG(rd) WRITE_REG(r1) WRITE_REG(r2imm)}
#define WRITE_2REGS_IMM {WRITE_REG(rd) WRITE_REG(r1) WRITE_IMM}
#define WRITE_2REGS {WRITE_REG(rd) WRITE_REG(r1)}
#define WRITE_REG_LABEL {WRITE_REG(rd) WRITE_LABEL}
#define WRITE_REG_IMM {WRITE_REG(rd) WRITE_IMM}
//==============================================================================

//============================IRGenExecute_=====================================
#define GEP2_32(arg) builder.CreateConstGEP2_32(regFileType, regFile, 0, arg)
#define LOAD_REG(arg) builder.CreateLoad(int32Type, GEP2_32(arg))
#define GEN_IMM(arg) builder.getInt32(arg)

// ISA(Opcode_, Name_, SkipArgs_, ReadArgs_, WriteArgs_, Execute_,
// IRGenExecute_)

ISA(0x1, EXIT, {}, {}, {}, { CPU->run = false; }, { builder.CreateRetVoid(); })

ISA(
    0x2, ADD, SKIP_3ARGS, READ_3REGS, WRITE_3REGS,
    { CPU->reg_file[rd] = CPU->reg_file[r1] + CPU->reg_file[r2imm]; },
    {
      builder.CreateStore(builder.CreateAdd(LOAD_REG(I.r1), LOAD_REG(I.r2imm)),
                          GEP2_32(I.rd));
    })

ISA(
    0x3, MOVi, SKIP_2ARGS, READ_REG_IMM, WRITE_REG_IMM,
    { CPU->reg_file[rd] = r2imm; },
    { builder.CreateStore(GEN_IMM(I.r2imm), GEP2_32(I.rd)); })

ISA(
    0x4, BR_COND, SKIP_2ARGS, READ_REG_LABEL, WRITE_REG_LABEL,
    {
      if (CPU->reg_file[rd]) {
        CPU->next_pc = r2imm;
      }
    },
    {
      ++PC;
      builder.CreateCondBr(
          builder.CreateTrunc(LOAD_REG(I.rd), builder.getInt1Ty()),
          BBMap[I.r2imm], BBMap[PC]);
      builder.SetInsertPoint(BBMap[PC]);
      continue;
    })

ISA(
    0x5, BRANCH, SKIP_1ARGS, READ_LABEL, WRITE_LABEL, { CPU->next_pc = r2imm; },
    {
      ++PC;
      builder.CreateBr(BBMap[I.r2imm]);
      builder.SetInsertPoint(BBMap[PC]);
      continue;
    })
