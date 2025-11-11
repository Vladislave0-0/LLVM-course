; ModuleID = 'asm_program'
source_filename = "asm_program"

define void @main() {
entry:
  %registers = alloca [32 x i32], align 4
  %reg_ptr = getelementptr [32 x i32], ptr %registers, i64 0, i64 0
  store i32 0, ptr %reg_ptr, align 4
  %reg_ptr1 = getelementptr [32 x i32], ptr %registers, i64 0, i64 1
  store i32 0, ptr %reg_ptr1, align 4
  %reg_ptr2 = getelementptr [32 x i32], ptr %registers, i64 0, i64 2
  store i32 0, ptr %reg_ptr2, align 4
  %reg_ptr3 = getelementptr [32 x i32], ptr %registers, i64 0, i64 3
  store i32 0, ptr %reg_ptr3, align 4
  %reg_ptr4 = getelementptr [32 x i32], ptr %registers, i64 0, i64 4
  store i32 0, ptr %reg_ptr4, align 4
  %reg_ptr5 = getelementptr [32 x i32], ptr %registers, i64 0, i64 5
  store i32 0, ptr %reg_ptr5, align 4
  %reg_ptr6 = getelementptr [32 x i32], ptr %registers, i64 0, i64 6
  store i32 0, ptr %reg_ptr6, align 4
  %reg_ptr7 = getelementptr [32 x i32], ptr %registers, i64 0, i64 7
  store i32 0, ptr %reg_ptr7, align 4
  %reg_ptr8 = getelementptr [32 x i32], ptr %registers, i64 0, i64 8
  store i32 0, ptr %reg_ptr8, align 4
  %reg_ptr9 = getelementptr [32 x i32], ptr %registers, i64 0, i64 9
  store i32 0, ptr %reg_ptr9, align 4
  %reg_ptr10 = getelementptr [32 x i32], ptr %registers, i64 0, i64 10
  store i32 0, ptr %reg_ptr10, align 4
  %reg_ptr11 = getelementptr [32 x i32], ptr %registers, i64 0, i64 11
  store i32 0, ptr %reg_ptr11, align 4
  %reg_ptr12 = getelementptr [32 x i32], ptr %registers, i64 0, i64 12
  store i32 0, ptr %reg_ptr12, align 4
  %reg_ptr13 = getelementptr [32 x i32], ptr %registers, i64 0, i64 13
  store i32 0, ptr %reg_ptr13, align 4
  %reg_ptr14 = getelementptr [32 x i32], ptr %registers, i64 0, i64 14
  store i32 0, ptr %reg_ptr14, align 4
  %reg_ptr15 = getelementptr [32 x i32], ptr %registers, i64 0, i64 15
  store i32 0, ptr %reg_ptr15, align 4
  %reg_ptr16 = getelementptr [32 x i32], ptr %registers, i64 0, i64 16
  store i32 0, ptr %reg_ptr16, align 4
  %reg_ptr17 = getelementptr [32 x i32], ptr %registers, i64 0, i64 17
  store i32 0, ptr %reg_ptr17, align 4
  %reg_ptr18 = getelementptr [32 x i32], ptr %registers, i64 0, i64 18
  store i32 0, ptr %reg_ptr18, align 4
  %reg_ptr19 = getelementptr [32 x i32], ptr %registers, i64 0, i64 19
  store i32 0, ptr %reg_ptr19, align 4
  %reg_ptr20 = getelementptr [32 x i32], ptr %registers, i64 0, i64 20
  store i32 0, ptr %reg_ptr20, align 4
  %reg_ptr21 = getelementptr [32 x i32], ptr %registers, i64 0, i64 21
  store i32 0, ptr %reg_ptr21, align 4
  %reg_ptr22 = getelementptr [32 x i32], ptr %registers, i64 0, i64 22
  store i32 0, ptr %reg_ptr22, align 4
  %reg_ptr23 = getelementptr [32 x i32], ptr %registers, i64 0, i64 23
  store i32 0, ptr %reg_ptr23, align 4
  %reg_ptr24 = getelementptr [32 x i32], ptr %registers, i64 0, i64 24
  store i32 0, ptr %reg_ptr24, align 4
  %reg_ptr25 = getelementptr [32 x i32], ptr %registers, i64 0, i64 25
  store i32 0, ptr %reg_ptr25, align 4
  %reg_ptr26 = getelementptr [32 x i32], ptr %registers, i64 0, i64 26
  store i32 0, ptr %reg_ptr26, align 4
  %reg_ptr27 = getelementptr [32 x i32], ptr %registers, i64 0, i64 27
  store i32 0, ptr %reg_ptr27, align 4
  %reg_ptr28 = getelementptr [32 x i32], ptr %registers, i64 0, i64 28
  store i32 0, ptr %reg_ptr28, align 4
  %reg_ptr29 = getelementptr [32 x i32], ptr %registers, i64 0, i64 29
  store i32 0, ptr %reg_ptr29, align 4
  %reg_ptr30 = getelementptr [32 x i32], ptr %registers, i64 0, i64 30
  store i32 0, ptr %reg_ptr30, align 4
  %reg_ptr31 = getelementptr [32 x i32], ptr %registers, i64 0, i64 31
  store i32 0, ptr %reg_ptr31, align 4
  %reg_ptr32 = getelementptr [32 x i32], ptr %registers, i64 0, i64 0
  %reg_ptr33 = getelementptr [32 x i32], ptr %registers, i64 0, i64 1
  %reg_ptr34 = getelementptr [32 x i32], ptr %registers, i64 0, i64 2
  %reg_ptr35 = getelementptr [32 x i32], ptr %registers, i64 0, i64 3
  %reg_ptr36 = getelementptr [32 x i32], ptr %registers, i64 0, i64 4
  %reg_ptr37 = getelementptr [32 x i32], ptr %registers, i64 0, i64 5
  %reg_ptr38 = getelementptr [32 x i32], ptr %registers, i64 0, i64 6
  %reg_ptr39 = getelementptr [32 x i32], ptr %registers, i64 0, i64 7
  %reg_ptr40 = getelementptr [32 x i32], ptr %registers, i64 0, i64 8
  %reg_ptr41 = getelementptr [32 x i32], ptr %registers, i64 0, i64 9
  %reg_ptr42 = getelementptr [32 x i32], ptr %registers, i64 0, i64 10
  %reg_ptr43 = getelementptr [32 x i32], ptr %registers, i64 0, i64 11
  %reg_ptr44 = getelementptr [32 x i32], ptr %registers, i64 0, i64 12
  %reg_ptr45 = getelementptr [32 x i32], ptr %registers, i64 0, i64 13
  %reg_ptr46 = getelementptr [32 x i32], ptr %registers, i64 0, i64 14
  %reg_ptr47 = getelementptr [32 x i32], ptr %registers, i64 0, i64 15
  %reg_ptr48 = getelementptr [32 x i32], ptr %registers, i64 0, i64 16
  %reg_ptr49 = getelementptr [32 x i32], ptr %registers, i64 0, i64 17
  %reg_ptr50 = getelementptr [32 x i32], ptr %registers, i64 0, i64 18
  %reg_ptr51 = getelementptr [32 x i32], ptr %registers, i64 0, i64 19
  %reg_ptr52 = getelementptr [32 x i32], ptr %registers, i64 0, i64 20
  %reg_ptr53 = getelementptr [32 x i32], ptr %registers, i64 0, i64 21
  %reg_ptr54 = getelementptr [32 x i32], ptr %registers, i64 0, i64 22
  %reg_ptr55 = getelementptr [32 x i32], ptr %registers, i64 0, i64 23
  %reg_ptr56 = getelementptr [32 x i32], ptr %registers, i64 0, i64 24
  %reg_ptr57 = getelementptr [32 x i32], ptr %registers, i64 0, i64 25
  %reg_ptr58 = getelementptr [32 x i32], ptr %registers, i64 0, i64 26
  %reg_ptr59 = getelementptr [32 x i32], ptr %registers, i64 0, i64 27
  %reg_ptr60 = getelementptr [32 x i32], ptr %registers, i64 0, i64 28
  %reg_ptr61 = getelementptr [32 x i32], ptr %registers, i64 0, i64 29
  %reg_ptr62 = getelementptr [32 x i32], ptr %registers, i64 0, i64 30
  %reg_ptr63 = getelementptr [32 x i32], ptr %registers, i64 0, i64 31
  store i32 5, ptr %reg_ptr32, align 4
  store i32 3, ptr %reg_ptr33, align 4
  %0 = load i32, ptr %reg_ptr32, align 4
  %1 = load i32, ptr %reg_ptr33, align 4
  %add_result = add i32 %0, %1
  store i32 %add_result, ptr %reg_ptr34, align 4
  ret void

label_init:                                       ; No predecessors!
}
