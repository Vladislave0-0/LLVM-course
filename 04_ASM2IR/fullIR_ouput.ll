; ModuleID = 'ASM2IR'
source_filename = "ASM2IR"

@reg_file = external global [64 x i64]

define void @app() {
app:
  %0 = alloca [512 x [512 x i32]], align 4
  store ptr %0, ptr @reg_file, align 8
  %1 = alloca [512 x [512 x i32]], align 4
  store ptr %1, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 1), align 8
  %2 = load ptr, ptr @reg_file, align 8
  call void @llvm.memset.p0.i64(ptr align 16 %2, i8 0, i64 1048576, i1 false)
  %3 = load ptr, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 1), align 8
  call void @llvm.memset.p0.i64(ptr align 16 %3, i8 0, i64 1048576, i1 false)
  store i64 0, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 2), align 4
  br label %init_outer_cond

init_outer_cond:                                  ; preds = %init_outer_inc, %app
  %4 = load i64, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 2), align 4
  %5 = icmp slt i64 %4, 32
  %6 = zext i1 %5 to i64
  store i64 %6, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 10), align 4
  %7 = load i64, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 10), align 4
  %8 = trunc i64 %7 to i1
  br i1 %8, label %init_outer_body, label %main_loop_setup

init_outer_body:                                  ; preds = %init_outer_cond
  store i64 0, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 3), align 4
  br label %init_inner_cond

init_inner_cond:                                  ; preds = %init_inner_body, %init_outer_body
  %9 = load i64, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 3), align 4
  %10 = icmp slt i64 %9, 32
  %11 = zext i1 %10 to i64
  store i64 %11, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 10), align 4
  %12 = load i64, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 10), align 4
  %13 = trunc i64 %12 to i1
  br i1 %13, label %init_inner_body, label %init_outer_inc

init_inner_body:                                  ; preds = %init_inner_cond
  %14 = call i32 @simRand()
  %15 = sext i32 %14 to i64
  store i64 %15, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 4), align 4
  %16 = load i64, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 4), align 4
  %17 = and i64 %16, 1
  store i64 %17, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 4), align 4
  %18 = load i64, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 2), align 4
  %19 = load i64, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 3), align 4
  %20 = load ptr, ptr @reg_file, align 8
  %21 = getelementptr inbounds [512 x [512 x i32]], ptr %20, i64 0, i64 %18, i64 %19
  %22 = load i64, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 4), align 4
  %23 = trunc i64 %22 to i32
  store i32 %23, ptr %21, align 4
  %24 = load i64, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 3), align 4
  %25 = add i64 %24, 1
  store i64 %25, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 3), align 4
  br label %init_inner_cond

init_outer_inc:                                   ; preds = %init_inner_cond
  %26 = load i64, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 2), align 4
  %27 = add i64 %26, 1
  store i64 %27, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 2), align 4
  br label %init_outer_cond

main_loop_setup:                                  ; preds = %init_outer_cond
  store i64 0, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 9), align 4
  br label %main_loop_cond

main_loop_cond:                                   ; preds = %draw_horizontal_end, %main_loop_setup
  %28 = load i64, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 9), align 4
  %29 = icmp slt i64 %28, 10000
  %30 = zext i1 %29 to i64
  store i64 %30, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 10), align 4
  %31 = load i64, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 10), align 4
  %32 = trunc i64 %31 to i1
  br i1 %32, label %main_loop_body, label %exit_program

main_loop_body:                                   ; preds = %main_loop_cond
  store i64 0, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 2), align 4
  br label %build_outer_cond

build_outer_cond:                                 ; preds = %build_outer_inc, %main_loop_body
  %33 = load i64, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 2), align 4
  %34 = icmp slt i64 %33, 32
  %35 = zext i1 %34 to i64
  store i64 %35, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 10), align 4
  %36 = load i64, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 10), align 4
  %37 = trunc i64 %36 to i1
  br i1 %37, label %build_outer_body, label %copy_grid

