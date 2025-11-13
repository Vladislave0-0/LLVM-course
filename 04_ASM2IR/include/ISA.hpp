// ISA arguments format:
// - Opcode
// - Name
// - SkipArgs: string -> 0 [ifstream InputFile]
// - ReadArgs: string -> args [ifstream InputFile, Instr I, map BBName2PC]
// - WriteArgs: args -> string [stringstream Stream, Instr I, map PC2BBName]
// - Execute: args -> EXECUTION [uint32_t rd, uint32_t r1, uint32_t r2imm, cpu
// *C]
// - IRGenExecute = args -> IR [IRBuilder builder, regFileType regFile, Instr I,
//                            map BBMap, uint32_t PC, GraphicalFuncs]

// ISA(Opcode_, Name_, SkipArgs_, ReadArgs_, WriteArgs_, Execute_,
// IRGenExecute_)

//=================================SkipArgs=====================================
// #include <SDL2/SDL_stdinc.h>
#define SKIP_1ARG                                                              \
  { input >> arg; }

#define SKIP_2ARGS                                                             \
  { input >> arg >> arg; }

#define SKIP_3ARGS                                                             \
  {                                                                            \
    input >> arg;                                                              \
    input >> arg;                                                              \
    input >> arg;                                                              \
  }

#define SKIP_4ARGS                                                             \
  { input >> arg >> arg >> arg >> arg; }

//==============================================================================

//=================================ReadArgs=====================================
#define READ_REG(reg)                                                          \
  {                                                                            \
    input >> arg;                                                              \
    I.reg = std::stoi(arg.substr(1));                                          \
  }

#define READ_TO_R2IMM                                                          \
  {                                                                            \
    input >> arg;                                                              \
    I.r2imm = std::stoi(arg);                                                  \
  }

#define READ_TO_R3IMM                                                          \
  {                                                                            \
    input >> arg;                                                              \
    I.r3imm = std::stoi(arg);                                                  \
  }

#define READ_LABEL_TO_R2IMM                                                    \
  {                                                                            \
    input >> arg;                                                              \
    if (bb2pc.find(arg) == bb2pc.end())                                        \
      return true;                                                             \
                                                                               \
    I.r2imm = bb2pc[arg];                                                      \
  }

#define READ_LABEL_TO_R3IMM                                                    \
  {                                                                            \
    input >> arg;                                                              \
    if (bb2pc.find(arg) == bb2pc.end())                                        \
      return true;                                                             \
                                                                               \
    I.r3imm = bb2pc[arg];                                                      \
  }

#define READ_2REGS {READ_REG(rd) READ_REG(r1)}
#define READ_3REGS {READ_2REGS READ_REG(r2imm)}
#define READ_4REGS {READ_3REGS READ_REG(r3imm)}

#define READ_2REGS_R2IMM                                                       \
  {                                                                            \
    READ_REG(rd) READ_REG(r1);                                                 \
    READ_TO_R2IMM                                                              \
  }
#define READ_3REGS_R3IMM {READ_3REGS READ_TO_R3IMM}

#define READ_REG_LABEL_TO_R2IMM {READ_REG(rd) READ_LABEL_TO_R2IMM}
#define READ_REG_LABEL_TO_R3IMM {READ_REG_LABEL_TO_R2IMM READ_LABEL_TO_R3IMM}

#define READ_REG_R2IMM {READ_REG(rd) READ_TO_R2IMM}
// #define READ_2REGS_R2IMM_REG {READ_2REGS_R2IMM READ_REG(rs3imm)}

//==============================================================================

//=================================WriteArgs=====================================
#define WRITE_REG(reg)                                                         \
  { stream << " x" << I.reg; }

#define WRITE_2IMM                                                             \
  { stream << " " << I.r2imm; }

#define WRITE_3IMM                                                             \
  { stream << " " << I.r3imm; }

#define WRITE_2LABEL                                                           \
  { stream << " " << pc2bb[I.r2imm]; }

