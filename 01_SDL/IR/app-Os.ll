; ModuleID = 'app.c'
source_filename = "app.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-i128:128-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

; Function Attrs: nounwind optsize uwtable
define dso_local void @app() local_unnamed_addr #0 {
  %1 = alloca [16 x [16 x i32]], align 16
  %2 = alloca [16 x [16 x i32]], align 16
  call void @llvm.lifetime.start.p0(i64 1024, ptr nonnull %1) #5
  call void @llvm.lifetime.start.p0(i64 1024, ptr nonnull %2) #5
  call void @llvm.memset.p0.i64(ptr noundef nonnull align 16 dereferenceable(1024) %1, i8 0, i64 1024, i1 false), !tbaa !5
  %3 = getelementptr inbounds [16 x i32], ptr %1, i64 7, i64 8
  store i32 1, ptr %3, align 16, !tbaa !5
  %4 = getelementptr inbounds [16 x i32], ptr %1, i64 8, i64 9
  store i32 1, ptr %4, align 4, !tbaa !5
  %5 = getelementptr inbounds [16 x i32], ptr %1, i64 9, i64 7
  store i32 1, ptr %5, align 4, !tbaa !5
  %6 = getelementptr inbounds [16 x i32], ptr %1, i64 9, i64 8
  store i32 1, ptr %6, align 16, !tbaa !5
  %7 = getelementptr inbounds [16 x i32], ptr %1, i64 9, i64 9
  store i32 1, ptr %7, align 4, !tbaa !5
  br label %8

8:                                                ; preds = %0, %91
  %9 = phi i32 [ 0, %0 ], [ %92, %91 ]
  br label %11

10:                                               ; preds = %91
  call void @llvm.lifetime.end.p0(i64 1024, ptr nonnull %2) #5
  call void @llvm.lifetime.end.p0(i64 1024, ptr nonnull %1) #5
  ret void

11:                                               ; preds = %8, %14
  %12 = phi i64 [ 0, %8 ], [ %15, %14 ]
  %13 = trunc i64 %12 to i32
  br label %18

14:                                               ; preds = %46
  %15 = add nuw nsw i64 %12, 1
  %16 = icmp eq i64 %15, 16
  br i1 %16, label %17, label %11, !llvm.loop !9

17:                                               ; preds = %14
  call void @llvm.memcpy.p0.p0.i64(ptr noundef nonnull align 16 dereferenceable(1024) %1, ptr noundef nonnull align 16 dereferenceable(1024) %2, i64 1024, i1 false), !tbaa !5
  br label %58

18:                                               ; preds = %11, %46
  %19 = phi i64 [ 0, %11 ], [ %56, %46 ]
  %20 = trunc i64 %19 to i32
  br label %21

21:                                               ; preds = %27, %18
  %22 = phi i32 [ 0, %18 ], [ %43, %27 ]
  %23 = phi i32 [ -1, %18 ], [ %28, %27 ]
  %24 = add i32 %23, %20
  %25 = and i32 %24, 15
  %26 = zext nneg i32 %25 to i64
  br label %30

27:                                               ; preds = %42
  %28 = add nsw i32 %23, 1
  %29 = icmp eq i32 %28, 2
  br i1 %29, label %46, label %21, !llvm.loop !11

30:                                               ; preds = %42, %21
  %31 = phi i32 [ %22, %21 ], [ %43, %42 ]
  %32 = phi i32 [ -1, %21 ], [ %44, %42 ]
  %33 = or i32 %32, %23
  %34 = icmp eq i32 %33, 0
  br i1 %34, label %42, label %35

35:                                               ; preds = %30
  %36 = add i32 %32, %13
  %37 = and i32 %36, 15
  %38 = zext nneg i32 %37 to i64
  %39 = getelementptr inbounds [16 x i32], ptr %1, i64 %38, i64 %26
  %40 = load i32, ptr %39, align 4, !tbaa !5
  %41 = add nsw i32 %40, %31
  br label %42

42:                                               ; preds = %35, %30
  %43 = phi i32 [ %31, %30 ], [ %41, %35 ]
  %44 = add nsw i32 %32, 1
  %45 = icmp eq i32 %44, 2
  br i1 %45, label %27, label %30, !llvm.loop !12

