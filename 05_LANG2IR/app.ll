; ModuleID = 'LANG2IR'
source_filename = "LANG2IR"

declare void @simFlush()

declare void @simPutPixel(i32, i32, i32)

declare i32 @simRand()

define i32 @app() {
entry:
  %0 = alloca i32, align 4
  %1 = alloca i32, align 4
  %2 = alloca i32, align 4
  %3 = alloca i32, align 4
  %4 = alloca i32, align 4
  %5 = alloca i32, align 4
  %6 = alloca i32, align 4
  store i32 100, ptr %6, align 4
  store i32 100, ptr %5, align 4
  store i32 0, ptr %4, align 4
  store i32 -65536, ptr %3, align 4
  br label %whileCondBB

whileCondBB:                                      ; preds = %afterWhileBB3, %entry
  %load = load i32, ptr %4, align 4
  %lt = icmp slt i32 %load, 100
  br i1 %lt, label %whileBodyBB, label %afterWhileBB

whileBodyBB:                                      ; preds = %whileCondBB
  store i32 0, ptr %2, align 4
  br label %whileCondBB1

afterWhileBB:                                     ; preds = %whileCondBB
  call void @simFlush()
  ret i32 0

whileCondBB1:                                     ; preds = %whileBodyBB2, %whileBodyBB
  %load4 = load i32, ptr %2, align 4
  %lt5 = icmp slt i32 %load4, 100
  br i1 %lt5, label %whileBodyBB2, label %afterWhileBB3

whileBodyBB2:                                     ; preds = %whileCondBB1
  %load6 = load i32, ptr %6, align 4
  %load7 = load i32, ptr %2, align 4
  %add = add i32 %load6, %load7
  store i32 %add, ptr %1, align 4
  %load8 = load i32, ptr %5, align 4
  %load9 = load i32, ptr %4, align 4
  %add10 = add i32 %load8, %load9
  store i32 %add10, ptr %0, align 4
  %load11 = load i32, ptr %1, align 4
  %load12 = load i32, ptr %0, align 4
  %load13 = load i32, ptr %3, align 4
  call void @simPutPixel(i32 %load11, i32 %load12, i32 %load13)
  %load14 = load i32, ptr %2, align 4
  %add15 = add i32 %load14, 1
  store i32 %add15, ptr %2, align 4
  br label %whileCondBB1

afterWhileBB3:                                    ; preds = %whileCondBB1
  %load16 = load i32, ptr %4, align 4
  %add17 = add i32 %load16, 1
  store i32 %add17, ptr %4, align 4
  br label %whileCondBB
}