#define WRITE_3LABEL                                                           \
  { stream << " " << pc2bb[I.r3imm]; }

#define WRITE_2REGS {WRITE_REG(rd) WRITE_REG(r1)}
#define WRITE_3REGS {WRITE_2REGS WRITE_REG(r2imm)}
#define WRITE_4REGS {WRITE_3REGS WRITE_REG(r3imm)}

#define WRITE_2REGS_IMM {WRITE_2REGS WRITE_2IMM}
#define WRITE_3REGS_IMM {WRITE_3REGS WRITE_3IMM}

#define WRITE_REG_2LABEL {WRITE_REG(rd) WRITE_2LABEL}
#define WRITE_REG_3LABEL {WRITE_REG_2LABEL WRITE_3LABEL}

#define WRITE_REG_IMM {WRITE_REG(rd) WRITE_2IMM}

//==============================================================================

//============================IRGenExecute======================================
#define GEP2_64(arg) builder.CreateConstGEP2_64(regFileType, reg_file, 0, arg)
#define STORE(from_, to_) builder.CreateStore(from_, to_)
#define LOAD_REG(arg) builder.CreateLoad(i64Ty, GEP2_64(arg))
#define GEN_IMM(arg) builder.getInt64(arg)

// ISA(Opcode_, Name_, SkipArgs_, ReadArgs_, WriteArgs_, Execute_,
// IRGenExecute_)

ISA(0x1, EXIT, {}, {}, {}, { cpu->run = false; }, { builder.CreateRetVoid(); })

ISA(
    0x2, ADD, SKIP_3ARGS, READ_3REGS, WRITE_3REGS,
    { cpu->reg_file[rd] = cpu->reg_file[r1] + cpu->reg_file[r2imm]; },
    {
      STORE(builder.CreateAdd(LOAD_REG(I.r1), LOAD_REG(I.r2imm)),
            GEP2_64(I.rd));
    })

ISA(
    0x3, ADDi, SKIP_3ARGS, READ_2REGS_R2IMM, WRITE_2REGS_IMM,
    { cpu->reg_file[rd] = cpu->reg_file[r1] + r2imm; },
    {
      STORE(builder.CreateAdd(LOAD_REG(I.r1), GEN_IMM(I.r2imm)), GEP2_64(I.rd));
    })

ISA(
    0x4, MOV, SKIP_2ARGS, READ_2REGS, WRITE_2REGS,
    { cpu->reg_file[rd] = cpu->reg_file[r1]; },
    { STORE(LOAD_REG(I.r1), GEP2_64(I.rd)); })

ISA(
    0x5, MOVi, SKIP_2ARGS, READ_REG_R2IMM, WRITE_REG_IMM,
    {
      cpu->reg_file[rd] = r2imm;
      // std::cout << "[DEBUG] MOVi: rd = " << r2imm << "\n";
    },
    { STORE(GEN_IMM(I.r2imm), GEP2_64(I.rd)); })

ISA(
    0x6, BR_COND, SKIP_3ARGS, READ_REG_LABEL_TO_R3IMM, WRITE_REG_3LABEL,
    {
      if (cpu->reg_file[rd]) {
        cpu->next_pc = r2imm;
      } else {
        cpu->next_pc = r3imm;
      }
    },
    {
      builder.CreateCondBr(
          builder.CreateTrunc(LOAD_REG(I.rd), builder.getInt1Ty()),
          BBMap[I.r2imm], BBMap[I.r3imm]);
      builder.SetInsertPoint(BBMap[++pc]);
      continue;
    })

ISA(
    0x7, BRANCH, SKIP_1ARG, READ_LABEL_TO_R2IMM, WRITE_2LABEL,
    { cpu->next_pc = r2imm; },
    {
      builder.CreateBr(BBMap[I.r2imm]);
      builder.SetInsertPoint(BBMap[++pc]);
      continue;
    })

