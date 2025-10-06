; ModuleID = '../01_SDL/src/app.c'
source_filename = "../01_SDL/src/app.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-i128:128-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

; Function Attrs: nounwind uwtable
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

8:                                                ; preds = %0, %125
  %9 = phi i32 [ 0, %0 ], [ %126, %125 ]
  br label %11

10:                                               ; preds = %125
  call void @llvm.lifetime.end.p0(i64 1024, ptr nonnull %2) #5
  call void @llvm.lifetime.end.p0(i64 1024, ptr nonnull %1) #5
  ret void

11:                                               ; preds = %8, %49
  %12 = phi i64 [ 0, %8 ], [ %15, %49 ]
  %13 = add nuw i64 %12, 15
  %14 = and i64 %13, 15
  %15 = add nuw nsw i64 %12, 1
  %16 = and i64 %15, 15
  %17 = getelementptr inbounds [16 x i32], ptr %1, i64 %14, i64 15
  %18 = load i32, ptr %17, align 4, !tbaa !5
  %19 = getelementptr inbounds [16 x i32], ptr %1, i64 %12, i64 15
  %20 = load i32, ptr %19, align 4, !tbaa !5
  %21 = getelementptr inbounds [16 x i32], ptr %1, i64 %16, i64 15
  %22 = load i32, ptr %21, align 4, !tbaa !5
  %23 = getelementptr inbounds [16 x i32], ptr %1, i64 %14, i64 0
  %24 = load i32, ptr %23, align 16, !tbaa !5
  %25 = getelementptr inbounds [16 x i32], ptr %1, i64 %16, i64 0
  %26 = load i32, ptr %25, align 16, !tbaa !5
  %27 = getelementptr inbounds [16 x i32], ptr %1, i64 %14, i64 1
  %28 = load i32, ptr %27, align 4, !tbaa !5
  %29 = getelementptr inbounds [16 x i32], ptr %1, i64 %12, i64 1
  %30 = load i32, ptr %29, align 4, !tbaa !5
  %31 = getelementptr inbounds [16 x i32], ptr %1, i64 %16, i64 1
  %32 = load i32, ptr %31, align 4, !tbaa !5
  %33 = add nsw i32 %20, %18
  %34 = add nsw i32 %33, %22
  %35 = add nsw i32 %34, %24
  %36 = add nsw i32 %35, %26
  %37 = add nsw i32 %36, %28
  %38 = add nsw i32 %37, %30
  %39 = add nsw i32 %38, %32
  %40 = getelementptr inbounds [16 x [16 x i32]], ptr %1, i64 0, i64 %12, i64 0
  %41 = load i32, ptr %40, align 16, !tbaa !5
  %42 = icmp eq i32 %41, 0
  %43 = icmp eq i32 %39, 3
  %44 = and i32 %39, -2
  %45 = icmp eq i32 %44, 2
  %46 = select i1 %42, i1 %43, i1 %45
  %47 = zext i1 %46 to i32
  %48 = getelementptr inbounds [16 x [16 x i32]], ptr %2, i64 0, i64 %12, i64 0
  store i32 %47, ptr %48, align 16
  br label %52

49:                                               ; preds = %52
  %50 = icmp eq i64 %15, 16
  br i1 %50, label %51, label %11, !llvm.loop !9

51:                                               ; preds = %49
  call void @llvm.memcpy.p0.p0.i64(ptr noundef nonnull align 16 dereferenceable(1024) %1, ptr noundef nonnull align 16 dereferenceable(1024) %2, i64 1024, i1 false), !tbaa !5
  br label %92

