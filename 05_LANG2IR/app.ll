; ModuleID = 'LANG2IR'
source_filename = "LANG2IR"

declare void @simPutPixel(i32, i32, i32)

declare void @simFlush()

declare i32 @simRand()

define i32 @validCell(i32 %0, i32 %1) {
entry:
  %2 = alloca i32, align 4
  %3 = alloca i32, align 4
  store i32 %0, ptr %3, align 4
  store i32 %1, ptr %2, align 4
  br label %ifCondBB

ifCondBB:                                         ; preds = %entry
  %load = load i32, ptr %3, align 4
  %lt = icmp slt i32 %load, 0
  br i1 %lt, label %ifBodyBB, label %afterIfBB

ifBodyBB:                                         ; preds = %ifCondBB
  ret i32 0
  br label %afterIfBB

afterIfBB:                                        ; preds = %ifBodyBB, %ifCondBB
  br label %ifCondBB1

ifCondBB1:                                        ; preds = %afterIfBB
  %load4 = load i32, ptr %2, align 4
  %lt5 = icmp slt i32 %load4, 0
  br i1 %lt5, label %ifBodyBB2, label %afterIfBB3

ifBodyBB2:                                        ; preds = %ifCondBB1
  ret i32 0
  br label %afterIfBB3

afterIfBB3:                                       ; preds = %ifBodyBB2, %ifCondBB1
  br label %ifCondBB6

ifCondBB6:                                        ; preds = %afterIfBB3
  %load9 = load i32, ptr %3, align 4
  %ge = icmp sge i32 %load9, 32
  br i1 %ge, label %ifBodyBB7, label %afterIfBB8

ifBodyBB7:                                        ; preds = %ifCondBB6
  ret i32 0
  br label %afterIfBB8

afterIfBB8:                                       ; preds = %ifBodyBB7, %ifCondBB6
  br label %ifCondBB10

ifCondBB10:                                       ; preds = %afterIfBB8
  %load13 = load i32, ptr %2, align 4
  %ge14 = icmp sge i32 %load13, 32
  br i1 %ge14, label %ifBodyBB11, label %afterIfBB12

ifBodyBB11:                                       ; preds = %ifCondBB10
  ret i32 0
  br label %afterIfBB12

afterIfBB12:                                      ; preds = %ifBodyBB11, %ifCondBB10
  ret i32 1
}

define i32 @drawLiveCell(i32 %0, i32 %1, i32 %2) {
entry:
  %3 = alloca i32, align 4
  %4 = alloca i32, align 4
  %5 = alloca i32, align 4
  %6 = alloca i32, align 4
  %7 = alloca i32, align 4
  %8 = alloca i32, align 4
  %9 = alloca i32, align 4
  store i32 %0, ptr %9, align 4
  store i32 %1, ptr %8, align 4
  store i32 %2, ptr %7, align 4
  br label %ifCondBB

ifCondBB:                                         ; preds = %entry
  %load = load i32, ptr %9, align 4
  %load1 = load i32, ptr %8, align 4
  %10 = call i32 @validCell(i32 %load, i32 %load1)
  %eq = icmp eq i32 %10, 0
  br i1 %eq, label %ifBodyBB, label %afterIfBB

ifBodyBB:                                         ; preds = %ifCondBB
  ret i32 0
  br label %afterIfBB

afterIfBB:                                        ; preds = %ifBodyBB, %ifCondBB
  %load2 = load i32, ptr %9, align 4
  %mul = mul i32 %load2, 16
  store i32 %mul, ptr %6, align 4
  %load3 = load i32, ptr %8, align 4
  %mul4 = mul i32 %load3, 16
  store i32 %mul4, ptr %5, align 4
  store i32 0, ptr %4, align 4
  br label %whileCondBB

whileCondBB:                                      ; preds = %afterWhileBB8, %afterIfBB
  %load5 = load i32, ptr %4, align 4
  %lt = icmp slt i32 %load5, 16
  br i1 %lt, label %whileBodyBB, label %afterWhileBB

whileBodyBB:                                      ; preds = %whileCondBB
  store i32 0, ptr %3, align 4
  br label %whileCondBB6

afterWhileBB:                                     ; preds = %whileCondBB
  ret i32 0

whileCondBB6:                                     ; preds = %whileBodyBB7, %whileBodyBB
  %load9 = load i32, ptr %3, align 4
  %lt10 = icmp slt i32 %load9, 16
  br i1 %lt10, label %whileBodyBB7, label %afterWhileBB8

whileBodyBB7:                                     ; preds = %whileCondBB6
  %load11 = load i32, ptr %6, align 4
  %load12 = load i32, ptr %3, align 4
  %add = add i32 %load11, %load12
  %load13 = load i32, ptr %5, align 4
  %load14 = load i32, ptr %4, align 4
  %add15 = add i32 %load13, %load14
  %load16 = load i32, ptr %7, align 4
  call void @simPutPixel(i32 %add, i32 %add15, i32 %load16)
  %load17 = load i32, ptr %3, align 4
  %add18 = add i32 %load17, 1
  store i32 %add18, ptr %3, align 4
  br label %whileCondBB6

afterWhileBB8:                                    ; preds = %whileCondBB6
  %load19 = load i32, ptr %4, align 4
  %add20 = add i32 %load19, 1
  store i32 %add20, ptr %4, align 4
  br label %whileCondBB
}