ISA(
    0x8, CMP_EQ, SKIP_3ARGS, READ_2REGS_R2IMM, WRITE_2REGS_IMM,
    { cpu->reg_file[rd] = (cpu->reg_file[r1] == r2imm) ? 1 : 0; },
    {
      STORE(builder.CreateZExt(
                builder.CreateICmpEQ(LOAD_REG(I.r1), GEN_IMM(I.r2imm)),
                builder.getInt64Ty()),
            GEP2_64(I.rd));
    })

ISA(
    0x9, ANDi, SKIP_3ARGS, READ_2REGS_R2IMM, WRITE_2REGS_IMM,
    { cpu->reg_file[rd] = cpu->reg_file[r1] & r2imm; },
    {
      STORE(builder.CreateAnd({LOAD_REG(I.r1), GEN_IMM(I.r2imm)}),
            GEP2_64(I.rd));
    })

ISA(
    0xa, SIM_RAND, SKIP_1ARG, READ_REG(rd), WRITE_REG(rd),
    { cpu->reg_file[rd] = simRand(); },
    {
      STORE(
          builder.CreateSExt(builder.CreateCall(simRand), builder.getInt64Ty()),
          GEP2_64(I.rd));
    })

ISA(
    0xb, SCREEN_FLUSH, {}, {}, {}, { simFlush(); },
    { builder.CreateCall(simFlush); })

ISA(
    0xc, SCREEN_PUT_PIXEL, SKIP_3ARGS, READ_3REGS, WRITE_3REGS,
    {
      simPutPixel(cpu->reg_file[rd], cpu->reg_file[r1], cpu->reg_file[r2imm]);
    },
    {
      builder.CreateCall(
          simPutPixel,
          {builder.CreateTrunc(LOAD_REG(I.rd), builder.getInt32Ty()),
           builder.CreateTrunc(LOAD_REG(I.r1), builder.getInt32Ty()),
           builder.CreateTrunc(LOAD_REG(I.r2imm), builder.getInt32Ty())});
    })

ISA(
    0xd, SHL, SKIP_3ARGS, READ_2REGS_R2IMM, WRITE_2REGS_IMM,
    { cpu->reg_file[rd] = cpu->reg_file[r1] << r2imm; },
    {
      STORE(builder.CreateShl(LOAD_REG(I.r1), GEN_IMM(I.r2imm)), GEP2_64(I.rd));
    })

ISA(
    0xe, CMP_LT, SKIP_3ARGS, READ_2REGS_R2IMM, WRITE_2REGS_IMM,
    { cpu->reg_file[rd] = (cpu->reg_file[r1] < r2imm) ? 1 : 0; },
    {
      STORE(builder.CreateZExt(
                builder.CreateICmpSLT(LOAD_REG(I.r1), GEN_IMM(I.r2imm)),
                builder.getInt64Ty()),
            GEP2_64(I.rd));
    })

ISA(
    0xf, DUMP_REG, SKIP_1ARG, READ_REG(rd), WRITE_REG(rd),
    { dumpReg(rd, cpu->reg_file[rd]); },
    { builder.CreateCall(dumpReg, {GEN_IMM(I.rd), LOAD_REG(I.rd)}); })

ISA(
    0xff, DUMP_REGS, SKIP_2ARGS, READ_2REGS, WRITE_2REGS,
    {
      std::cout << "\n[START_DUMP_REGS]\n";
      for (long long i = rd; i <= r1; ++i) {
        dumpReg(i, cpu->reg_file[i]);
      }
      std::cout << "[END_DUMP_REGS]\n\n";
    },
    { 
      // std::cout << "\n[START_DUMP_REGS]\n";
      // for (long long i = rd; i <= r1; ++i) {
      //   builder.CreateCall(dumpReg, {GEN_IMM(I.rd), LOAD_REG(I.rd)});
      // }
      // std::cout << "[END_DUMP_REGS]\n\n";
    })