46:                                               ; preds = %27
  %47 = getelementptr inbounds [16 x [16 x i32]], ptr %1, i64 0, i64 %12, i64 %19
  %48 = load i32, ptr %47, align 4, !tbaa !5
  %49 = icmp eq i32 %48, 0
  %50 = icmp eq i32 %43, 3
  %51 = and i32 %43, -2
  %52 = icmp eq i32 %51, 2
  %53 = select i1 %49, i1 %50, i1 %52
  %54 = zext i1 %53 to i32
  %55 = getelementptr inbounds [16 x [16 x i32]], ptr %2, i64 0, i64 %12, i64 %19
  store i32 %54, ptr %55, align 4
  %56 = add nuw nsw i64 %19, 1
  %57 = icmp eq i64 %56, 16
  br i1 %57, label %14, label %18, !llvm.loop !13

58:                                               ; preds = %17, %60
  %59 = phi i32 [ %61, %60 ], [ 0, %17 ]
  br label %63

60:                                               ; preds = %63
  %61 = add nuw nsw i32 %59, 1
  %62 = icmp eq i32 %61, 512
  br i1 %62, label %67, label %58, !llvm.loop !14

63:                                               ; preds = %58, %63
  %64 = phi i32 [ 0, %58 ], [ %65, %63 ]
  tail call void @simPutPixel(i32 noundef %64, i32 noundef %59, i32 noundef -1) #6
  %65 = add nuw nsw i32 %64, 1
  %66 = icmp eq i32 %65, 512
  br i1 %66, label %60, label %63, !llvm.loop !15

67:                                               ; preds = %60, %94
  %68 = phi i64 [ %95, %94 ], [ 0, %60 ]
  %69 = trunc i64 %68 to i32
  %70 = shl i32 %69, 5
  br label %97

71:                                               ; preds = %94, %74
  %72 = phi i32 [ %75, %74 ], [ 0, %94 ]
  %73 = shl nuw nsw i32 %72, 5
  br label %77

74:                                               ; preds = %77
  %75 = add nuw nsw i32 %72, 1
  %76 = icmp eq i32 %75, 16
  br i1 %76, label %81, label %71, !llvm.loop !16

77:                                               ; preds = %77, %71
  %78 = phi i32 [ 0, %71 ], [ %79, %77 ]
  tail call void @simPutPixel(i32 noundef %73, i32 noundef %78, i32 noundef 6908265) #6
  %79 = add nuw nsw i32 %78, 1
  %80 = icmp eq i32 %79, 512
  br i1 %80, label %74, label %77, !llvm.loop !17

81:                                               ; preds = %74, %84
  %82 = phi i32 [ %85, %84 ], [ 0, %74 ]
  %83 = shl nuw nsw i32 %82, 5
  br label %87

84:                                               ; preds = %87
  %85 = add nuw nsw i32 %82, 1
  %86 = icmp eq i32 %85, 16
  br i1 %86, label %91, label %81, !llvm.loop !18

87:                                               ; preds = %87, %81
  %88 = phi i32 [ 0, %81 ], [ %89, %87 ]
  tail call void @simPutPixel(i32 noundef %88, i32 noundef %83, i32 noundef 6908265) #6
  %89 = add nuw nsw i32 %88, 1
  %90 = icmp eq i32 %89, 512
  br i1 %90, label %84, label %87, !llvm.loop !19

91:                                               ; preds = %84
  tail call void (...) @simFlush() #6
  %92 = add nuw nsw i32 %9, 1
  %93 = icmp eq i32 %92, 10000
  br i1 %93, label %10, label %8, !llvm.loop !20

94:                                               ; preds = %116
  %95 = add nuw nsw i64 %68, 1
  %96 = icmp eq i64 %95, 16
  br i1 %96, label %71, label %67, !llvm.loop !21

97:                                               ; preds = %67, %116
  %98 = phi i64 [ 0, %67 ], [ %117, %116 ]
  %99 = getelementptr inbounds [16 x [16 x i32]], ptr %1, i64 0, i64 %68, i64 %98
  %100 = load i32, ptr %99, align 4, !tbaa !5
  %101 = icmp eq i32 %100, 0
  br i1 %101, label %116, label %102