build_outer_body:                                 ; preds = %build_outer_cond
  store i64 0, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 3), align 4
  br label %build_inner_cond

build_inner_cond:                                 ; preds = %store_cell, %build_outer_body
  %38 = load i64, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 3), align 4
  %39 = icmp slt i64 %38, 32
  %40 = zext i1 %39 to i64
  store i64 %40, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 10), align 4
  %41 = load i64, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 10), align 4
  %42 = trunc i64 %41 to i1
  br i1 %42, label %build_inner_body, label %build_outer_inc

build_inner_body:                                 ; preds = %build_inner_cond
  store i64 0, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 5), align 4
  store i64 -1, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 6), align 4
  br label %dx_loop_cond

dx_loop_cond:                                     ; preds = %dx_loop_inc, %build_inner_body
  %43 = load i64, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 6), align 4
  %44 = icmp slt i64 %43, 2
  %45 = zext i1 %44 to i64
  store i64 %45, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 10), align 4
  %46 = load i64, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 10), align 4
  %47 = trunc i64 %46 to i1
  br i1 %47, label %dx_loop_body, label %apply_rules

dx_loop_body:                                     ; preds = %dx_loop_cond
  store i64 -1, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 7), align 4
  br label %dy_loop_cond

dy_loop_cond:                                     ; preds = %dy_loop_inc, %dx_loop_body
  %48 = load i64, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 7), align 4
  %49 = icmp slt i64 %48, 2
  %50 = zext i1 %49 to i64
  store i64 %50, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 10), align 4
  %51 = load i64, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 10), align 4
  %52 = trunc i64 %51 to i1
  br i1 %52, label %dy_loop_body, label %dx_loop_inc

dy_loop_body:                                     ; preds = %dy_loop_cond
  %53 = load i64, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 6), align 4
  %54 = icmp eq i64 %53, 0
  %55 = zext i1 %54 to i64
  store i64 %55, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 10), align 4
  %56 = load i64, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 7), align 4
  %57 = icmp eq i64 %56, 0
  %58 = zext i1 %57 to i64
  store i64 %58, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 11), align 4
  %59 = load i64, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 10), align 4
  %60 = load i64, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 11), align 4
  %61 = and i64 %59, %60
  store i64 %61, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 10), align 4
  %62 = load i64, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 10), align 4
  %63 = trunc i64 %62 to i1
  br i1 %63, label %dy_loop_inc, label %calc_neighbor

calc_neighbor:                                    ; preds = %dy_loop_body
  %64 = load i64, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 7), align 4
  %65 = load i64, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 2), align 4
  %66 = add i64 %65, %64
  store i64 %66, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 8), align 4
  %67 = load i64, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 8), align 4
  %68 = add i64 %67, 32
  store i64 %68, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 8), align 4
  %69 = load i64, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 8), align 4
  %70 = and i64 %69, 31
  store i64 %70, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 8), align 4
  %71 = load i64, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 6), align 4
  %72 = load i64, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 3), align 4
  %73 = add i64 %72, %71
  store i64 %73, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 11), align 4
  %74 = load i64, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 11), align 4
  %75 = add i64 %74, 32
  store i64 %75, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 11), align 4
  %76 = load i64, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 11), align 4
  %77 = and i64 %76, 31
  store i64 %77, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 11), align 4
  %78 = load i64, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 8), align 4
  %79 = load i64, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 11), align 4
  %80 = load ptr, ptr @reg_file, align 8
  %81 = getelementptr inbounds [512 x [512 x i32]], ptr %80, i64 0, i64 %78, i64 %79
  %82 = load i32, ptr %81, align 4
  %83 = sext i32 %82 to i64
  store i64 %83, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 12), align 4
  %84 = load i64, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 12), align 4
  %85 = load i64, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 5), align 4
  %86 = add i64 %85, %84
  store i64 %86, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 5), align 4
  br label %dy_loop_inc

