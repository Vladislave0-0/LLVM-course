; ModuleID = 'ASM2IR'
source_filename = "ASM2IR"

@reg_file = external global [64 x i64]

define void @app() {
app:
  store i64 100, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 1), align 4
  store i64 100, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 2), align 4
  store i64 0, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 6), align 4
  store i64 -65536, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 8), align 4
  br label %outer_loop

outer_loop:                                       ; preds = %continue_outer, %app
  store i64 0, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 7), align 4
  br label %inner_loop

inner_loop:                                       ; preds = %inner_loop, %outer_loop
  %0 = load i64, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 7), align 4
  %1 = load i64, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 1), align 4
  %2 = add i64 %1, %0
  store i64 %2, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 3), align 4
  %3 = load i64, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 6), align 4
  %4 = load i64, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 2), align 4
  %5 = add i64 %4, %3
  store i64 %5, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 4), align 4
  %6 = load i64, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 3), align 4
  %7 = trunc i64 %6 to i32
  %8 = load i64, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 4), align 4
  %9 = trunc i64 %8 to i32
  %10 = load i64, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 8), align 4
  %11 = trunc i64 %10 to i32
  call void @simPutPixel(i32 %7, i32 %9, i32 %11)
  %12 = load i64, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 7), align 4
  %13 = add i64 %12, 1
  store i64 %13, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 7), align 4
  %14 = load i64, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 7), align 4
  %15 = icmp slt i64 %14, 100
  %16 = zext i1 %15 to i64
  store i64 %16, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 9), align 4
  %17 = load i64, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 9), align 4
  %18 = trunc i64 %17 to i1
  br i1 %18, label %inner_loop, label %continue_outer

continue_outer:                                   ; preds = %inner_loop
  %19 = load i64, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 6), align 4
  %20 = add i64 %19, 1
  store i64 %20, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 6), align 4
  %21 = load i64, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 6), align 4
  %22 = icmp slt i64 %21, 100
  %23 = zext i1 %22 to i64
  store i64 %23, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 9), align 4
  %24 = load i64, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 9), align 4
  %25 = trunc i64 %24 to i1
  br i1 %25, label %outer_loop, label %finish

finish:                                           ; preds = %continue_outer
  call void @simFlush()
  ret void
}

declare void @simFlush()

declare void @simPutPixel(i32, i32, i32)

declare i32 @simRand()

declare void @dumpReg(i64, i64)