define i32 @drawGrid() {
entry:
  %0 = alloca i32, align 4
  %1 = alloca i32, align 4
  %2 = alloca i32, align 4
  %3 = alloca i32, align 4
  %4 = alloca i32, align 4
  %5 = alloca i32, align 4
  %6 = alloca i32, align 4
  %7 = alloca i32, align 4
  %8 = alloca i32, align 4
  store i32 512, ptr %8, align 4
  store i32 512, ptr %7, align 4
  store i32 6908265, ptr %6, align 4
  store i32 0, ptr %5, align 4
  br label %whileCondBB

whileCondBB:                                      ; preds = %afterWhileBB4, %entry
  %load = load i32, ptr %5, align 4
  %lt = icmp slt i32 %load, 32
  br i1 %lt, label %whileBodyBB, label %afterWhileBB

whileBodyBB:                                      ; preds = %whileCondBB
  %load1 = load i32, ptr %5, align 4
  %mul = mul i32 %load1, 16
  store i32 %mul, ptr %4, align 4
  store i32 0, ptr %3, align 4
  br label %whileCondBB2

afterWhileBB:                                     ; preds = %whileCondBB
  store i32 0, ptr %2, align 4
  br label %whileCondBB14

whileCondBB2:                                     ; preds = %whileBodyBB3, %whileBodyBB
  %load5 = load i32, ptr %3, align 4
  %load6 = load i32, ptr %8, align 4
  %lt7 = icmp slt i32 %load5, %load6
  br i1 %lt7, label %whileBodyBB3, label %afterWhileBB4

whileBodyBB3:                                     ; preds = %whileCondBB2
  %load8 = load i32, ptr %4, align 4
  %load9 = load i32, ptr %3, align 4
  %load10 = load i32, ptr %6, align 4
  call void @simPutPixel(i32 %load8, i32 %load9, i32 %load10)
  %load11 = load i32, ptr %3, align 4
  %add = add i32 %load11, 1
  store i32 %add, ptr %3, align 4
  br label %whileCondBB2

afterWhileBB4:                                    ; preds = %whileCondBB2
  %load12 = load i32, ptr %5, align 4
  %add13 = add i32 %load12, 1
  store i32 %add13, ptr %5, align 4
  br label %whileCondBB

whileCondBB14:                                    ; preds = %afterWhileBB23, %afterWhileBB
  %load17 = load i32, ptr %2, align 4
  %lt18 = icmp slt i32 %load17, 32
  br i1 %lt18, label %whileBodyBB15, label %afterWhileBB16

whileBodyBB15:                                    ; preds = %whileCondBB14
  %load19 = load i32, ptr %2, align 4
  %mul20 = mul i32 %load19, 16
  store i32 %mul20, ptr %1, align 4
  store i32 0, ptr %0, align 4
  br label %whileCondBB21

afterWhileBB16:                                   ; preds = %whileCondBB14
  ret i32 0

whileCondBB21:                                    ; preds = %whileBodyBB22, %whileBodyBB15
  %load24 = load i32, ptr %0, align 4
  %load25 = load i32, ptr %7, align 4
  %lt26 = icmp slt i32 %load24, %load25
  br i1 %lt26, label %whileBodyBB22, label %afterWhileBB23

whileBodyBB22:                                    ; preds = %whileCondBB21
  %load27 = load i32, ptr %0, align 4
  %load28 = load i32, ptr %1, align 4
  %load29 = load i32, ptr %6, align 4
  call void @simPutPixel(i32 %load27, i32 %load28, i32 %load29)
  %load30 = load i32, ptr %0, align 4
  %add31 = add i32 %load30, 1
  store i32 %add31, ptr %0, align 4
  br label %whileCondBB21

afterWhileBB23:                                   ; preds = %whileCondBB21
  %load32 = load i32, ptr %2, align 4
  %add33 = add i32 %load32, 1
  store i32 %add33, ptr %2, align 4
  br label %whileCondBB14
}