dy_loop_inc:                                      ; preds = %calc_neighbor, %dy_loop_body
  %87 = load i64, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 7), align 4
  %88 = add i64 %87, 1
  store i64 %88, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 7), align 4
  br label %dy_loop_cond

dx_loop_inc:                                      ; preds = %dy_loop_cond
  %89 = load i64, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 6), align 4
  %90 = add i64 %89, 1
  store i64 %90, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 6), align 4
  br label %dx_loop_cond

apply_rules:                                      ; preds = %dx_loop_cond
  %91 = load i64, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 2), align 4
  %92 = load i64, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 3), align 4
  %93 = load ptr, ptr @reg_file, align 8
  %94 = getelementptr inbounds [512 x [512 x i32]], ptr %93, i64 0, i64 %91, i64 %92
  %95 = load i32, ptr %94, align 4
  %96 = sext i32 %95 to i64
  store i64 %96, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 6), align 4
  %97 = load i64, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 6), align 4
  %98 = icmp eq i64 %97, 1
  %99 = zext i1 %98 to i64
  store i64 %99, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 10), align 4
  %100 = load i64, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 10), align 4
  %101 = trunc i64 %100 to i1
  br i1 %101, label %live_cell, label %dead_cell

live_cell:                                        ; preds = %apply_rules
  %102 = load i64, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 5), align 4
  %103 = icmp eq i64 %102, 2
  %104 = zext i1 %103 to i64
  store i64 %104, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 10), align 4
  %105 = load i64, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 5), align 4
  %106 = icmp eq i64 %105, 3
  %107 = zext i1 %106 to i64
  store i64 %107, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 11), align 4
  %108 = load i64, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 10), align 4
  %109 = load i64, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 11), align 4
  %110 = or i64 %108, %109
  store i64 %110, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 10), align 4
  %111 = load i64, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 10), align 4
  %112 = trunc i64 %111 to i1
  br i1 %112, label %set_alive, label %set_dead

dead_cell:                                        ; preds = %apply_rules
  %113 = load i64, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 5), align 4
  %114 = icmp eq i64 %113, 3
  %115 = zext i1 %114 to i64
  store i64 %115, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 10), align 4
  %116 = load i64, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 10), align 4
  %117 = trunc i64 %116 to i1
  br i1 %117, label %set_alive, label %set_dead

set_alive:                                        ; preds = %dead_cell, %live_cell
  store i64 1, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 12), align 4
  br label %store_cell

set_dead:                                         ; preds = %dead_cell, %live_cell
  store i64 0, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 12), align 4
  br label %store_cell

store_cell:                                       ; preds = %set_dead, %set_alive
  %118 = load i64, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 2), align 4
  %119 = load i64, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 3), align 4
  %120 = load ptr, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 1), align 8
  %121 = getelementptr inbounds [512 x [512 x i32]], ptr %120, i64 0, i64 %118, i64 %119
  %122 = load i64, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 12), align 4
  %123 = trunc i64 %122 to i32
  store i32 %123, ptr %121, align 4
  %124 = load i64, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 3), align 4
  %125 = add i64 %124, 1
  store i64 %125, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 3), align 4
  br label %build_inner_cond

build_outer_inc:                                  ; preds = %build_inner_cond
  %126 = load i64, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 2), align 4
  %127 = add i64 %126, 1
  store i64 %127, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 2), align 4
  br label %build_outer_cond

copy_grid:                                        ; preds = %build_outer_cond
  %128 = load ptr, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 1), align 8
  %129 = load ptr, ptr @reg_file, align 8
  call void @llvm.memcpy.p0.p0.i64(ptr align 16 %129, ptr align 16 %128, i64 1048576, i1 false)
  store i64 0, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 13), align 4
  br label %clear_outer_cond

clear_outer_cond:                                 ; preds = %clear_inner_end, %copy_grid
  %130 = load i64, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 13), align 4
  %131 = icmp slt i64 %130, 512
  %132 = zext i1 %131 to i64
  store i64 %132, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 10), align 4
  %133 = load i64, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 10), align 4
  %134 = trunc i64 %133 to i1
  br i1 %134, label %clear_outer_body, label %clear_outer_end