52:                                               ; preds = %11, %52
  %53 = phi i64 [ 1, %11 ], [ %67, %52 ]
  %54 = shl i64 %53, 32
  %55 = add i64 %54, -4294967296
  %56 = ashr exact i64 %55, 32
  %57 = getelementptr inbounds [16 x i32], ptr %1, i64 %14, i64 %56
  %58 = load i32, ptr %57, align 4, !tbaa !5
  %59 = getelementptr inbounds [16 x i32], ptr %1, i64 %12, i64 %56
  %60 = load i32, ptr %59, align 4, !tbaa !5
  %61 = getelementptr inbounds [16 x i32], ptr %1, i64 %16, i64 %56
  %62 = load i32, ptr %61, align 4, !tbaa !5
  %63 = getelementptr inbounds [16 x i32], ptr %1, i64 %14, i64 %53
  %64 = load i32, ptr %63, align 4, !tbaa !5
  %65 = getelementptr inbounds [16 x i32], ptr %1, i64 %16, i64 %53
  %66 = load i32, ptr %65, align 4, !tbaa !5
  %67 = add nuw nsw i64 %53, 1
  %68 = and i64 %67, 15
  %69 = getelementptr inbounds [16 x i32], ptr %1, i64 %14, i64 %68
  %70 = load i32, ptr %69, align 4, !tbaa !5
  %71 = getelementptr inbounds [16 x i32], ptr %1, i64 %12, i64 %68
  %72 = load i32, ptr %71, align 4, !tbaa !5
  %73 = getelementptr inbounds [16 x i32], ptr %1, i64 %16, i64 %68
  %74 = load i32, ptr %73, align 4, !tbaa !5
  %75 = add nsw i32 %60, %58
  %76 = add nsw i32 %75, %62
  %77 = add nsw i32 %76, %64
  %78 = add nsw i32 %77, %66
  %79 = add nsw i32 %78, %70
  %80 = add nsw i32 %79, %72
  %81 = add nsw i32 %80, %74
  %82 = getelementptr inbounds [16 x [16 x i32]], ptr %1, i64 0, i64 %12, i64 %53
  %83 = load i32, ptr %82, align 4, !tbaa !5
  %84 = icmp eq i32 %83, 0
  %85 = icmp eq i32 %81, 3
  %86 = and i32 %81, -2
  %87 = icmp eq i32 %86, 2
  %88 = select i1 %84, i1 %85, i1 %87
  %89 = zext i1 %88 to i32
  %90 = getelementptr inbounds [16 x [16 x i32]], ptr %2, i64 0, i64 %12, i64 %53
  store i32 %89, ptr %90, align 4
  %91 = icmp eq i64 %67, 16
  br i1 %91, label %49, label %52, !llvm.loop !11

92:                                               ; preds = %51, %94
  %93 = phi i32 [ %95, %94 ], [ 0, %51 ]
  br label %97

94:                                               ; preds = %97
  %95 = add nuw nsw i32 %93, 1
  %96 = icmp eq i32 %95, 128
  br i1 %96, label %101, label %92, !llvm.loop !13

97:                                               ; preds = %92, %97
  %98 = phi i32 [ 0, %92 ], [ %99, %97 ]
  tail call void @simPutPixel(i32 noundef %98, i32 noundef %93, i32 noundef -1) #5
  %99 = add nuw nsw i32 %98, 1
  %100 = icmp eq i32 %99, 128
  br i1 %100, label %94, label %97, !llvm.loop !14

101:                                              ; preds = %94, %128
  %102 = phi i64 [ %129, %128 ], [ 0, %94 ]
  %103 = trunc i64 %102 to i32
  %104 = shl i32 %103, 3
  br label %131

105:                                              ; preds = %128, %108
  %106 = phi i32 [ %109, %108 ], [ 0, %128 ]
  %107 = shl nuw nsw i32 %106, 3
  br label %111

108:                                              ; preds = %111
  %109 = add nuw nsw i32 %106, 1
  %110 = icmp eq i32 %109, 16
  br i1 %110, label %115, label %105, !llvm.loop !15

111:                                              ; preds = %111, %105
  %112 = phi i32 [ 0, %105 ], [ %113, %111 ]
  tail call void @simPutPixel(i32 noundef %107, i32 noundef %112, i32 noundef 6908265) #5
  %113 = add nuw nsw i32 %112, 1
  %114 = icmp eq i32 %113, 128
  br i1 %114, label %108, label %111, !llvm.loop !16

115:                                              ; preds = %108, %118
  %116 = phi i32 [ %119, %118 ], [ 0, %108 ]
  %117 = shl nuw nsw i32 %116, 3
  br label %121

118:                                              ; preds = %121
  %119 = add nuw nsw i32 %116, 1
  %120 = icmp eq i32 %119, 16
  br i1 %120, label %125, label %115, !llvm.loop !17

121:                                              ; preds = %121, %115
  %122 = phi i32 [ 0, %115 ], [ %123, %121 ]
  tail call void @simPutPixel(i32 noundef %122, i32 noundef %117, i32 noundef 6908265) #5
  %123 = add nuw nsw i32 %122, 1
  %124 = icmp eq i32 %123, 128
  br i1 %124, label %118, label %121, !llvm.loop !18

125:                                              ; preds = %118
  tail call void (...) @simFlush() #5
  %126 = add nuw nsw i32 %9, 1
  %127 = icmp eq i32 %126, 10000
  br i1 %127, label %10, label %8, !llvm.loop !19

