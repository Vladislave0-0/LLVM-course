; ModuleID = 'app.c'
source_filename = "app.c"

define void @app() {
  %1 = alloca [32 x [32 x i32]], align 16
  %2 = alloca [32 x [32 x i32]], align 16
  call void @llvm.lifetime.start.p0(i64 4096, ptr %1)
  call void @llvm.memset.p0.i64(ptr align 16 %1, i8 0, i64 4096, i1 false)
  call void @llvm.lifetime.start.p0(i64 4096, ptr %2)
  br label %3

3:                                                ; preds = %5, %0
  %4 = phi i64 [ 0, %0 ], [ %6, %5 ]
  br label %8

5:                                                ; preds = %8
  %6 = add i64 %4, 1
  %7 = icmp eq i64 %6, 32
  br i1 %7, label %15, label %3

8:                                                ; preds = %8, %3
  %9 = phi i64 [ 0, %3 ], [ %13, %8 ]
  %10 = call i32 @simRand()
  %11 = srem i32 %10, 2
  %12 = getelementptr inbounds [32 x i32], ptr %1, i64 %4, i64 %9
  store i32 %11, ptr %12, align 4
  %13 = add i64 %9, 1
  %14 = icmp eq i64 %13, 32
  br i1 %14, label %5, label %8

15:                                               ; preds = %98, %5
  %16 = phi i32 [ 0, %5 ], [ %99, %98 ]
  br label %18

17:                                               ; preds = %98
  call void @llvm.lifetime.end.p0(i64 4096, ptr %2)
  call void @llvm.lifetime.end.p0(i64 4096, ptr %1)
  ret void

18:                                               ; preds = %21, %15
  %19 = phi i64 [ 0, %15 ], [ %22, %21 ]
  %20 = trunc i64 %19 to i32
  br label %25

21:                                               ; preds = %53
  %22 = add i64 %19, 1
  %23 = icmp eq i64 %22, 32
  br i1 %23, label %24, label %18

24:                                               ; preds = %21
  call void @llvm.memcpy.p0.p0.i64(ptr align 16 %1, ptr align 16 %2, i64 4096, i1 false)
  br label %65

25:                                               ; preds = %53, %18
  %26 = phi i64 [ 0, %18 ], [ %63, %53 ]
  %27 = trunc i64 %26 to i32
  br label %28

28:                                               ; preds = %34, %25
  %29 = phi i32 [ 0, %25 ], [ %50, %34 ]
  %30 = phi i32 [ -1, %25 ], [ %35, %34 ]
  %31 = add i32 %30, %27
  %32 = and i32 %31, 31
  %33 = zext i32 %32 to i64
  br label %37

34:                                               ; preds = %49
  %35 = add nsw i32 %30, 1
  %36 = icmp eq i32 %35, 2
  br i1 %36, label %53, label %28

37:                                               ; preds = %49, %28
  %38 = phi i32 [ %29, %28 ], [ %50, %49 ]
  %39 = phi i32 [ -1, %28 ], [ %51, %49 ]
  %40 = or i32 %39, %30
  %41 = icmp eq i32 %40, 0
  br i1 %41, label %49, label %42

42:                                               ; preds = %37
  %43 = add i32 %39, %20
  %44 = and i32 %43, 31
  %45 = zext i32 %44 to i64
  %46 = getelementptr inbounds [32 x i32], ptr %1, i64 %45, i64 %33
  %47 = load i32, ptr %46, align 4
  %48 = add nsw i32 %47, %38
  br label %49

49:                                               ; preds = %42, %37
  %50 = phi i32 [ %38, %37 ], [ %48, %42 ]
  %51 = add nsw i32 %39, 1
  %52 = icmp eq i32 %51, 2
  br i1 %52, label %34, label %37

53:                                               ; preds = %34
  %54 = getelementptr inbounds [32 x [32 x i32]], ptr %1, i64 0, i64 %19, i64 %26
  %55 = load i32, ptr %54, align 4
  %56 = icmp eq i32 %55, 0
  %57 = icmp eq i32 %50, 3
  %58 = and i32 %50, -2
  %59 = icmp eq i32 %58, 2
  %60 = select i1 %56, i1 %57, i1 %59
  %61 = zext i1 %60 to i32
  %62 = getelementptr inbounds [32 x [32 x i32]], ptr %2, i64 0, i64 %19, i64 %26
  store i32 %61, ptr %62, align 4
  %63 = add nsw i64 %26, 1
  %64 = icmp eq i64 %63, 32
  br i1 %64, label %21, label %25

65:                                               ; preds = %67, %24
  %66 = phi i32 [ 0, %24 ], [ %68, %67 ]
  br label %70

67:                                               ; preds = %70
  %68 = add nsw i32 %66, 1
  %69 = icmp eq i32 %68, 512
  br i1 %69, label %74, label %65

70:                                               ; preds = %70, %65
  %71 = phi i32 [ 0, %65 ], [ %72, %70 ]
  call void @simPutPixel(i32 %71, i32 %66, i32 -1)
  %72 = add nsw i32 %71, 1
  %73 = icmp eq i32 %72, 512
  br i1 %73, label %67, label %70

74:                                               ; preds = %101, %67
  %75 = phi i64 [ 0, %67 ], [ %102, %101 ]
  %76 = trunc i64 %75 to i32
  %77 = shl i32 %76, 4
  br label %104

78:                                               ; preds = %101, %81
  %79 = phi i32 [ 0, %101 ], [ %82, %81 ]
  %80 = shl i32 %79, 4
  br label %84

81:                                               ; preds = %84
  %82 = add i32 %79, 1
  %83 = icmp eq i32 %82, 32
  br i1 %83, label %88, label %78

84:                                               ; preds = %84, %78
  %85 = phi i32 [ 0, %78 ], [ %86, %84 ]
  call void @simPutPixel(i32 %80, i32 %85, i32 6908265)
  %86 = add nsw i32 %85, 1
  %87 = icmp eq i32 %86, 512
  br i1 %87, label %81, label %84

88:                                               ; preds = %91, %81
  %89 = phi i32 [ 0, %81 ], [ %92, %91 ]
  %90 = shl i32 %89, 4
  br label %94

91:                                               ; preds = %94
  %92 = add i32 %89, 1
  %93 = icmp eq i32 %92, 32
  br i1 %93, label %98, label %88

94:                                               ; preds = %94, %88
  %95 = phi i32 [ 0, %88 ], [ %96, %94 ]
  call void @simPutPixel(i32 %95, i32 %90, i32 6908265)
  %96 = add nsw i32 %95, 1
  %97 = icmp eq i32 %96, 512
  br i1 %97, label %91, label %94

98:                                               ; preds = %91
  call void @simFlush()
  %99 = add nsw i32 %16, 1
  %100 = icmp eq i32 %99, 10000
  br i1 %100, label %17, label %15

101:                                              ; preds = %123
  %102 = add nsw i64 %75, 1
  %103 = icmp eq i64 %102, 32
  br i1 %103, label %78, label %74

104:                                              ; preds = %123, %74
  %105 = phi i64 [ 0, %74 ], [ %124, %123 ]
  %106 = getelementptr inbounds [32 x [32 x i32]], ptr %1, i64 0, i64 %75, i64 %105
  %107 = load i32, ptr %106, align 4
  %108 = icmp eq i32 %107, 0
  br i1 %108, label %123, label %109

109:                                              ; preds = %104
  %110 = trunc i64 %105 to i32
  %111 = shl i32 %110, 4
  br label %112

112:                                              ; preds = %115, %109
  %113 = phi i32 [ 0, %109 ], [ %116, %115 ]
  %114 = add i32 %113, %77
  br label %118

115:                                              ; preds = %118
  %116 = add i32 %113, 1
  %117 = icmp eq i32 %116, 16
  br i1 %117, label %123, label %112

118:                                              ; preds = %118, %112
  %119 = phi i32 [ 0, %112 ], [ %121, %118 ]
  %120 = add nsw i32 %119, %111
  call void @simPutPixel(i32 %120, i32 %114, i32 -2139062017)
  %121 = add nsw i32 %119, 1
  %122 = icmp eq i32 %121, 16
  br i1 %122, label %115, label %118

123:                                              ; preds = %115, %104
  %124 = add nsw i64 %105, 1
  %125 = icmp eq i64 %124, 32
  br i1 %125, label %101, label %104
}

declare i32 @simRand()

declare void @simPutPixel(i32, i32, i32)

declare void @simFlush()

; Function Attrs: nocallback nofree nosync nounwind willreturn memory(argmem: readwrite)
declare void @llvm.lifetime.start.p0(i64 immarg, ptr nocapture) #0

; Function Attrs: nocallback nofree nounwind willreturn memory(argmem: write)
declare void @llvm.memset.p0.i64(ptr nocapture writeonly, i8, i64, i1 immarg) #1

; Function Attrs: nocallback nofree nosync nounwind willreturn memory(argmem: readwrite)
declare void @llvm.lifetime.end.p0(i64 immarg, ptr nocapture) #0

; Function Attrs: nocallback nofree nounwind willreturn memory(argmem: readwrite)
declare void @llvm.memcpy.p0.p0.i64(ptr noalias nocapture writeonly, ptr noalias nocapture readonly, i64, i1 immarg) #2

attributes #0 = { nocallback nofree nosync nounwind willreturn memory(argmem: readwrite) }
attributes #1 = { nocallback nofree nounwind willreturn memory(argmem: write) }
attributes #2 = { nocallback nofree nounwind willreturn memory(argmem: readwrite) }