clear_outer_body:                                 ; preds = %clear_outer_cond
  store i64 0, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 14), align 4
  br label %clear_inner_cond

clear_inner_cond:                                 ; preds = %clear_inner_body, %clear_outer_body
  %135 = load i64, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 14), align 4
  %136 = icmp slt i64 %135, 512
  %137 = zext i1 %136 to i64
  store i64 %137, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 10), align 4
  %138 = load i64, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 10), align 4
  %139 = trunc i64 %138 to i1
  br i1 %139, label %clear_inner_body, label %clear_inner_end

clear_inner_body:                                 ; preds = %clear_inner_cond
  store i64 -1, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 15), align 4
  %140 = load i64, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 14), align 4
  %141 = trunc i64 %140 to i32
  %142 = load i64, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 13), align 4
  %143 = trunc i64 %142 to i32
  %144 = load i64, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 15), align 4
  %145 = trunc i64 %144 to i32
  call void @simPutPixel(i32 %141, i32 %143, i32 %145)
  %146 = load i64, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 14), align 4
  %147 = add i64 %146, 1
  store i64 %147, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 14), align 4
  br label %clear_inner_cond

clear_inner_end:                                  ; preds = %clear_inner_cond
  %148 = load i64, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 13), align 4
  %149 = add i64 %148, 1
  store i64 %149, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 13), align 4
  br label %clear_outer_cond

clear_outer_end:                                  ; preds = %clear_outer_cond
  store i64 0, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 2), align 4
  br label %draw_outer_cond

draw_outer_cond:                                  ; preds = %draw_inner_end, %clear_outer_end
  %150 = load i64, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 2), align 4
  %151 = icmp slt i64 %150, 32
  %152 = zext i1 %151 to i64
  store i64 %152, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 10), align 4
  %153 = load i64, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 10), align 4
  %154 = trunc i64 %153 to i1
  br i1 %154, label %draw_outer_body, label %draw_outer_end

draw_outer_body:                                  ; preds = %draw_outer_cond
  store i64 0, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 3), align 4
  br label %draw_inner_cond

draw_inner_cond:                                  ; preds = %draw_inner_inc, %draw_outer_body
  %155 = load i64, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 3), align 4
  %156 = icmp slt i64 %155, 32
  %157 = zext i1 %156 to i64
  store i64 %157, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 10), align 4
  %158 = load i64, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 10), align 4
  %159 = trunc i64 %158 to i1
  br i1 %159, label %draw_inner_body, label %draw_inner_end

draw_inner_body:                                  ; preds = %draw_inner_cond
  %160 = load i64, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 2), align 4
  %161 = load i64, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 3), align 4
  %162 = load ptr, ptr @reg_file, align 8
  %163 = getelementptr inbounds [512 x [512 x i32]], ptr %162, i64 0, i64 %160, i64 %161
  %164 = load i32, ptr %163, align 4
  %165 = sext i32 %164 to i64
  store i64 %165, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 4), align 4
  %166 = load i64, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 4), align 4
  %167 = icmp eq i64 %166, 1
  %168 = zext i1 %167 to i64
  store i64 %168, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 10), align 4
  %169 = load i64, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 10), align 4
  %170 = trunc i64 %169 to i1
  br i1 %170, label %draw_cell, label %draw_inner_inc

draw_cell:                                        ; preds = %draw_inner_body
  store i64 0, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 13), align 4
  br label %draw_y_cond

draw_y_cond:                                      ; preds = %draw_x_end, %draw_cell
  %171 = load i64, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 13), align 4
  %172 = icmp slt i64 %171, 16
  %173 = zext i1 %172 to i64
  store i64 %173, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 10), align 4
  %174 = load i64, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 10), align 4
  %175 = trunc i64 %174 to i1
  br i1 %175, label %draw_y_body, label %draw_y_end

draw_y_body:                                      ; preds = %draw_y_cond
  store i64 0, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 14), align 4
  br label %draw_x_cond

