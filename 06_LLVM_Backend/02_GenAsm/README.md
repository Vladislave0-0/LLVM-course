# Assembler Generation

`test.ll`:

```llvm
define dso_local i32 @main() {
  ret i32 12
}
```

Получение `test.s` из `test.ll`:
```
.../llvm-project/build/bin/llc test.ll -march rus
```

---

#### [Rus] 2. Add Register Info for Rus architecture:
>ERROR: void llvm::TargetPassConfig::addPassesToHandleExceptions(): Assertion `MCAI && "No MCAsmInfo"' failed.
+ Rus/RusTargetMachine.cpp RusTargetMachine + initAsmInfo();
>ERROR: void llvm::LLVMTargetMachine::initAsmInfo(): Assertion `MRI && "Unable to create reg info"' failed.
+ RusMCTargetDesc.cpp : createRusMCRegisterInfo()
+ RusRegisterInfo.td/.h/.cpp + generation
+ RusGenRegisterInfo.inc including:
```cpp
const RusFrameLowering *
RusGenRegisterInfo::getFrameLowering(const MachineFunction &MF) {
  return static_cast<const RusFrameLowering *>(
      MF.getSubtarget().getFrameLowering());
}
```
+ RusFrameLowering.h (`virtual ... = 0`)
>ERROR: void llvm::LLVMTargetMachine::initAsmInfo(): Assertion `MII && "Unable to create instruction info"' failed.


#### [Rus] 3. Add Instruction Info for Rus architecture:
+ RusMCTargetDesc.cpp : createRusMCInstrInfo
+ RusInstrFormat.td RusInstrInfo.td/.h/.cpp + generation
+ RusImfo.h
>ERROR: void llvm::LLVMTargetMachine::initAsmInfo(): Assertion `STI && "Unable to create subtarget info"' failed.


#### [Rus] 4. Add empty Subtarget for Rus architecture:
+ RusMCTargetDesc.cpp : createRusMCSubtargetInfo + RusSubtarget.h/.cpp + gen RusGenSubtargetInfo.inc
>ERROR: void llvm::LLVMTargetMachine::initAsmInfo(): Assertion `TmpAsmInfo && "MCAsmInfo not initialized."


#### [Rus] 5. Add RusMCAsmInfo for Rus architecture:
+ RusMCTargetDesc.cpp : createRusMCAsmInfo + RusMCAsmInfo.h/.cpp
>ERROR: llc: error: target does not support generation of this file type


#### [Rus] 6. Add empty RusPassConfig: + [Rus] 9. Add createRusISelDag
+ RusMCTargetDesc.cpp : RusPassConfig
>ERROR: Assertion `InstPrinter' failed.


#### [Rus] 7. Add empty RusInstPrinter
+ Rus/RusTargetMachine.cpp : createRusMCInstPrinter()
+ Rus/RusInstPrinter.h
>ERROR: llc: error: target does not support generation of this file type


#### [Rus] 8. Add empty RusAsmPrinter
+ RusAsmPrinter.cpp
>ERROR: Segmentation fault (compileModule(char**, llvm::LLVMContext&) in Target->getObjFileLowering())


#### [Rus] 10. Add RusTargetMachine::getObjFileLowering
+ RusTargetMachine.cpp: TLOF
>ERROR: Segmentation fault in Running pass 'Expand large div/rem' on function '@main'


#### [Rus] 11. Update Subtarget and add RusTargetLowering
+ RusISelLowering.h : RusTargetLowering
>ERROR: Segmentation fault in Running pass 'Rus DAG->DAG Pattern Instruction Selection' on function '@main' in STI->getFrameLowering()

#### [Rus] 12. Add getFrameLowering to RusSubtarget
+ RusSubtarget.h : *getFrameLowering
>ERROR: Not Implemented  UNREACHABLE executed at virtual SDValue LowerCall(...)

#### [Rus] 13. Add Calling Convention, MachineFunction and Lowering Functions
+ RusCallingConv.td, RusMachineFunctionInfo.h + Big RusISelLowering.cpp Update
>ERROR: Segmentation fault in Running pass 'Rus DAG->DAG Pattern Instruction Selection' on function '@main' in MF.getSubtarget().getRegisterInfo()

#### [Rus] 14. Update RusRegisterInfo and add to RusSubtarget
+ RusRegisterInfo.cpp .h updates
+ RusSubtarget.h : + getRegisterInfo
>ERROR: Creating constant: t1: i32 = Constant<12> Assertion `idx < size()' failed. TLI.getNumRegistersForCallingConv

#### [Rus] 15. Extend RusTargetLowering with RusRegisterInfo
+ RusTargetLowering.cpp RusTargetLowering update
>ERROR: Segmentation fault ISEL: Starting pattern match

#### [Rus] 16. Add InstrInfo and TSInfo to RusSubtarget
+ RusSubtarget.h : + getInstrInfo, getSelectionDAGInfo
Check instructions in asm file (`test.s`):
```llvm
main:                                   ; @main
; %bb.0:

.Lfunc_end0:
```
#### [Rus] 17. Add full RusInstPrinter
+ MCTargetDesc/RusInstPrinter.cpp
```llvm
main:                                   ; @main
; %bb.0:
	BR LESHY
.Lfunc_end0:
```

#### [Rus] 18. Implement lowerRusMachineInstrToMCInst for AsmPrinter
+ RusMCInstLower.cpp
```llvm
main:                                   ; @main
; %bb.0:
	MOVi GUSLI 12
	BR LESHY
.Lfunc_end0:
```

#### Extra experiments:
```
build/bin/llc build/test.ll -march rus -view-isel-dags
```
![image](https://github.com/user-attachments/assets/dbde84db-faee-4fea-83e7-18be9d352f44)
```
build/bin/llc build/test.ll -march rus -view-sched-dags
```
![image](https://github.com/user-attachments/assets/d0a4b2b8-a564-4f8c-8cce-37379c2006c3)
