; ModuleID = 'ASM2IR'
source_filename = "ASM2IR"

@switch.table.app = private local_unnamed_addr constant [3 x i32] [i32 -16711936, i32 -16776961, i32 -65536], align 4

define void @app() {
app:
  %0 = alloca [64 x i64], align 8
  %1 = getelementptr [64 x i64], ptr %0, i64 0, i64 1
  store i64 0, ptr %1, align 4
  br label %label1

label1:                                           ; preds = %label7, %app
  %2 = getelementptr [64 x i64], ptr %0, i64 0, i64 2
  store i64 0, ptr %2, align 4
  br label %label9

label9:                                           ; preds = %put_pixel, %label1
  %3 = getelementptr [64 x i64], ptr %0, i64 0, i64 3
  %4 = call i32 @simRand()
  %5 = sext i32 %4 to i64
  store i64 %5, ptr %3, align 4
  %6 = getelementptr [64 x i64], ptr %0, i64 0, i64 3
  %7 = getelementptr [64 x i64], ptr %0, i64 0, i64 3
  %8 = load i64, ptr %7, align 4
  %9 = and i64 %8, 1
  store i64 %9, ptr %6, align 4
  %10 = getelementptr [64 x i64], ptr %0, i64 0, i64 0
  %11 = getelementptr [64 x i64], ptr %0, i64 0, i64 3
  %12 = load i64, ptr %11, align 4
  %13 = icmp eq i64 %12, 0
  %14 = zext i1 %13 to i64
  store i64 %14, ptr %10, align 4
  %15 = getelementptr [64 x i64], ptr %0, i64 0, i64 0
  %16 = load i64, ptr %15, align 4
  %17 = trunc i64 %16 to i1
  br i1 %17, label %set_black, label %set_color

set_color:                                        ; preds = %label9
  %18 = getelementptr [64 x i64], ptr %0, i64 0, i64 4
  %19 = getelementptr [64 x i64], ptr %0, i64 0, i64 2
  %20 = load i64, ptr %19, align 4
  store i64 %20, ptr %18, align 4
  %21 = getelementptr [64 x i64], ptr %0, i64 0, i64 4
  %22 = getelementptr [64 x i64], ptr %0, i64 0, i64 4
  %23 = load i64, ptr %22, align 4
  %24 = shl i64 %23, 9
  store i64 %24, ptr %21, align 4
  %25 = getelementptr [64 x i64], ptr %0, i64 0, i64 4
  %26 = getelementptr [64 x i64], ptr %0, i64 0, i64 1
  %27 = load i64, ptr %26, align 4
  %28 = getelementptr [64 x i64], ptr %0, i64 0, i64 4
  %29 = load i64, ptr %28, align 4
  %30 = add i64 %29, %27
  store i64 %30, ptr %25, align 4
  %31 = getelementptr [64 x i64], ptr %0, i64 0, i64 4
  %32 = getelementptr [64 x i64], ptr %0, i64 0, i64 4
  %33 = load i64, ptr %32, align 4
  %34 = shl i64 %33, 7
  store i64 %34, ptr %31, align 4
  %35 = getelementptr [64 x i64], ptr %0, i64 0, i64 4
  %36 = getelementptr [64 x i64], ptr %0, i64 0, i64 4
  %37 = load i64, ptr %36, align 4
  %38 = add i64 %37, 16711680
  store i64 %38, ptr %35, align 4
  br label %put_pixel

set_black:                                        ; preds = %label9
  %39 = getelementptr [64 x i64], ptr %0, i64 0, i64 4
  store i64 -16777216, ptr %39, align 4
  br label %put_pixel

put_pixel:                                        ; preds = %set_black, %set_color
  %40 = getelementptr [64 x i64], ptr %0, i64 0, i64 1
  %41 = load i64, ptr %40, align 4
  %42 = trunc i64 %41 to i32
  %43 = getelementptr [64 x i64], ptr %0, i64 0, i64 2
  %44 = load i64, ptr %43, align 4
  %45 = trunc i64 %44 to i32
  %46 = getelementptr [64 x i64], ptr %0, i64 0, i64 4
  %47 = load i64, ptr %46, align 4
  %48 = trunc i64 %47 to i32
  call void @simPutPixel(i32 %42, i32 %45, i32 %48)
  %49 = getelementptr [64 x i64], ptr %0, i64 0, i64 2
  %50 = getelementptr [64 x i64], ptr %0, i64 0, i64 2
  %51 = load i64, ptr %50, align 4
  %52 = add i64 %51, 1
  store i64 %52, ptr %49, align 4
  %53 = getelementptr [64 x i64], ptr %0, i64 0, i64 0
  %54 = getelementptr [64 x i64], ptr %0, i64 0, i64 2
  %55 = load i64, ptr %54, align 4
  %56 = icmp eq i64 %55, 256
  %57 = zext i1 %56 to i64
  store i64 %57, ptr %53, align 4
  %58 = getelementptr [64 x i64], ptr %0, i64 0, i64 0
  %59 = load i64, ptr %58, align 4
  %60 = trunc i64 %59 to i1
  br i1 %60, label %label9, label %label4

label4:                                           ; preds = %put_pixel
  %61 = getelementptr [64 x i64], ptr %0, i64 0, i64 1
  %62 = getelementptr [64 x i64], ptr %0, i64 0, i64 1
  %63 = load i64, ptr %62, align 4
  %64 = add i64 %63, 1
  store i64 %64, ptr %61, align 4
  %65 = getelementptr [64 x i64], ptr %0, i64 0, i64 0
  %66 = getelementptr [64 x i64], ptr %0, i64 0, i64 1
  %67 = load i64, ptr %66, align 4
  %68 = icmp eq i64 %67, 512
  %69 = zext i1 %68 to i64
  store i64 %69, ptr %65, align 4
  %70 = getelementptr [64 x i64], ptr %0, i64 0, i64 0
  %71 = load i64, ptr %70, align 4
  %72 = trunc i64 %71 to i1
  br i1 %72, label %label7, label %flush

flush:                                            ; preds = %label4
  call void @simFlush()
  %73 = getelementptr [64 x i64], ptr %0, i64 0, i64 1
  store i64 0, ptr %73, align 4
  br label %label7

label7:                                           ; preds = %flush, %label4
  br label %label1
}

declare void @simFlush()

declare void @simPutPixel(i32, i32, i32)

declare i32 @simRand()