draw_x_cond:                                      ; preds = %draw_x_body, %draw_y_body
  %176 = load i64, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 14), align 4
  %177 = icmp slt i64 %176, 16
  %178 = zext i1 %177 to i64
  store i64 %178, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 10), align 4
  %179 = load i64, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 10), align 4
  %180 = trunc i64 %179 to i1
  br i1 %180, label %draw_x_body, label %draw_x_end

draw_x_body:                                      ; preds = %draw_x_cond
  %181 = load i64, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 3), align 4
  %182 = shl i64 %181, 4
  store i64 %182, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 5), align 4
  %183 = load i64, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 14), align 4
  %184 = load i64, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 5), align 4
  %185 = add i64 %184, %183
  store i64 %185, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 5), align 4
  %186 = load i64, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 2), align 4
  %187 = shl i64 %186, 4
  store i64 %187, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 6), align 4
  %188 = load i64, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 13), align 4
  %189 = load i64, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 6), align 4
  %190 = add i64 %189, %188
  store i64 %190, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 6), align 4
  store i64 6591981, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 15), align 4
  %191 = load i64, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 5), align 4
  %192 = trunc i64 %191 to i32
  %193 = load i64, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 6), align 4
  %194 = trunc i64 %193 to i32
  %195 = load i64, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 15), align 4
  %196 = trunc i64 %195 to i32
  call void @simPutPixel(i32 %192, i32 %194, i32 %196)
  %197 = load i64, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 14), align 4
  %198 = add i64 %197, 1
  store i64 %198, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 14), align 4
  br label %draw_x_cond

draw_x_end:                                       ; preds = %draw_x_cond
  %199 = load i64, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 13), align 4
  %200 = add i64 %199, 1
  store i64 %200, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 13), align 4
  br label %draw_y_cond

draw_y_end:                                       ; preds = %draw_y_cond
  br label %draw_inner_inc

draw_inner_inc:                                   ; preds = %draw_y_end, %draw_inner_body
  %201 = load i64, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 3), align 4
  %202 = add i64 %201, 1
  store i64 %202, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 3), align 4
  br label %draw_inner_cond

draw_inner_end:                                   ; preds = %draw_inner_cond
  %203 = load i64, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 2), align 4
  %204 = add i64 %203, 1
  store i64 %204, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 2), align 4
  br label %draw_outer_cond

draw_outer_end:                                   ; preds = %draw_outer_cond
  store i64 0, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 16), align 4
  br label %draw_vertical_cond

draw_vertical_cond:                               ; preds = %draw_vertical_inner_end, %draw_outer_end
  %205 = load i64, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 16), align 4
  %206 = icmp slt i64 %205, 32
  %207 = zext i1 %206 to i64
  store i64 %207, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 10), align 4
  %208 = load i64, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 10), align 4
  %209 = trunc i64 %208 to i1
  br i1 %209, label %draw_vertical_body, label %draw_vertical_end

draw_vertical_body:                               ; preds = %draw_vertical_cond
  %210 = load i64, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 16), align 4
  %211 = shl i64 %210, 4
  store i64 %211, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 17), align 4
  store i64 0, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 18), align 4
  br label %draw_vertical_inner_cond

draw_vertical_inner_cond:                         ; preds = %draw_vertical_inner_body, %draw_vertical_body
  %212 = load i64, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 18), align 4
  %213 = icmp slt i64 %212, 512
  %214 = zext i1 %213 to i64
  store i64 %214, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 10), align 4
  %215 = load i64, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 10), align 4
  %216 = trunc i64 %215 to i1
  br i1 %216, label %draw_vertical_inner_body, label %draw_vertical_inner_end