128:                                              ; preds = %158
  %129 = add nuw nsw i64 %102, 1
  %130 = icmp eq i64 %129, 16
  br i1 %130, label %105, label %101, !llvm.loop !20

131:                                              ; preds = %101, %158
  %132 = phi i64 [ 0, %101 ], [ %159, %158 ]
  %133 = getelementptr inbounds [16 x [16 x i32]], ptr %1, i64 0, i64 %102, i64 %132
  %134 = load i32, ptr %133, align 4, !tbaa !5
  %135 = icmp eq i32 %134, 0
  br i1 %135, label %158, label %136

136:                                              ; preds = %131
  %137 = shl nuw nsw i64 %132, 3
  %138 = trunc i64 %137 to i32
  %139 = trunc i64 %137 to i32
  %140 = or disjoint i32 %139, 1
  %141 = trunc i64 %137 to i32
  %142 = or disjoint i32 %141, 2
  %143 = trunc i64 %137 to i32
  %144 = or disjoint i32 %143, 3
  %145 = trunc i64 %137 to i32
  %146 = or disjoint i32 %145, 4
  %147 = trunc i64 %137 to i32
  %148 = or disjoint i32 %147, 5
  %149 = trunc i64 %137 to i32
  %150 = or disjoint i32 %149, 6
  %151 = trunc i64 %137 to i32
  %152 = or disjoint i32 %151, 7
  br label %153

153:                                              ; preds = %153, %136
  %154 = phi i32 [ 0, %136 ], [ %156, %153 ]
  %155 = add nuw nsw i32 %154, %104
  tail call void @simPutPixel(i32 noundef %138, i32 noundef %155, i32 noundef -2139062017) #5
  tail call void @simPutPixel(i32 noundef %140, i32 noundef %155, i32 noundef -2139062017) #5
  tail call void @simPutPixel(i32 noundef %142, i32 noundef %155, i32 noundef -2139062017) #5
  tail call void @simPutPixel(i32 noundef %144, i32 noundef %155, i32 noundef -2139062017) #5
  tail call void @simPutPixel(i32 noundef %146, i32 noundef %155, i32 noundef -2139062017) #5
  tail call void @simPutPixel(i32 noundef %148, i32 noundef %155, i32 noundef -2139062017) #5
  tail call void @simPutPixel(i32 noundef %150, i32 noundef %155, i32 noundef -2139062017) #5
  tail call void @simPutPixel(i32 noundef %152, i32 noundef %155, i32 noundef -2139062017) #5
  %156 = add nuw nsw i32 %154, 1
  %157 = icmp eq i32 %156, 8
  br i1 %157, label %158, label %153, !llvm.loop !21

158:                                              ; preds = %153, %131
  %159 = add nuw nsw i64 %132, 1
  %160 = icmp eq i64 %159, 16
  br i1 %160, label %128, label %131, !llvm.loop !22
}

; Function Attrs: mustprogress nocallback nofree nosync nounwind willreturn memory(argmem: readwrite)
declare void @llvm.lifetime.start.p0(i64 immarg, ptr nocapture) #1

; Function Attrs: mustprogress nocallback nofree nounwind willreturn memory(argmem: write)
declare void @llvm.memset.p0.i64(ptr nocapture writeonly, i8, i64, i1 immarg) #2

; Function Attrs: mustprogress nocallback nofree nosync nounwind willreturn memory(argmem: readwrite)
declare void @llvm.lifetime.end.p0(i64 immarg, ptr nocapture) #1

declare void @simPutPixel(i32 noundef, i32 noundef, i32 noundef) local_unnamed_addr #3

declare void @simFlush(...) local_unnamed_addr #3

; Function Attrs: nocallback nofree nounwind willreturn memory(argmem: readwrite)
declare void @llvm.memcpy.p0.p0.i64(ptr noalias nocapture writeonly, ptr noalias nocapture readonly, i64, i1 immarg) #4

attributes #0 = { nounwind uwtable "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #1 = { mustprogress nocallback nofree nosync nounwind willreturn memory(argmem: readwrite) }
attributes #2 = { mustprogress nocallback nofree nounwind willreturn memory(argmem: write) }
attributes #3 = { "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #4 = { nocallback nofree nounwind willreturn memory(argmem: readwrite) }
attributes #5 = { nounwind }

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
!11 = distinct !{!11, !10, !12}
!12 = !{!"llvm.loop.peeled.count", i32 1}
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