define i32 @app() {
entry:
  %0 = alloca i32, align 4
  %1 = alloca i32, align 4
  %2 = alloca i32, align 4
  %3 = alloca i32, align 4
  %4 = alloca i32, align 4
  %5 = alloca i32, align 4
  %6 = alloca i32, align 4
  %7 = alloca i32, align 4
  %8 = alloca i32, align 4
  %9 = alloca i32, align 4
  %10 = alloca i32, align 4
  %11 = alloca i32, align 4
  %12 = alloca i32, align 4
  %13 = alloca i32, align 4
  %14 = alloca i32, align 4
  %15 = alloca i32, align 4
  %16 = alloca i32, align 4
  %17 = alloca i32, align 4
  %18 = alloca i32, align 4
  %19 = alloca [32 x [32 x i32]], align 4
  %20 = alloca [32 x [32 x i32]], align 4
  %21 = alloca i32, align 4
  %22 = alloca i32, align 4
  %23 = alloca i32, align 4
  %24 = alloca i32, align 4
  store i32 512, ptr %24, align 4
  store i32 512, ptr %23, align 4
  store i32 6591981, ptr %22, align 4
  store i32 -1, ptr %21, align 4
  store i32 0, ptr %18, align 4
  br label %whileCondBB

whileCondBB:                                      ; preds = %afterWhileBB3, %entry
  %load = load i32, ptr %18, align 4
  %lt = icmp slt i32 %load, 32
  br i1 %lt, label %whileBodyBB, label %afterWhileBB

whileBodyBB:                                      ; preds = %whileCondBB
  store i32 0, ptr %17, align 4
  br label %whileCondBB1

afterWhileBB:                                     ; preds = %whileCondBB
  store i32 0, ptr %16, align 4
  br label %whileCondBB11

whileCondBB1:                                     ; preds = %whileBodyBB2, %whileBodyBB
  %load4 = load i32, ptr %17, align 4
  %lt5 = icmp slt i32 %load4, 32
  br i1 %lt5, label %whileBodyBB2, label %afterWhileBB3

whileBodyBB2:                                     ; preds = %whileCondBB1
  %load6 = load i32, ptr %18, align 4
  %load7 = load i32, ptr %17, align 4
  %25 = getelementptr [32 x [32 x i32]], ptr %20, i32 0, i32 %load6, i32 %load7
  %26 = call i32 @simRand()
  %rem = srem i32 %26, 2
  store i32 %rem, ptr %25, align 4
  %load8 = load i32, ptr %17, align 4
  %add = add i32 %load8, 1
  store i32 %add, ptr %17, align 4
  br label %whileCondBB1

afterWhileBB3:                                    ; preds = %whileCondBB1
  %load9 = load i32, ptr %18, align 4
  %add10 = add i32 %load9, 1
  store i32 %add10, ptr %18, align 4
  br label %whileCondBB

whileCondBB11:                                    ; preds = %afterWhileBB135, %afterWhileBB
  %load14 = load i32, ptr %16, align 4
  %lt15 = icmp slt i32 %load14, 10000
  br i1 %lt15, label %whileBodyBB12, label %afterWhileBB13

whileBodyBB12:                                    ; preds = %whileCondBB11
  store i32 0, ptr %15, align 4
  br label %whileCondBB16

afterWhileBB13:                                   ; preds = %whileCondBB11
  ret i32 0

whileCondBB16:                                    ; preds = %afterWhileBB23, %whileBodyBB12
  %load19 = load i32, ptr %15, align 4
  %lt20 = icmp slt i32 %load19, 32
  br i1 %lt20, label %whileBodyBB17, label %afterWhileBB18

whileBodyBB17:                                    ; preds = %whileCondBB16
  store i32 0, ptr %14, align 4
  br label %whileCondBB21

afterWhileBB18:                                   ; preds = %whileCondBB16
  store i32 0, ptr %5, align 4
  br label %whileCondBB95

whileCondBB21:                                    ; preds = %afterElseBB, %whileBodyBB17
  %load24 = load i32, ptr %14, align 4
  %lt25 = icmp slt i32 %load24, 32
  br i1 %lt25, label %whileBodyBB22, label %afterWhileBB23

whileBodyBB22:                                    ; preds = %whileCondBB21
  store i32 0, ptr %13, align 4
  store i32 -1, ptr %12, align 4
  br label %whileCondBB26

afterWhileBB23:                                   ; preds = %whileCondBB21
  %load93 = load i32, ptr %15, align 4
  %add94 = add i32 %load93, 1
  store i32 %add94, ptr %15, align 4
  br label %whileCondBB16

whileCondBB26:                                    ; preds = %afterWhileBB32, %whileBodyBB22
  %load29 = load i32, ptr %12, align 4
  %le = icmp sle i32 %load29, 1
  br i1 %le, label %whileBodyBB27, label %afterWhileBB28

whileBodyBB27:                                    ; preds = %whileCondBB26
  store i32 -1, ptr %11, align 4
  br label %whileCondBB30

afterWhileBB28:                                   ; preds = %whileCondBB26
  %load66 = load i32, ptr %15, align 4
  %load67 = load i32, ptr %14, align 4
  %27 = getelementptr [32 x [32 x i32]], ptr %20, i32 0, i32 %load66, i32 %load67
  %array_load68 = load i32, ptr %27, align 4
  store i32 %array_load68, ptr %7, align 4
  store i32 0, ptr %6, align 4
  br label %ifCondBB69

whileCondBB30:                                    ; preds = %afterIfBB43, %whileBodyBB27
  %load33 = load i32, ptr %11, align 4
  %le34 = icmp sle i32 %load33, 1
  br i1 %le34, label %whileBodyBB31, label %afterWhileBB32

whileBodyBB31:                                    ; preds = %whileCondBB30
  store i32 0, ptr %10, align 4
  br label %ifCondBB

afterWhileBB32:                                   ; preds = %whileCondBB30
  %load64 = load i32, ptr %12, align 4
  %add65 = add i32 %load64, 1
  store i32 %add65, ptr %12, align 4
  br label %whileCondBB26

ifCondBB:                                         ; preds = %whileBodyBB31
  %load35 = load i32, ptr %12, align 4
  %eq = icmp eq i32 %load35, 0
  br i1 %eq, label %ifBodyBB, label %afterIfBB

ifBodyBB:                                         ; preds = %ifCondBB
  br label %ifCondBB36

afterIfBB:                                        ; preds = %afterIfBB38, %ifCondBB
  br label %ifCondBB41

ifCondBB36:                                       ; preds = %ifBodyBB
  %load39 = load i32, ptr %11, align 4
  %eq40 = icmp eq i32 %load39, 0
  br i1 %eq40, label %ifBodyBB37, label %afterIfBB38

ifBodyBB37:                                       ; preds = %ifCondBB36
  store i32 1, ptr %10, align 4
  br label %afterIfBB38

afterIfBB38:                                      ; preds = %ifBodyBB37, %ifCondBB36
  br label %afterIfBB

ifCondBB41:                                       ; preds = %afterIfBB
  %load44 = load i32, ptr %10, align 4
  %eq45 = icmp eq i32 %load44, 0
  br i1 %eq45, label %ifBodyBB42, label %afterIfBB43

ifBodyBB42:                                       ; preds = %ifCondBB41
  %load46 = load i32, ptr %14, align 4
  %load47 = load i32, ptr %12, align 4
  %add48 = add i32 %load46, %load47
  store i32 %add48, ptr %9, align 4
  %load49 = load i32, ptr %15, align 4
  %load50 = load i32, ptr %11, align 4
  %add51 = add i32 %load49, %load50
  store i32 %add51, ptr %8, align 4
  %load52 = load i32, ptr %9, align 4
  %add53 = add i32 %load52, 32
  %rem54 = srem i32 %add53, 32
  store i32 %rem54, ptr %9, align 4
  %load55 = load i32, ptr %8, align 4
  %add56 = add i32 %load55, 32
  %rem57 = srem i32 %add56, 32
  store i32 %rem57, ptr %8, align 4
  %load58 = load i32, ptr %13, align 4
  %load59 = load i32, ptr %8, align 4
  %load60 = load i32, ptr %9, align 4
  %28 = getelementptr [32 x [32 x i32]], ptr %20, i32 0, i32 %load59, i32 %load60
  %array_load = load i32, ptr %28, align 4
  %add61 = add i32 %load58, %array_load
  store i32 %add61, ptr %13, align 4
  br label %afterIfBB43

afterIfBB43:                                      ; preds = %ifBodyBB42, %ifCondBB41
  %load62 = load i32, ptr %11, align 4
  %add63 = add i32 %load62, 1
  store i32 %add63, ptr %11, align 4
  br label %whileCondBB30

ifCondBB69:                                       ; preds = %afterWhileBB28
  %load71 = load i32, ptr %7, align 4
  %eq72 = icmp eq i32 %load71, 1
  br i1 %eq72, label %ifBodyBB70, label %elseBodyBB

ifBodyBB70:                                       ; preds = %ifCondBB69
  br label %ifCondBB73

elseBodyBB:                                       ; preds = %afterIfBB80, %ifCondBB69
  br label %ifCondBB83

ifCondBB73:                                       ; preds = %ifBodyBB70
  %load76 = load i32, ptr %13, align 4
  %eq77 = icmp eq i32 %load76, 2
  br i1 %eq77, label %ifBodyBB74, label %afterIfBB75

ifBodyBB74:                                       ; preds = %ifCondBB73
  store i32 1, ptr %6, align 4
  br label %afterIfBB75

afterIfBB75:                                      ; preds = %ifBodyBB74, %ifCondBB73
  br label %ifCondBB78

ifCondBB78:                                       ; preds = %afterIfBB75
  %load81 = load i32, ptr %13, align 4
  %eq82 = icmp eq i32 %load81, 3
  br i1 %eq82, label %ifBodyBB79, label %afterIfBB80

ifBodyBB79:                                       ; preds = %ifCondBB78
  store i32 1, ptr %6, align 4
  br label %afterIfBB80

afterIfBB80:                                      ; preds = %ifBodyBB79, %ifCondBB78
  br label %elseBodyBB

ifCondBB83:                                       ; preds = %elseBodyBB
  %load86 = load i32, ptr %13, align 4
  %eq87 = icmp eq i32 %load86, 3
  br i1 %eq87, label %ifBodyBB84, label %afterIfBB85

ifBodyBB84:                                       ; preds = %ifCondBB83
  store i32 1, ptr %6, align 4
  br label %afterIfBB85

afterIfBB85:                                      ; preds = %ifBodyBB84, %ifCondBB83
  br label %afterElseBB

afterElseBB:                                      ; preds = %afterIfBB85
  %load88 = load i32, ptr %15, align 4
  %load89 = load i32, ptr %14, align 4
  %29 = getelementptr [32 x [32 x i32]], ptr %19, i32 0, i32 %load88, i32 %load89
  %load90 = load i32, ptr %6, align 4
  store i32 %load90, ptr %29, align 4
  %load91 = load i32, ptr %14, align 4
  %add92 = add i32 %load91, 1
  store i32 %add92, ptr %14, align 4
  br label %whileCondBB21

whileCondBB95:                                    ; preds = %afterWhileBB102, %afterWhileBB18
  %load98 = load i32, ptr %5, align 4
  %lt99 = icmp slt i32 %load98, 32
  br i1 %lt99, label %whileBodyBB96, label %afterWhileBB97

whileBodyBB96:                                    ; preds = %whileCondBB95
  store i32 0, ptr %4, align 4
  br label %whileCondBB100

afterWhileBB97:                                   ; preds = %whileCondBB95
  store i32 0, ptr %3, align 4
  br label %whileCondBB114

whileCondBB100:                                   ; preds = %whileBodyBB101, %whileBodyBB96
  %load103 = load i32, ptr %4, align 4
  %lt104 = icmp slt i32 %load103, 32
  br i1 %lt104, label %whileBodyBB101, label %afterWhileBB102

whileBodyBB101:                                   ; preds = %whileCondBB100
  %load105 = load i32, ptr %5, align 4
  %load106 = load i32, ptr %4, align 4
  %30 = getelementptr [32 x [32 x i32]], ptr %20, i32 0, i32 %load105, i32 %load106
  %load107 = load i32, ptr %5, align 4
  %load108 = load i32, ptr %4, align 4
  %31 = getelementptr [32 x [32 x i32]], ptr %19, i32 0, i32 %load107, i32 %load108
  %array_load109 = load i32, ptr %31, align 4
  store i32 %array_load109, ptr %30, align 4
  %load110 = load i32, ptr %4, align 4
  %add111 = add i32 %load110, 1
  store i32 %add111, ptr %4, align 4
  br label %whileCondBB100

afterWhileBB102:                                  ; preds = %whileCondBB100
  %load112 = load i32, ptr %5, align 4
  %add113 = add i32 %load112, 1
  store i32 %add113, ptr %5, align 4
  br label %whileCondBB95

whileCondBB114:                                   ; preds = %afterWhileBB122, %afterWhileBB97
  %load117 = load i32, ptr %3, align 4
  %load118 = load i32, ptr %23, align 4
  %lt119 = icmp slt i32 %load117, %load118
  br i1 %lt119, label %whileBodyBB115, label %afterWhileBB116

whileBodyBB115:                                   ; preds = %whileCondBB114
  store i32 0, ptr %2, align 4
  br label %whileCondBB120

afterWhileBB116:                                  ; preds = %whileCondBB114
  store i32 0, ptr %1, align 4
  br label %whileCondBB133

whileCondBB120:                                   ; preds = %whileBodyBB121, %whileBodyBB115
  %load123 = load i32, ptr %2, align 4
  %load124 = load i32, ptr %24, align 4
  %lt125 = icmp slt i32 %load123, %load124
  br i1 %lt125, label %whileBodyBB121, label %afterWhileBB122

whileBodyBB121:                                   ; preds = %whileCondBB120
  %load126 = load i32, ptr %2, align 4
  %load127 = load i32, ptr %3, align 4
  %load128 = load i32, ptr %21, align 4
  call void @simPutPixel(i32 %load126, i32 %load127, i32 %load128)
  %load129 = load i32, ptr %2, align 4
  %add130 = add i32 %load129, 1
  store i32 %add130, ptr %2, align 4
  br label %whileCondBB120

afterWhileBB122:                                  ; preds = %whileCondBB120
  %load131 = load i32, ptr %3, align 4
  %add132 = add i32 %load131, 1
  store i32 %add132, ptr %3, align 4
  br label %whileCondBB114

whileCondBB133:                                   ; preds = %afterWhileBB140, %afterWhileBB116
  %load136 = load i32, ptr %1, align 4
  %lt137 = icmp slt i32 %load136, 32
  br i1 %lt137, label %whileBodyBB134, label %afterWhileBB135

whileBodyBB134:                                   ; preds = %whileCondBB133
  store i32 0, ptr %0, align 4
  br label %whileCondBB138

afterWhileBB135:                                  ; preds = %whileCondBB133
  %32 = call i32 @drawGrid()
  call void @simFlush()
  %load157 = load i32, ptr %16, align 4
  %add158 = add i32 %load157, 1
  store i32 %add158, ptr %16, align 4
  br label %whileCondBB11

whileCondBB138:                                   ; preds = %afterIfBB145, %whileBodyBB134
  %load141 = load i32, ptr %0, align 4
  %lt142 = icmp slt i32 %load141, 32
  br i1 %lt142, label %whileBodyBB139, label %afterWhileBB140

whileBodyBB139:                                   ; preds = %whileCondBB138
  br label %ifCondBB143

afterWhileBB140:                                  ; preds = %whileCondBB138
  %load155 = load i32, ptr %1, align 4
  %add156 = add i32 %load155, 1
  store i32 %add156, ptr %1, align 4
  br label %whileCondBB133

ifCondBB143:                                      ; preds = %whileBodyBB139
  %load146 = load i32, ptr %1, align 4
  %load147 = load i32, ptr %0, align 4
  %33 = getelementptr [32 x [32 x i32]], ptr %20, i32 0, i32 %load146, i32 %load147
  %array_load148 = load i32, ptr %33, align 4
  %eq149 = icmp eq i32 %array_load148, 1
  br i1 %eq149, label %ifBodyBB144, label %afterIfBB145

ifBodyBB144:                                      ; preds = %ifCondBB143
  %load150 = load i32, ptr %0, align 4
  %load151 = load i32, ptr %1, align 4
  %load152 = load i32, ptr %22, align 4
  %34 = call i32 @drawLiveCell(i32 %load150, i32 %load151, i32 %load152)
  br label %afterIfBB145

afterIfBB145:                                     ; preds = %ifBodyBB144, %ifCondBB143
  %load153 = load i32, ptr %0, align 4
  %add154 = add i32 %load153, 1
  store i32 %add154, ptr %0, align 4
  br label %whileCondBB138
}
