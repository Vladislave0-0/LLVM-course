// ISA arguments format:
// - Opcode
// - Name
// - SkipArgs: string -> 0 [ifstream InputFile]
// - ReadArgs: string -> args [ifstream InputFile, Instr I, map BBName2PC]
// - WriteArgs: args -> string [stringstream Stream, Instr I, map PC2BBName]
// - Execute: args -> EXECUTION [uint32_t rd, uint32_t r1, uint32_t r2imm, cpu
// *C]
// - IRGenExecute = args -> IR [IRBuilder builder, regFileTy regFile, Instr I,
//                            map BBMap, uint32_t PC, GraphicalFuncs]

// ISA(Opcode_, Name_, SkipArgs_, ReadArgs_, WriteArgs_, Execute_,
// IRGenExecute_)

#define SIM_X_SIZE 512
#define SIM_Y_SIZE 512
#define I32_SIZE 4

//=================================SkipArgs=====================================
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
                                                                               \
    if (bb2pc.find(arg) == bb2pc.end())                                        \
      return true;                                                             \
                                                                               \
    I.r2imm = bb2pc[arg];                                                      \
  }

#define READ_LABEL_TO_R3IMM                                                    \
  {                                                                            \
    input >> arg;                                                              \
                                                                               \
    if (bb2pc.find(arg) == bb2pc.end())                                        \
      return true;                                                             \
                                                                               \
    I.r3imm = bb2pc[arg];                                                      \
  }

#define READ_2REGS {READ_REG(rd) READ_REG(r1)}
#define READ_3REGS {READ_2REGS READ_REG(r2imm)}
#define READ_4REGS {READ_3REGS READ_REG(r3imm)}

#define READ_2REGS_R2IMM {READ_REG(rd) READ_REG(r1) READ_TO_R2IMM}
#define READ_3REGS_R3IMM {READ_3REGS READ_TO_R3IMM}

#define READ_REG_LABEL {READ_REG(rd) READ_LABEL_TO_R2IMM}
#define READ_REG_2LABELS {READ_REG_LABEL READ_LABEL_TO_R3IMM}

#define READ_REG_R2IMM {READ_REG(rd) READ_TO_R2IMM}
// #define READ_2REGS_R2IMM_REG {READ_2REGS_R2IMM READ_REG(rs3imm)}

//==============================================================================

//=================================WriteArgs=====================================
#define WRITE_REG(reg)                                                         \
  { stream << " x" << I.reg; }

// #define WRITE_R2IMM                                                             \
//   { stream << " " << I.r2imm; }

// #define WRITE_R3IMM                                                             \
//   { stream << " " << I.r3imm; }

#define WRITE_LABEL_TO_R2IMM                                                   \
  { stream << " " << pc2bb[I.r2imm]; }

#define WRITE_LABEL_TO_R3IMM                                                   \
  { stream << " " << pc2bb[I.r3imm]; }

#define WRITE_2REGS {WRITE_REG(rd) WRITE_REG(r1)}
#define WRITE_3REGS {WRITE_2REGS WRITE_REG(r2imm)}
#define WRITE_4REGS {WRITE_3REGS WRITE_REG(r3imm)}

#define WRITE_2REGS_R2IMM {WRITE_3REGS}

#define WRITE_REG_LABEL {WRITE_REG(rd) WRITE_LABEL_TO_R2IMM}
#define WRITE_REG_2LABELS {WRITE_REG_LABEL WRITE_LABEL_TO_R3IMM}

//==============================================================================

//============================IRGenExecute======================================
#define GEP2_64(arg) builder.CreateConstGEP2_64(regFileTy, reg_file, 0, arg)
#define STORE(from_, to_) builder.CreateStore(from_, to_)
#define LOAD_REG(arg) builder.CreateLoad(i64Ty, GEP2_64(arg))
#define LOAD_PTR(arg) builder.CreateLoad(i32PtrTy, GEP2_64(arg))
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
    0x3, ADDi, SKIP_3ARGS, READ_2REGS_R2IMM, WRITE_2REGS_R2IMM,
    { cpu->reg_file[rd] = cpu->reg_file[r1] + r2imm; },
    {
      STORE(builder.CreateAdd(LOAD_REG(I.r1), GEN_IMM(I.r2imm)), GEP2_64(I.rd));
    })

