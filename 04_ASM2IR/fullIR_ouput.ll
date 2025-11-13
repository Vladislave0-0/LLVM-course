; ModuleID = 'ASM2IR'
source_filename = "ASM2IR"

define void @app() {
app:
  %0 = alloca [64 x i64], align 8
  %1 = getelementptr [64 x i64], ptr %0, i64 0, i64 1
  store i64 100, ptr %1, align 4
  %2 = getelementptr [64 x i64], ptr %0, i64 0, i64 2
  store i64 100, ptr %2, align 4
  %3 = getelementptr [64 x i64], ptr %0, i64 0, i64 6
  store i64 0, ptr %3, align 4
  %4 = getelementptr [64 x i64], ptr %0, i64 0, i64 8
  store i64 -65536, ptr %4, align 4
  br label %outer_loop

outer_loop:                                       ; preds = %continue_outer, %app
  %5 = getelementptr [64 x i64], ptr %0, i64 0, i64 7
  store i64 0, ptr %5, align 4
  br label %inner_loop

inner_loop:                                       ; preds = %inner_loop, %outer_loop
  %6 = getelementptr [64 x i64], ptr %0, i64 0, i64 3
  %7 = getelementptr [64 x i64], ptr %0, i64 0, i64 7
  %8 = load i64, ptr %7, align 4
  %9 = getelementptr [64 x i64], ptr %0, i64 0, i64 1
  %10 = load i64, ptr %9, align 4
  %11 = add i64 %10, %8
  store i64 %11, ptr %6, align 4
  %12 = getelementptr [64 x i64], ptr %0, i64 0, i64 4
  %13 = getelementptr [64 x i64], ptr %0, i64 0, i64 6
  %14 = load i64, ptr %13, align 4
  %15 = getelementptr [64 x i64], ptr %0, i64 0, i64 2
  %16 = load i64, ptr %15, align 4
  %17 = add i64 %16, %14
  store i64 %17, ptr %12, align 4
  %18 = getelementptr [64 x i64], ptr %0, i64 0, i64 3
  %19 = load i64, ptr %18, align 4
  %20 = trunc i64 %19 to i32
  %21 = getelementptr [64 x i64], ptr %0, i64 0, i64 4
  %22 = load i64, ptr %21, align 4
  %23 = trunc i64 %22 to i32
  %24 = getelementptr [64 x i64], ptr %0, i64 0, i64 8
  %25 = load i64, ptr %24, align 4
  %26 = trunc i64 %25 to i32
  call void @simPutPixel(i32 %20, i32 %23, i32 %26)
  %27 = getelementptr [64 x i64], ptr %0, i64 0, i64 7
  %28 = getelementptr [64 x i64], ptr %0, i64 0, i64 7
  %29 = load i64, ptr %28, align 4
  %30 = add i64 %29, 1
  store i64 %30, ptr %27, align 4
  %31 = getelementptr [64 x i64], ptr %0, i64 0, i64 9
  %32 = getelementptr [64 x i64], ptr %0, i64 0, i64 7
  %33 = load i64, ptr %32, align 4
  %34 = icmp slt i64 %33, 100
  %35 = zext i1 %34 to i64
  store i64 %35, ptr %31, align 4
  %36 = getelementptr [64 x i64], ptr %0, i64 0, i64 9
  %37 = load i64, ptr %36, align 4
  %38 = trunc i64 %37 to i1
  br i1 %38, label %inner_loop, label %continue_outer

continue_outer:                                   ; preds = %inner_loop
  %39 = getelementptr [64 x i64], ptr %0, i64 0, i64 6
  %40 = getelementptr [64 x i64], ptr %0, i64 0, i64 6
  %41 = load i64, ptr %40, align 4
  %42 = add i64 %41, 1
  store i64 %42, ptr %39, align 4
  %43 = getelementptr [64 x i64], ptr %0, i64 0, i64 9
  %44 = getelementptr [64 x i64], ptr %0, i64 0, i64 6
  %45 = load i64, ptr %44, align 4
  %46 = icmp slt i64 %45, 100
  %47 = zext i1 %46 to i64
  store i64 %47, ptr %43, align 4
  %48 = getelementptr [64 x i64], ptr %0, i64 0, i64 9
  %49 = load i64, ptr %48, align 4
  %50 = trunc i64 %49 to i1
  br i1 %50, label %outer_loop, label %finish

finish:                                           ; preds = %continue_outer
  call void @simFlush()
  ret void
}

declare void @simFlush()

declare void @simPutPixel(i32, i32, i32)

declare i32 @simRand()

declare void @dumpReg(i64, i64)