draw_vertical_inner_body:                         ; preds = %draw_vertical_inner_cond
  store i64 6908265, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 19), align 4
  %217 = load i64, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 17), align 4
  %218 = trunc i64 %217 to i32
  %219 = load i64, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 18), align 4
  %220 = trunc i64 %219 to i32
  %221 = load i64, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 19), align 4
  %222 = trunc i64 %221 to i32
  call void @simPutPixel(i32 %218, i32 %220, i32 %222)
  %223 = load i64, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 18), align 4
  %224 = add i64 %223, 1
  store i64 %224, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 18), align 4
  br label %draw_vertical_inner_cond

draw_vertical_inner_end:                          ; preds = %draw_vertical_inner_cond
  %225 = load i64, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 16), align 4
  %226 = add i64 %225, 1
  store i64 %226, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 16), align 4
  br label %draw_vertical_cond

draw_vertical_end:                                ; preds = %draw_vertical_cond
  store i64 0, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 16), align 4
  br label %draw_horizontal_cond

draw_horizontal_cond:                             ; preds = %draw_horizontal_inner_end, %draw_vertical_end
  %227 = load i64, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 16), align 4
  %228 = icmp slt i64 %227, 32
  %229 = zext i1 %228 to i64
  store i64 %229, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 10), align 4
  %230 = load i64, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 10), align 4
  %231 = trunc i64 %230 to i1
  br i1 %231, label %draw_horizontal_body, label %draw_horizontal_end

draw_horizontal_body:                             ; preds = %draw_horizontal_cond
  %232 = load i64, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 16), align 4
  %233 = shl i64 %232, 4
  store i64 %233, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 17), align 4
  store i64 0, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 18), align 4
  br label %draw_horizontal_inner_cond

draw_horizontal_inner_cond:                       ; preds = %draw_horizontal_inner_body, %draw_horizontal_body
  %234 = load i64, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 18), align 4
  %235 = icmp slt i64 %234, 512
  %236 = zext i1 %235 to i64
  store i64 %236, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 10), align 4
  %237 = load i64, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 10), align 4
  %238 = trunc i64 %237 to i1
  br i1 %238, label %draw_horizontal_inner_body, label %draw_horizontal_inner_end

draw_horizontal_inner_body:                       ; preds = %draw_horizontal_inner_cond
  store i64 6908265, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 19), align 4
  %239 = load i64, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 18), align 4
  %240 = trunc i64 %239 to i32
  %241 = load i64, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 17), align 4
  %242 = trunc i64 %241 to i32
  %243 = load i64, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 19), align 4
  %244 = trunc i64 %243 to i32
  call void @simPutPixel(i32 %240, i32 %242, i32 %244)
  %245 = load i64, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 18), align 4
  %246 = add i64 %245, 1
  store i64 %246, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 18), align 4
  br label %draw_horizontal_inner_cond

draw_horizontal_inner_end:                        ; preds = %draw_horizontal_inner_cond
  %247 = load i64, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 16), align 4
  %248 = add i64 %247, 1
  store i64 %248, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 16), align 4
  br label %draw_horizontal_cond

draw_horizontal_end:                              ; preds = %draw_horizontal_cond
  call void @simFlush()
  %249 = load i64, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 9), align 4
  %250 = add i64 %249, 1
  store i64 %250, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i64 0, i64 9), align 4
  br label %main_loop_cond

exit_program:                                     ; preds = %main_loop_cond
  ret void
}

declare void @simFlush()

declare void @simPutPixel(i32, i32, i32)

declare i32 @simRand()

declare void @dumpReg(i64, i64)

declare void @dumpGrid(ptr)

; Function Attrs: nocallback nofree nounwind willreturn memory(argmem: write)
declare void @llvm.memset.p0.i64(ptr nocapture writeonly, i8, i64, i1 immarg) #0

; Function Attrs: nocallback nofree nounwind willreturn memory(argmem: readwrite)
declare void @llvm.memcpy.p0.p0.i64(ptr noalias nocapture writeonly, ptr noalias nocapture readonly, i64, i1 immarg) #1

attributes #0 = { nocallback nofree nounwind willreturn memory(argmem: write) }
attributes #1 = { nocallback nofree nounwind willreturn memory(argmem: readwrite) }