ISA(
    0x4, MOV, SKIP_2ARGS, READ_2REGS, WRITE_2REGS,
    { cpu->reg_file[rd] = cpu->reg_file[r1]; },
    { STORE(LOAD_REG(I.r1), GEP2_64(I.rd)); })

ISA(
    0x5, MOVi, SKIP_2ARGS, READ_REG_R2IMM, WRITE_2REGS,
    { cpu->reg_file[rd] = r2imm; }, { STORE(GEN_IMM(I.r2imm), GEP2_64(I.rd)); })

ISA(
    0x6, BR_COND, SKIP_3ARGS, READ_REG_2LABELS, WRITE_REG_2LABELS,
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
    0x7, BRANCH, SKIP_1ARG, READ_LABEL_TO_R2IMM, WRITE_LABEL_TO_R2IMM,
    { cpu->next_pc = r2imm; },
    {
      builder.CreateBr(BBMap[I.r2imm]);
      builder.SetInsertPoint(BBMap[++pc]);
      continue;
    })

ISA(
    0x8, CMP_EQ, SKIP_3ARGS, READ_2REGS_R2IMM, WRITE_2REGS_R2IMM,
    { cpu->reg_file[rd] = (cpu->reg_file[r1] == r2imm) ? 1 : 0; },
    {
      STORE(builder.CreateZExt(
                builder.CreateICmpEQ(LOAD_REG(I.r1), GEN_IMM(I.r2imm)),
                builder.getInt64Ty()),
            GEP2_64(I.rd));
    })

ISA(
    0x9, ANDi, SKIP_3ARGS, READ_2REGS_R2IMM, WRITE_2REGS_R2IMM,
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
    0xc, SCREEN_PUT_PIXEL, SKIP_3ARGS, READ_3REGS, WRITE_2REGS_R2IMM,
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
    0xd, SHL, SKIP_3ARGS, READ_2REGS_R2IMM, WRITE_2REGS_R2IMM,
    { cpu->reg_file[rd] = cpu->reg_file[r1] << r2imm; },
    {
      STORE(builder.CreateShl(LOAD_REG(I.r1), GEN_IMM(I.r2imm)), GEP2_64(I.rd));
    })

