# Assembler Graphic Generation

`graphic.ll`:
```llvm
define dso_local void @app() {
entry:
  call void @llvm.rus.putpixel(i32 5, i32 5, i32 -1)
  call void @llvm.rus.flush()
  call i32 @llvm.rus.rand()
  ret void
}

declare void @llvm.rus.putpixel(i32, i32, i32)
declare void @llvm.rus.flush()
declare i32 @llvm.rus.rand()
```

Получение `graphic.s` из `graphic.ll`:
```
.../llvm-project/build/bin/llc graphic.ll -march rus --filetype=asm
```

---

>ERROR: llvm::RusTargetLowering::LowerCall Assertion `getTargetMachine().shouldAssumeDSOLocal(GV)'
#### [Rus] 23. Add Rus intrinsics support (flush, putpixel, rand)
+ llvm/include/llvm/IR/IntrinsicsRus.td + update RusInstrInfo.td
Check intrinsics in asm file (`graphic.s`):
```llvm
app:                                    ; @app
; %bb.0:                                ; %entry
	MOVi LAPTI -1
	MOVi TROPKA 5
	PUTPIXEL TROPKA TROPKA LAPTI
	FLUSH
	RAND LAPTI
	BR LESHY
.Lfunc_end0:
```


Add intrisics to the custom FrontEnd:
```cpp
// 05_LANG2IR/include/IRGenerator.hpp:
  const std::string_view simPutPixelName = "llvm.rus.simPutPixel";
  const std::string_view simFlushName = "llvm.rus.simFlush";
  const std::string_view simRandName = "llvm.rus.simRand";
```

```cpp
// 05_LANG2IR/src/IRGenerator.cpp:
  auto *voidTy = llvm::Type::getVoidTy(context);
  auto *simFlushTy = llvm::FunctionType::get(voidTy, {}, false);
  auto *simRandTy = llvm::FunctionType::get(i32Ty, {}, false);

  auto *simPutPixelTy =
      llvm::FunctionType::get(voidTy, {i32Ty, i32Ty, i32Ty}, false);

  llvm::Function::Create(simPutPixelTy, llvm::GlobalValue::ExternalLinkage,
                         simPutPixelName, *IRModule);

  llvm::Function::Create(simFlushTy, llvm::GlobalValue::ExternalLinkage,
                         simFlushName, *IRModule);

  llvm::Function::Create(simRandTy, llvm::GlobalValue::ExternalLinkage,
                         simRandName, *IRModule);
```
