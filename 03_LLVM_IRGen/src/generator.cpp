#include "../include/generator.hpp"

#include <llvm/ExecutionEngine/ExecutionEngine.h>
#include <llvm/ExecutionEngine/GenericValue.h>
#include <llvm/IR/Verifier.h>
#include <llvm/Transforms/Utils/Cloning.h>
#include <memory>

extern "C" {
void simInit();
void simExit();
void simFlush();
void simPutPixel(int, int, int);
int simRand();
}

namespace LLVM_IRGen {
llvm::Function *Generator::printSimPutPixel() {
  auto *voidTy = llvm::Type::getVoidTy(context);
  auto *i32 = llvm::Type::getInt32Ty(context);
  auto *funcTy = llvm::FunctionType::get(voidTy, {i32, i32, i32}, false);

  return llvm::Function::Create(funcTy, llvm::GlobalValue::ExternalLinkage,
                                simPutPixelName, *IRModule);
}

llvm::Function *Generator::printSimFlush() {
  auto *voidTy = llvm::Type::getVoidTy(context);
  auto *funcTy = llvm::FunctionType::get(voidTy, {}, false);

  return llvm::Function::Create(funcTy, llvm::GlobalValue::ExternalLinkage,
                                simFlushName, *IRModule);
}

llvm::Function *Generator::printSimRand() {
  auto *i32 = llvm::Type::getInt32Ty(context);
  auto *funcTy = llvm::FunctionType::get(i32, {}, false);

  return llvm::Function::Create(funcTy, llvm::GlobalValue::ExternalLinkage,
                                simRandName, *IRModule);
}

bool Generator::verifyModule_() {
  bool status = verifyModule(*IRModule, &outs());

  outs() << "[VERIFICATION STATUS] ";
  if (!status)
    return outs() << "Passed\n\n", true;

  return outs() << "Failed\n\n", false;
}

void Generator::dump(const std::string &filename) {
  std::error_code error;
  llvm::raw_fd_ostream OS(filename, error);

  if (error)
    return;

  IRModule->print(OS, nullptr);
}

void Generator::interpretation() {
  std::unique_ptr<Module> executionModule = CloneModule(*IRModule);
  auto *app = executionModule->getFunction(appName);

  LLVMInitializeNativeTarget();
  LLVMInitializeNativeAsmPrinter();

  ExecutionEngine *ee = EngineBuilder(std::move(executionModule)).create();

  ee->InstallLazyFunctionCreator([&](const std::string &fnName) -> void * {
    if (fnName == simFlushName) {
      return reinterpret_cast<void *>(simFlush);
    } else if (fnName == simRandName) {
      return reinterpret_cast<void *>(simRand);
    } else if (fnName == simPutPixelName) {
      return reinterpret_cast<void *>(simPutPixel);
    }
    return nullptr;
  });

  ee->finalizeObject();

  simInit();

  ArrayRef<GenericValue> NoArgs;
  GenericValue value = ee->runFunction(app, NoArgs);

  simExit();
}

void Generator::generation() {
  // Usable types.
  auto *i32 = llvm::Type::getInt32Ty(context);
  auto *i64 = llvm::Type::getInt64Ty(context);
  auto *voidTy = llvm::Type::getVoidTy(context);
  auto *rowTy = llvm::ArrayType::get(i32, 32);    // [32 x i32]
  auto *gridTy = llvm::ArrayType::get(rowTy, 32); // [32 x [32 x i32]]

  // Creating function app().
  auto *funcTy = llvm::FunctionType::get(voidTy, false);
  auto *appFunc = llvm::Function::Create(
      funcTy, llvm::GlobalValue::ExternalLinkage, appName, *IRModule);

  // All functions declaration.
  auto *simRand = printSimRand();
  auto *simPutPixel = printSimPutPixel();
  auto *simFlush = printSimFlush();

  // All basic block in app.ll.
  auto *BB0 = llvm::BasicBlock::Create(context, "", appFunc);
  auto *BB3 = llvm::BasicBlock::Create(context, "", appFunc);
  auto *BB5 = llvm::BasicBlock::Create(context, "", appFunc);
  auto *BB8 = llvm::BasicBlock::Create(context, "", appFunc);
  auto *BB15 = llvm::BasicBlock::Create(context, "", appFunc);
  auto *BB17 = llvm::BasicBlock::Create(context, "", appFunc);
  auto *BB18 = llvm::BasicBlock::Create(context, "", appFunc);
  auto *BB21 = llvm::BasicBlock::Create(context, "", appFunc);
  auto *BB24 = llvm::BasicBlock::Create(context, "", appFunc);
  auto *BB25 = llvm::BasicBlock::Create(context, "", appFunc);
  auto *BB28 = llvm::BasicBlock::Create(context, "", appFunc);
  auto *BB34 = llvm::BasicBlock::Create(context, "", appFunc);
  auto *BB37 = llvm::BasicBlock::Create(context, "", appFunc);
  auto *BB42 = llvm::BasicBlock::Create(context, "", appFunc);
  auto *BB49 = llvm::BasicBlock::Create(context, "", appFunc);
  auto *BB53 = llvm::BasicBlock::Create(context, "", appFunc);
  auto *BB65 = llvm::BasicBlock::Create(context, "", appFunc);
  auto *BB67 = llvm::BasicBlock::Create(context, "", appFunc);
  auto *BB70 = llvm::BasicBlock::Create(context, "", appFunc);
  auto *BB74 = llvm::BasicBlock::Create(context, "", appFunc);
  auto *BB78 = llvm::BasicBlock::Create(context, "", appFunc);
  auto *BB81 = llvm::BasicBlock::Create(context, "", appFunc);
  auto *BB84 = llvm::BasicBlock::Create(context, "", appFunc);
  auto *BB88 = llvm::BasicBlock::Create(context, "", appFunc);
  auto *BB91 = llvm::BasicBlock::Create(context, "", appFunc);
  auto *BB94 = llvm::BasicBlock::Create(context, "", appFunc);
  auto *BB98 = llvm::BasicBlock::Create(context, "", appFunc);
  auto *BB101 = llvm::BasicBlock::Create(context, "", appFunc);
  auto *BB104 = llvm::BasicBlock::Create(context, "", appFunc);
  auto *BB109 = llvm::BasicBlock::Create(context, "", appFunc);
  auto *BB112 = llvm::BasicBlock::Create(context, "", appFunc);
  auto *BB115 = llvm::BasicBlock::Create(context, "", appFunc);
  auto *BB118 = llvm::BasicBlock::Create(context, "", appFunc);
  auto *BB123 = llvm::BasicBlock::Create(context, "", appFunc);

  //============================ BB0 ============================
  builder.SetInsertPoint(BB0);

  // %1 = alloca [32 x [32 x i32]], align 16
  auto *grid1 = builder.CreateAlloca(gridTy, nullptr, "");
  grid1->setAlignment(llvm::Align(16));

  // %2 = alloca [32 x [32 x i32]], align 16
  auto *grid2 = builder.CreateAlloca(gridTy, nullptr, "");
  grid2->setAlignment(llvm::Align(16));

  // call void @llvm.lifetime.start.p0(i64 4096, ptr nonnull %1)
  auto *grid1_i8 = builder.CreateBitCast(
      grid1, PointerType::get(Type::getInt8Ty(context), 0));
  builder.CreateLifetimeStart(grid1_i8, builder.getInt64(4096));

  // call void @llvm.memset.p0.i64(ptr noundef nonnull align 16
  // dereferenceable(4096) %1, i8 0, i64 4096, i1 false)
  builder.CreateMemSet(grid1_i8, builder.getInt8(0), builder.getInt64(4096),
                       llvm::MaybeAlign(16));

  // call void @llvm.lifetime.start.p0(i64 4096, ptr nonnull %2)
  auto *grid2_i8 = builder.CreateBitCast(
      grid2, PointerType::get(Type::getInt8Ty(context), 0));
  builder.CreateLifetimeStart(grid2_i8, builder.getInt64(4096));

  // br label %3
  builder.CreateBr(BB3);

  //============================ BB3 ============================
  builder.SetInsertPoint(BB3);

  // %4 = phi i64 [ 0, %0 ], [ %6, %5 ]
  auto *phi4 = builder.CreatePHI(i64, 2);
  phi4->addIncoming(builder.getInt64(0), BB0);

  // br label %8
  builder.CreateBr(BB8);

  //============================ BB5 ============================
  builder.SetInsertPoint(BB5);

  // %6 = add nuw nsw i64 %4, 1
  auto *val6 = builder.CreateAdd(phi4, builder.getInt64(1));

  // %7 = icmp eq i64 %6, 32
  auto *val7 = builder.CreateICmpEQ(val6, builder.getInt64(32));

  // Updating phi4 from BB3
  phi4->addIncoming(val6, BB5);

  // br i1 %7, label %15, label %3
  builder.CreateCondBr(val7, BB15, BB3);

  //============================ BB8 ============================
  builder.SetInsertPoint(BB8);

  // %9 = phi i64 [ 0, %3 ], [ %13, %8 ]
  auto *phi9 = builder.CreatePHI(i64, 2);
  phi9->addIncoming(builder.getInt64(0), BB3);

  // %10 = tail call i32 (...) @simRand()
  auto *val10 = builder.CreateCall(simRand, {}, "");
  // %11 = srem i32 %10, 2
  auto *val11 = builder.CreateSRem(val10, builder.getInt32(2), "");

  // %12 = getelementptr inbounds [32 x i32], ptr %1, i64 %4, i64 %9
  auto *gep12 = builder.CreateInBoundsGEP(rowTy, grid1, {phi4, phi9});

  // store i32 %11, ptr %12, align 4
  builder.CreateStore(val11, gep12);

  // %13 = add nuw nsw i64 %9, 1
  auto *val13 = builder.CreateAdd(phi9, builder.getInt64(1));

  // Updating phi9 from BB8
  phi9->addIncoming(val13, BB8);

  // %14 = icmp eq i64 %13, 32
  auto *cmp14 = builder.CreateICmpEQ(val13, builder.getInt64(32));

  // br i1 %14, label %5, label %8
  builder.CreateCondBr(cmp14, BB5, BB8);

  //=========================== BB15 ============================
  builder.SetInsertPoint(BB15);

  // %16 = phi i32 [ %99, %98 ], [ 0, %5 ]
  auto *phi16 = builder.CreatePHI(i32, 2);
  phi16->addIncoming(builder.getInt32(0), BB5);

  // br label %18
  builder.CreateBr(BB18);

  //=========================== BB17 ============================
  builder.SetInsertPoint(BB17);

  // call void @llvm.lifetime.end.p0(i64 4096, ptr nonnull %2)
  builder.CreateLifetimeEnd(grid2_i8, builder.getInt64(4096));

  // call void @llvm.lifetime.end.p0(i64 4096, ptr nonnull %1)
  builder.CreateLifetimeEnd(grid1_i8, builder.getInt64(4096));

  // ret void
  builder.CreateRetVoid();

  //=========================== BB18 ============================
  builder.SetInsertPoint(BB18);

  // %19 = phi i64 [ 0, %15 ], [ %22, %21 ]
  auto *phi19 = builder.CreatePHI(i64, 2);
  phi19->addIncoming(builder.getInt64(0), BB15);

  // %20 = trunc i64 %19 to i32
  auto *val20 = builder.CreateTrunc(phi19, i32, "");

  // br label %25
  builder.CreateBr(BB25);

  //=========================== BB21 ============================
  builder.SetInsertPoint(BB21);

  // %22 = add nuw nsw i64 %19, 1
  auto *val22 = builder.CreateAdd(phi19, builder.getInt64(1));

  // %23 = icmp eq i64 %22, 32
  auto *cmp23 = builder.CreateICmpEQ(val22, builder.getInt64(32));

  // Updating phi19 from BB18
  phi19->addIncoming(val22, BB21);

  // br i1 %23, label %24, label %18
  builder.CreateCondBr(cmp23, BB24, BB18);

  //=========================== BB21 ============================
  builder.SetInsertPoint(BB24);

  // call void @llvm.memcpy.p0.p0.i64(ptr noundef nonnull align 16
  // dereferenceable(4096) %1, ptr noundef nonnull align 16
  // dereferenceable(4096) %2, i64 4096, i1 false)
  builder.CreateMemCpy(grid1, llvm::MaybeAlign(16), grid2, llvm::MaybeAlign(16),
                       builder.getInt64(4096), false);

  // br label %65
  builder.CreateBr(BB65);

  //=========================== BB25 ============================
  builder.SetInsertPoint(BB25);

  // %26 = phi i64 [ 0, %18 ], [ %63, %53 ]
  auto *phi26 = builder.CreatePHI(i64, 2);
  phi26->addIncoming(builder.getInt64(0), BB18);

  // %27 = trunc i64 %26 to i32
  auto *val27 = builder.CreateTrunc(phi26, i32, "");

  // br label %28
  builder.CreateBr(BB28);

  //=========================== BB28 ============================
  builder.SetInsertPoint(BB28);

  // %29 = phi i32 [ 0, %25 ], [ %50, %34 ]
  auto *phi29 = builder.CreatePHI(i32, 2);
  phi29->addIncoming(builder.getInt32(0), BB25);

  // %30 = phi i32 [ -1, %25 ], [ %35, %34 ]
  auto *phi30 = builder.CreatePHI(i32, 2);
  phi30->addIncoming(builder.getInt32(-1), BB25);

  // %31 = add i32 %30, %27
  auto *val31 = builder.CreateAdd(phi30, val27);

  // %32 = and i32 %31, 31
  auto *val32 = builder.CreateAnd(val31, builder.getInt32(31));

  // %33 = zext nneg i32 %32 to i64
  auto *val33 = builder.CreateZExt(val32, i64);

  // br label %37
  builder.CreateBr(BB37);

  //=========================== BB34 ============================
  builder.SetInsertPoint(BB34);

  // %35 = add nsw i32 %30, 1
  auto *val35 = builder.CreateNSWAdd(phi30, builder.getInt32(1));

  // Updating phi30 from BB28
  phi30->addIncoming(val35, BB34);

  // %36 = icmp eq i32 %35, 2
  auto *cmp36 = builder.CreateICmpEQ(val35, builder.getInt32(2));

  // br i1 %36, label %53, label %28
  builder.CreateCondBr(cmp36, BB53, BB28);

  //=========================== BB37 ============================
  builder.SetInsertPoint(BB37);

  // %38 = phi i32 [ %29, %28 ], [ %50, %49 ]
  auto *phi38 = builder.CreatePHI(i32, 2);
  phi38->addIncoming(phi29, BB28);

  // %39 = phi i32 [ -1, %28 ], [ %51, %49 ]
  auto *phi39 = builder.CreatePHI(i32, 2);
  phi39->addIncoming(builder.getInt32(-1), BB28);

  // %40 = or i32 %39, %30
  auto *val40 = builder.CreateOr(phi39, phi30);

  // %41 = icmp eq i32 %40, 0
  auto *cmp41 = builder.CreateICmpEQ(val40, builder.getInt32(0));

  // br i1 %41, label %49, label %42
  builder.CreateCondBr(cmp41, BB49, BB42);

  //=========================== BB42 ============================
  builder.SetInsertPoint(BB42);

  // %43 = add i32 %39, %20
  auto *val43 = builder.CreateAdd(phi39, val20);

  // %44 = and i32 %43, 31
  auto *val44 = builder.CreateAnd(val43, builder.getInt32(31));

  // %45 = zext nneg i32 %44 to i64
  auto *val45 = builder.CreateZExt(val44, i64);

  // %46 = getelementptr inbounds [32 x i32], ptr %1, i64 %45, i64 %33
  auto *gep46 = builder.CreateInBoundsGEP(rowTy, grid1, {val45, val33});

  // %47 = load i32, ptr %46, align 4
  auto *val47 = builder.CreateLoad(i32, gep46, "");

  // %48 = add nsw i32 %47, %38
  auto *val48 = builder.CreateNSWAdd(val47, phi38);

  // br label %49
  builder.CreateBr(BB49);

  //=========================== BB49 ============================
  builder.SetInsertPoint(BB49);

  // %50 = phi i32 [ %38, %37 ], [ %48, %42 ]
  auto *phi50 = builder.CreatePHI(i32, 2);
  phi50->addIncoming(phi38, BB37);
  phi50->addIncoming(val48, BB42);

  // %51 = add nsw i32 %39, 1
  auto *val51 = builder.CreateNSWAdd(phi39, builder.getInt32(1));

  // Updating phi38 from BB37
  phi29->addIncoming(phi50, BB34);

  // Updating phi38 from BB37
  phi38->addIncoming(phi50, BB49);

  // Updating phi39 from BB37
  phi39->addIncoming(val51, BB49);

  // %52 = icmp eq i32 %51, 2
  auto *cmp52 = builder.CreateICmpEQ(val51, builder.getInt32(2));

  // br i1 %52, label %34, label %37
  builder.CreateCondBr(cmp52, BB34, BB37);

  //=========================== BB53 ============================
  builder.SetInsertPoint(BB53);

  // %54 = getelementptr inbounds [32 x [32 x i32]], ptr %1, i64 0, i64 %19, i64
  // %26
  auto *val54 = builder.CreateInBoundsGEP(gridTy, grid1,
                                          {builder.getInt64(0), phi19, phi26});
  // %55 = load i32, ptr %54, align 4
  auto *val55 = builder.CreateLoad(i32, val54, "");

  // %56 = icmp eq i32 %55, 0
  auto *val56 = builder.CreateICmpEQ(val55, builder.getInt32(0));

  // %57 = icmp eq i32 %50, 3
  auto *val57 = builder.CreateICmpEQ(phi50, builder.getInt32(3));

  // %58 = and i32 %50, -2
  auto *val58 = builder.CreateAnd(phi50, builder.getInt32(-2));

  // %59 = icmp eq i32 %58, 2
  auto *val59 = builder.CreateICmpEQ(val58, builder.getInt32(2));

  // %60 = select i1 %56, i1 %57, i1 %59
  auto *val60 = builder.CreateSelect(val56, val57, val59);

  // %61 = zext i1 %60 to i32
  auto *val61 = builder.CreateZExt(val60, i32);

  // %62 = getelementptr inbounds [32 x [32 x i32]], ptr %2, i64 0, i64 %19, i64
  auto *val62 = builder.CreateInBoundsGEP(gridTy, grid2,
                                          {builder.getInt64(0), phi19, phi26});
  // %26 store i32 %61, ptr %62, align 4
  builder.CreateStore(val61, val62);

  // %63 = add nuw nsw i64 %26, 1
  auto *val63 = builder.CreateNSWAdd(phi26, builder.getInt64(1));

  // Updating phi26 from BB25
  phi26->addIncoming(val63, BB53);

  // %64 = icmp eq i64 %63, 32
  auto *val64 = builder.CreateICmpEQ(val63, builder.getInt64(32));

  // br i1 %64, label %21, label %25
  builder.CreateCondBr(val64, BB21, BB25);

  //=========================== BB65 ============================
  builder.SetInsertPoint(BB65);

  // %66 = phi i32 [ %68, %67 ], [ 0, %24 ]
  auto *phi66 = builder.CreatePHI(i32, 2);
  phi66->addIncoming(builder.getInt32(0), BB24);

  // br label %70
  builder.CreateBr(BB70);

  //=========================== BB67 ============================
  builder.SetInsertPoint(BB67);

  // %68 = add nuw nsw i32 %66, 1
  auto *val68 = builder.CreateNSWAdd(phi66, builder.getInt32(1));

  // Updating phi66 from BB28
  phi66->addIncoming(val68, BB67);

  // %69 = icmp eq i32 %68, 512
  auto *val69 = builder.CreateICmpEQ(val68, builder.getInt32(512));

  // br i1 %69, label %74, label %65
  builder.CreateCondBr(val69, BB74, BB65);

  //=========================== BB70 ============================
  builder.SetInsertPoint(BB70);

  // %71 = phi i32 [ 0, %65 ], [ %72, %70 ]
  auto *phi71 = builder.CreatePHI(i32, 2);
  phi71->addIncoming(builder.getInt32(0), BB65);

  // tail call void @simPutPixel(i32 noundef %71, i32 noundef %66, i32 noundef
  // -1)
  builder.CreateCall(simPutPixel, {phi71, phi66, builder.getInt32(-1)});

  // %72 = add nuw nsw i32 %71, 1
  auto *val72 = builder.CreateNSWAdd(phi71, builder.getInt32(1));

  phi71->addIncoming(val72, BB70);

  // %73 = icmp eq i32 %72, 512
  auto *val73 = builder.CreateICmpEQ(val72, builder.getInt32(512));

  // br i1 %73, label %67, label %70
  builder.CreateCondBr(val73, BB67, BB70);

  //=========================== BB74 ============================
  builder.SetInsertPoint(BB74);

  // %75 = phi i64 [ %102, %101 ], [ 0, %67 ]
  auto *phi75 = builder.CreatePHI(i64, 2);
  phi75->addIncoming(builder.getInt64(0), BB67);

  // %76 = trunc i64 %75 to i32
  auto *phi76 = builder.CreateTrunc(phi75, i32);

  // %77 = shl i32 %76, 4
  auto *val77 = builder.CreateShl(phi76, builder.getInt32(4));

  // br label %104
  builder.CreateBr(BB104);

  //=========================== BB78 ============================
  builder.SetInsertPoint(BB78);

  // %79 = phi i32 [ %82, %81 ], [ 0, %101 ]
  auto *phi79 = builder.CreatePHI(i32, 2);
  phi79->addIncoming(builder.getInt32(0), BB101);

  // %80 = shl nuw nsw i32 %79, 4
  auto *val80 = builder.CreateShl(phi79, builder.getInt32(4));

  // br label %84
  builder.CreateBr(BB84);

  //=========================== BB81 ============================
  builder.SetInsertPoint(BB81);

  // %82 = add nuw nsw i32 %79, 1
  auto *val82 = builder.CreateAdd(phi79, builder.getInt32(1));

  // Updating phi79 from BB78
  phi79->addIncoming(val82, BB81);

  // %83 = icmp eq i32 %82, 32
  auto *val83 = builder.CreateICmpEQ(val82, builder.getInt32(32));

  // br i1 %83, label %88, label %78
  builder.CreateCondBr(val83, BB88, BB78);

  //=========================== BB84 ============================
  builder.SetInsertPoint(BB84);

  // %85 = phi i32 [ 0, %78 ], [ %86, %84 ]
  auto *phi85 = builder.CreatePHI(i32, 2);
  phi85->addIncoming(builder.getInt32(0), BB78);

  // tail call void @simPutPixel(i32 noundef %80, i32 noundef %85, i32 noundef
  // 6908265)
  builder.CreateCall(simPutPixel, {val80, phi85, builder.getInt32(6908265)});

  // %86 = add nuw nsw i32 %85, 1
  auto *val86 = builder.CreateNSWAdd(phi85, builder.getInt32(1));

  // Updating phi85 from BB84
  phi85->addIncoming(val86, BB84);

  // %87 = icmp eq i32 %86, 512
  auto *cmp87 = builder.CreateICmpEQ(val86, builder.getInt32(512));

  // br i1 %87, label %81, label %84
  builder.CreateCondBr(cmp87, BB81, BB84);

  //=========================== BB88 ============================
  builder.SetInsertPoint(BB88);

  // %89 = phi i32 [ %92, %91 ], [ 0, %81 ]
  auto *phi89 = builder.CreatePHI(i32, 2);
  phi89->addIncoming(builder.getInt32(0), BB81);

  // %90 = shl nuw nsw i32 %89, 4
  auto *val90 = builder.CreateShl(phi89, builder.getInt32(4));

  // br label %94
  builder.CreateBr(BB94);

  //=========================== BB91 ============================
  builder.SetInsertPoint(BB91);

  // %92 = add nuw nsw i32 %89, 1
  auto *val92 = builder.CreateAdd(phi89, builder.getInt32(1));

  // Updating phi89 from BB88
  phi89->addIncoming(val92, BB91);

  // %93 = icmp eq i32 %92, 32
  auto *val93 = builder.CreateICmpEQ(val92, builder.getInt32(32));

  // br i1 %93, label %98, label %88
  builder.CreateCondBr(val93, BB98, BB88);

  //=========================== BB94 ============================
  builder.SetInsertPoint(BB94);

  // %95 = phi i32 [ 0, %88 ], [ %96, %94 ]
  auto *phi95 = builder.CreatePHI(i32, 2);
  phi95->addIncoming(builder.getInt32(0), BB88);

  // tail call void @simPutPixel(i32 noundef %95, i32 noundef %90, i32 noundef
  // 6908265)
  builder.CreateCall(simPutPixel, {phi95, val90, builder.getInt32(6908265)});

  // %96 = add nuw nsw i32 %95, 1
  auto *val96 = builder.CreateNSWAdd(phi95, builder.getInt32(1));

  // Updating phi95 from BB94
  phi95->addIncoming(val96, BB94);

  // %97 = icmp eq i32 %96, 512
  auto *val97 = builder.CreateICmpEQ(val96, builder.getInt32(512));

  // br i1 %97, label %91, label %94
  builder.CreateCondBr(val97, BB91, BB94);

  //=========================== BB98 ============================
  builder.SetInsertPoint(BB98);

  // tail call void (...) @simFlush()
  builder.CreateCall(simFlush, {});

  // %99 = add nuw nsw i32 %16, 1
  auto *val99 = builder.CreateNSWAdd(phi16, builder.getInt32(1));

  // Updating phi16 from BB15
  phi16->addIncoming(val99, BB98);

  // %100 = icmp eq i32 %99, 10000
  auto *val100 = builder.CreateICmpEQ(val99, builder.getInt32(10000));

  // br i1 %100, label %17, label %15
  builder.CreateCondBr(val100, BB17, BB15);

  //=========================== BB101 ============================
  builder.SetInsertPoint(BB101);

  // %102 = add nuw nsw i64 %75, 1
  auto *val102 = builder.CreateNSWAdd(phi75, builder.getInt64(1));

  // Updating phi75 from BB74
  phi75->addIncoming(val102, BB101);

  // %103 = icmp eq i64 %102, 32
  auto *val103 = builder.CreateICmpEQ(val102, builder.getInt64(32));

  // br i1 %103, label %78, label %74
  builder.CreateCondBr(val103, BB78, BB74);

  //=========================== BB104 ============================
  builder.SetInsertPoint(BB104);

  // %105 = phi i64 [ 0, %74 ], [ %124, %123 ]
  auto *phi105 = builder.CreatePHI(i64, 2);
  phi105->addIncoming(builder.getInt64(0), BB74);

  // %106 = getelementptr inbounds [32 x [32 x i32]], ptr %1, i64 0, i64 %75,
  // i64 %105
  auto *val106 = builder.CreateInBoundsGEP(
      gridTy, grid1, {builder.getInt64(0), phi75, phi105});

  // %107 = load i32, ptr %106, align 4
  auto *val107 = builder.CreateLoad(i32, val106);

  // %108 = icmp eq i32 %107, 0
  auto *val108 = builder.CreateICmpEQ(val107, builder.getInt32(0));

  // br i1 %108, label %123, label %109
  builder.CreateCondBr(val108, BB123, BB109);

  //=========================== BB109 ============================
  builder.SetInsertPoint(BB109);

  // %110 = trunc i64 %105 to i32
  auto *val110 = builder.CreateTrunc(phi105, i32);

  // %111 = shl i32 %110, 4
  auto *val111 = builder.CreateShl(val110, builder.getInt32(4));

  // br label %112
  builder.CreateBr(BB112);

  //=========================== BB112 ============================
  builder.SetInsertPoint(BB112);

  // %113 = phi i32 [ %116, %115 ], [ 0, %109 ]
  auto *phi113 = builder.CreatePHI(i32, 2);
  phi113->addIncoming(builder.getInt32(0), BB109);

  // %114 = add nuw nsw i32 %113, %77
  auto *val114 = builder.CreateAdd(phi113, val77);

  // br label %118
  builder.CreateBr(BB118);

  //=========================== BB115 ============================
  builder.SetInsertPoint(BB115);

  // %116 = add nuw nsw i32 %113, 1
  auto *val116 = builder.CreateAdd(phi113, builder.getInt32(1));

  // Updating phi113 from BB112
  phi113->addIncoming(val116, BB115);

  // %117 = icmp eq i32 %116, 16
  auto *val117 = builder.CreateICmpEQ(val116, builder.getInt32(16));

  // br i1 %117, label %123, label %112
  builder.CreateCondBr(val117, BB123, BB112);

  //=========================== BB118 ============================
  builder.SetInsertPoint(BB118);

  // %119 = phi i32 [ 0, %112 ], [ %121, %118 ]
  auto *phi119 = builder.CreatePHI(i32, 2);
  phi119->addIncoming(builder.getInt32(0), BB112);

  // %120 = add nuw nsw i32 %119, %111
  auto *val120 = builder.CreateNSWAdd(phi119, val111);

  // tail call void @simPutPixel(i32 noundef %120, i32 noundef %114, i32 noundef
  // -2139062017)
  builder.CreateCall(simPutPixel,
                     {val120, val114, builder.getInt32(-2139062017)});

  // %121 = add nuw nsw i32 %119, 1
  auto *val121 = builder.CreateNSWAdd(phi119, builder.getInt32(1));

  // Updating phi119 from BB118
  phi119->addIncoming(val121, BB118);

  // %122 = icmp eq i32 %121, 16
  auto *val122 = builder.CreateICmpEQ(val121, builder.getInt32(16));

  // br i1 %122, label %115, label %118
  builder.CreateCondBr(val122, BB115, BB118);

  //=========================== BB123 ============================
  builder.SetInsertPoint(BB123);

  // %124 = add nuw nsw i64 %105, 1
  auto *val124 = builder.CreateNSWAdd(phi105, builder.getInt64(1));

  // Updating phi105 from BB104
  phi105->addIncoming(val124, BB123);

  // %125 = icmp eq i64 %124, 32
  auto *val125 = builder.CreateICmpEQ(val124, builder.getInt64(32));

  // br i1 %125, label %101, label %104
  builder.CreateCondBr(val125, BB101, BB104);
}
} // namespace LLVM_IRGen