ISA(
    0xe, CMP_LT, SKIP_3ARGS, READ_2REGS_R2IMM, WRITE_2REGS_R2IMM,
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

ISA(0x10, DUMP_REGS, SKIP_2ARGS, READ_2REGS, WRITE_2REGS,
    {
      std::cout << "\n[START_DUMP_REGS]\n";
      for (long long i = rd; i <= r1; ++i) {
        dumpReg(i, cpu->reg_file[i]);
      }
      std::cout << "[END_DUMP_REGS]\n\n";
    },
    {})

ISA(
    0x11, INC_EQ, SKIP_3ARGS, READ_2REGS_R2IMM, WRITE_2REGS_R2IMM,
    {
      ++cpu->reg_file[r1];
      cpu->reg_file[rd] = (cpu->reg_file[r1] == r2imm) ? 1 : 0;
    },
    {
      STORE(builder.CreateAdd(LOAD_REG(I.r1), builder.getInt64(1)),
            GEP2_64(I.r1));
      STORE(builder.CreateZExt(
                builder.CreateICmpEQ(LOAD_REG(I.r1), GEN_IMM(I.r2imm)),
                builder.getInt64Ty()),
            GEP2_64(I.rd));
    })

ISA(
    0x12, ALGR, SKIP_1ARG, READ_REG(rd), WRITE_REG(rd),
    {
      cpu->reg_file[rd] =
          reinterpret_cast<uint64_t>(new uint32_t[SIM_X_SIZE * SIM_Y_SIZE]);
    },
    {
      ArrayType *arrTy = ArrayType::get(
          ArrayType::get(IntegerType::get(context, 32), SIM_X_SIZE),
          SIM_Y_SIZE);
      STORE(builder.CreateAlloca(arrTy), GEP2_64(I.rd));
    })

ISA(
    0x13, MEMSET, SKIP_1ARG, READ_REG(rd), WRITE_REG(rd),
    {
      ::memset((void *)cpu->reg_file[rd], 0,
               SIM_X_SIZE * SIM_Y_SIZE * I32_SIZE);
    },
    {
      builder.CreateMemSet(LOAD_PTR(I.rd), builder.getInt8(0),
                           builder.getInt64(SIM_X_SIZE * SIM_Y_SIZE * I32_SIZE),
                           MaybeAlign(16));
    })

ISA(
    0x14, MEMCPY, SKIP_2ARGS, READ_2REGS, WRITE_2REGS,
    {
      ::memcpy((void *)cpu->reg_file[rd], (void *)cpu->reg_file[r1],
               SIM_X_SIZE * SIM_Y_SIZE * I32_SIZE);
    },
    {
      builder.CreateMemCpy(
          LOAD_PTR(I.rd), MaybeAlign(16), LOAD_PTR(I.r1), MaybeAlign(16),
          builder.getInt64(SIM_X_SIZE * SIM_Y_SIZE * I32_SIZE));
    })

ISA(
    0x15, DUMP_GRID, SKIP_1ARG, READ_REG(rd), WRITE_REG(rd),
    { dumpGrid((int *)cpu->reg_file[rd]); },
    { builder.CreateCall(dumpGrid, {LOAD_PTR(I.rd)}); })

ISA(0x16, LT_START, SKIP_1ARG, READ_REG(rd), WRITE_REG(rd), {},
    { builder.CreateLifetimeStart(LOAD_PTR(I.rd)); })

ISA(0x17, LT_END, SKIP_1ARG, READ_REG(rd), WRITE_REG(rd), {},
    { builder.CreateLifetimeEnd(LOAD_PTR(I.rd)); })

ISA(
    0x18, SET_CELL, SKIP_4ARGS, READ_4REGS, WRITE_4REGS,
    {
      ((uint32_t *)cpu->reg_file[rd])[SIM_Y_SIZE * cpu->reg_file[r1] +
                                      cpu->reg_file[r2imm]] =
          cpu->reg_file[r3imm];
    },
    {
      ArrayType *gridTy = ArrayType::get(
          ArrayType::get(IntegerType::get(context, 32), SIM_Y_SIZE),
          SIM_X_SIZE);
      STORE(builder.CreateTrunc(LOAD_REG(I.r3imm), builder.getInt32Ty()),
            builder.CreateInBoundsGEP(
                gridTy, LOAD_PTR(I.rd),
                {builder.getInt64(0), LOAD_REG(I.r1), LOAD_REG(I.r2imm)}));
    })

ISA(
    0x19, GET_CELL, SKIP_4ARGS, READ_4REGS, WRITE_4REGS,
    {
      cpu->reg_file[r3imm] =
          ((uint32_t *)cpu->reg_file[rd])[SIM_Y_SIZE * cpu->reg_file[r1] +
                                          cpu->reg_file[r2imm]];
    },
    {
      ArrayType *gridTy = ArrayType::get(
          ArrayType::get(IntegerType::get(context, 32), SIM_Y_SIZE),
          SIM_X_SIZE);
      STORE(builder.CreateSExt(
                builder.CreateLoad(builder.getInt32Ty(),
                                   builder.CreateInBoundsGEP(
                                       gridTy, LOAD_PTR(I.rd),
                                       {builder.getInt64(0), LOAD_REG(I.r1),
                                        LOAD_REG(I.r2imm)})),
                builder.getInt64Ty()),
            GEP2_64(I.r3imm));
    })

ISA(
    0x1a, AND, SKIP_3ARGS, READ_3REGS, WRITE_3REGS,
    { cpu->reg_file[rd] = cpu->reg_file[r1] & cpu->reg_file[r2imm]; },
    {
      STORE(builder.CreateAnd({LOAD_REG(I.r1), LOAD_REG(I.r2imm)}),
            GEP2_64(I.rd));
    })

ISA(
    0x1b, OR, SKIP_3ARGS, READ_3REGS, WRITE_3REGS,
    { cpu->reg_file[rd] = cpu->reg_file[r1] | cpu->reg_file[r2imm]; },
    {
      STORE(builder.CreateOr({LOAD_REG(I.r1), LOAD_REG(I.r2imm)}),
            GEP2_64(I.rd));
    })

ISA(
    0x1c, CMP_GE, SKIP_3ARGS, READ_2REGS_R2IMM, WRITE_2REGS_R2IMM,
    { cpu->reg_file[rd] = (cpu->reg_file[r1] >= r2imm) ? 1 : 0; },
    {
      STORE(builder.CreateZExt(
                builder.CreateICmpSGE(LOAD_REG(I.r1), GEN_IMM(I.r2imm)),
                builder.getInt64Ty()),
            GEP2_64(I.rd));
    })
