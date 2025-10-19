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
  %10 = call i32 (...) @simRand()
  %11 = srem i32 %10, 2
  %12 = getelementptr inbounds [32 x i32], ptr %1, i64 %4, i64 %9
  store i32 %11, ptr %12, align 4
  %13 = add i64 %9, 1
  %14 = icmp eq i64 %13, 32
  br i1 %14, label %5, label %8

15:                                               ; preds = %5
  %16 = phi i32 [ 0, %5 ]
  br label %18

17:                                               ; No predecessors!
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
  %30 = phi i32 [ -1, %25 ], [ %35, %49 ]
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

74:                                               ; preds = %67

75:                                               ; No predecessors!

76:                                               ; No predecessors!

77:                                               ; No predecessors!

78:                                               ; No predecessors!

79:                                               ; No predecessors!

80:                                               ; No predecessors!

81:                                               ; No predecessors!

82:                                               ; No predecessors!

83:                                               ; No predecessors!

84:                                               ; No predecessors!

85:                                               ; No predecessors!

86:                                               ; No predecessors!

87:                                               ; No predecessors!

88:                                               ; No predecessors!
}

declare i32 @simRand(...)

declare void @simPutPixel(i32, i32, i32)

declare void @simFlush(...)

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

