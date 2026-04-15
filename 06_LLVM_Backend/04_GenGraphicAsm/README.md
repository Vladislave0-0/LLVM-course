# Assembler Graphic Generation

`graphic.ll`:
```llvm
define dso_local void @app() {
entry:
  call void @llvm.rus.putpixel(i32 5, i32 5, i32 -1)
  call void @llvm.rus.flush()
  ret void
}

declare void @llvm.rus.putpixel(i32, i32, i32)

declare void @llvm.rus.flush()
```

Получение `graphic.s` из `graphic.ll`:
```
.../llvm-project/build/bin/llc graphic.ll -march rus --filetype=asm
```

---

>ERROR: llvm::RusTargetLowering::LowerCall Assertion `getTargetMachine().shouldAssumeDSOLocal(GV)'
#### [Rus] 23. Add Rus intrinsics support (flush and putpixel)
+ llvm/include/llvm/IR/IntrinsicsRus.td + update RusInstrInfo.td
Check intrinsics in asm file (`graphic.s`):
```llvm
app:                                    ; @app
; %bb.0:                                ; %entry
	MOVli r2 -1
	MOVli r4 5
	PUTPIXEL r4 r4 r2
	FLUSH
	BR r0
.Lfunc_end0:
```

Add intrisics to the custom FrontEnd:
```cpp
// declare void @llvm.rus.putpixel(i32 noundef, i32 noundef, i32 noundef)
ArrayRef<Type *> rusPutPixelParamTypes = {Type::getInt32Ty(context),
                                            Type::getInt32Ty(context),
                                            Type::getInt32Ty(context)};
FunctionType *rusPutPixelType =
    FunctionType::get(voidType, rusPutPixelParamTypes, false);
rusPutPixelFunc =
    module->getOrInsertFunction("llvm.rus.putpixel", rusPutPixelType);

// declare void @llvm.rus.flush()
FunctionType *rusFlushType = FunctionType::get(voidType, false);
rusFlushFunc =
    module->getOrInsertFunction("llvm.rus.flush", rusFlushType);
```