102:                                              ; preds = %97
  %103 = trunc i64 %98 to i32
  %104 = shl i32 %103, 5
  br label %105

105:                                              ; preds = %108, %102
  %106 = phi i32 [ 0, %102 ], [ %109, %108 ]
  %107 = add nuw nsw i32 %106, %70
  br label %111

108:                                              ; preds = %111
  %109 = add nuw nsw i32 %106, 1
  %110 = icmp eq i32 %109, 32
  br i1 %110, label %116, label %105, !llvm.loop !22

111:                                              ; preds = %111, %105
  %112 = phi i32 [ 0, %105 ], [ %114, %111 ]
  %113 = add nuw nsw i32 %112, %104
  tail call void @simPutPixel(i32 noundef %113, i32 noundef %107, i32 noundef -2139062017) #6
  %114 = add nuw nsw i32 %112, 1
  %115 = icmp eq i32 %114, 32
  br i1 %115, label %108, label %111, !llvm.loop !23

116:                                              ; preds = %108, %97
  %117 = add nuw nsw i64 %98, 1
  %118 = icmp eq i64 %117, 16
  br i1 %118, label %94, label %97, !llvm.loop !24
}

; Function Attrs: mustprogress nocallback nofree nosync nounwind willreturn memory(argmem: readwrite)
declare void @llvm.lifetime.start.p0(i64 immarg, ptr nocapture) #1

; Function Attrs: mustprogress nocallback nofree nounwind willreturn memory(argmem: write)
declare void @llvm.memset.p0.i64(ptr nocapture writeonly, i8, i64, i1 immarg) #2

; Function Attrs: mustprogress nocallback nofree nosync nounwind willreturn memory(argmem: readwrite)
declare void @llvm.lifetime.end.p0(i64 immarg, ptr nocapture) #1

; Function Attrs: optsize
declare void @simPutPixel(i32 noundef, i32 noundef, i32 noundef) local_unnamed_addr #3

; Function Attrs: optsize
declare void @simFlush(...) local_unnamed_addr #3

; Function Attrs: nocallback nofree nounwind willreturn memory(argmem: readwrite)
declare void @llvm.memcpy.p0.p0.i64(ptr noalias nocapture writeonly, ptr noalias nocapture readonly, i64, i1 immarg) #4

attributes #0 = { nounwind optsize uwtable "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #1 = { mustprogress nocallback nofree nosync nounwind willreturn memory(argmem: readwrite) }
attributes #2 = { mustprogress nocallback nofree nounwind willreturn memory(argmem: write) }
attributes #3 = { optsize "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #4 = { nocallback nofree nounwind willreturn memory(argmem: readwrite) }
attributes #5 = { nounwind }
attributes #6 = { nounwind optsize }

!llvm.module.flags = !{!0, !1, !2, !3}
!llvm.ident = !{!4}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{i32 8, !"PIC Level", i32 2}
!2 = !{i32 7, !"PIE Level", i32 2}
!3 = !{i32 7, !"uwtable", i32 2}
!4 = !{!"Ubuntu clang version 18.1.8 (++20240731024944+3b5b5c1ec4a3-1~exp1~20240731145000.144)"}
!5 = !{!6, !6, i64 0}
!6 = !{!"int", !7, i64 0}
!7 = !{!"omnipotent char", !8, i64 0}
!8 = !{!"Simple C/C++ TBAA"}
!9 = distinct !{!9, !10}
!10 = !{!"llvm.loop.mustprogress"}
!11 = distinct !{!11, !10}
!12 = distinct !{!12, !10}
!13 = distinct !{!13, !10}
!14 = distinct !{!14, !10}
!15 = distinct !{!15, !10}
!16 = distinct !{!16, !10}
!17 = distinct !{!17, !10}
!18 = distinct !{!18, !10}
!19 = distinct !{!19, !10}
!20 = distinct !{!20, !10}
!21 = distinct !{!21, !10}
!22 = distinct !{!22, !10}
!23 = distinct !{!23, !10}
!24 = distinct !{!24, !10}
