#include "../include/generator.hpp"
#include "llvm/ExecutionEngine/ExecutionEngine.h"
#include "llvm/ExecutionEngine/GenericValue.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Verifier.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/Support/raw_ostream.h"
#include <memory>
#include <string>

namespace LLVM_IRGen {
llvm::Function *Generator::printSimRand() {
  auto *i32 = llvm::Type::getInt32Ty(context);
  auto *funcTy = llvm::FunctionType::get(i32, {}, true);

  return llvm::Function::Create(funcTy, llvm::GlobalValue::ExternalLinkage,
                                simRandName, *IRModule);
}

llvm::Function *Generator::printSimPutPixel() {
  auto *voidTy = llvm::Type::getVoidTy(context);
  auto *i32 = llvm::Type::getInt32Ty(context);
  auto *funcTy = llvm::FunctionType::get(voidTy, {i32, i32, i32}, false);

  return llvm::Function::Create(funcTy, llvm::GlobalValue::ExternalLinkage,
                                simPutPixelName, *IRModule);
}

llvm::Function *Generator::printSimFlush() {
  auto *voidTy = llvm::Type::getVoidTy(context);
  auto *funcTy = llvm::FunctionType::get(voidTy, {}, true);

  return llvm::Function::Create(funcTy, llvm::GlobalValue::ExternalLinkage,
                                simFlushName, *IRModule);
}

void Generator::dump() {
  IRModule->print(outs(), nullptr);
  outs() << '\n';
}

void Generator::interpretation() {}

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
  phi30->addIncoming(val35, BB49);

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
}
} // namespace LLVM_IRGen

// Updating phi30 from BB28
// %16 = phi i32 [ %99, %98 ]
