# Binary Generation

`test.ll`:

```llvm
define dso_local i32 @main() {
  ret i32 12
}
```

`test.s`:
```llvm
main:                                   ; @main
; %bb.0:
	MOVi GUSLI 12
	BR LESHY
.Lfunc_end0:
```

Получение `test.o` из `test.s`:
```
.../llvm-project/build/bin/llc test.ll -march rus --filetype=obj
```

---

>ERROR: createMCCodeEmitter failed
#### [Rus] 19. Add RusMCCodeEmitter
+ RusMCCodeEmitter.cpp
>ERROR: createMCAsmBackend failed
#### [Rus] 20. Add RusAsmBackend
+ RusAsmBackend.cpp
>ERROR: ELFRusAsmBackend::createObjectTargetWriter

#### [Rus] 21. Add RusELFObjectWriter
+ RusELFObjectWriter.cpp + add Rus in ELF.h/.cpp ELFObjectFile.h and ELFDumper.cpp

#### [Rus] 22. Update Rus Instruction info
+ Update RusInstrInfo.td RusInstrFormats.td

#### `llvm-readobj`:
```
ninja -C build llvm-readobj
.../llvm-project/build/bin/llvm-readobj test.o
```
```
File: test.o
Format: elf32-rus
Arch: rus
AddressSize: 32bit
LoadName: <Not found>
```
#### `llvm-readelf`:

```
ninja -C build llvm-readelf
.../llvm-project/build/bin/llvm-readelf -a test.o
```
```h
ELF Header:
  Magic:   7f 45 4c 46 01 01 01 00 00 00 00 00 00 00 00 00
  Class:                             ELF32
  Data:                              2's complement, little endian
  Version:                           1 (current)
  OS/ABI:                            UNIX - System V
  ABI Version:                       0
  Type:                              REL (Relocatable file)
  Machine:                           Rusulator target for LLVM course
....
  Number of section headers:         5
  Section header string table index: 1
There are 5 section headers, starting at offset 0xa0:

Section Headers:
  [Nr] Name              Type            Address  Off    Size   ES Flg Lk Inf Al
  [ 0]                   NULL            00000000 000000 000000 00      0   0  0
  [ 1] .strtab           STRTAB          00000000 00006c 000034 00      0   0  1
  [ 2] .text             PROGBITS        00000000 000034 000008 00  AX  0   0  4
  [ 3] .note.GNU-stack   PROGBITS        00000000 00003c 000000 00      0   0  1
  [ 4] .symtab           SYMTAB          00000000 00003c 000030 10      1   2  4
```
Check instructions in object file:
```
hexedit test.o
New position 0x34 (.text section address)
... 0C 00 90 AA  00 00 00 BB ...

```
