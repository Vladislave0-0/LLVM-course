; ModuleID = 'ASM2IR'
source_filename = "ASM2IR"

@reg_file = external global [64 x i64]

define void @app() {
app:
  call void @do_ALGR(i64 0, i64 109426321038016, i64 14, i64 30)
  call void @do_ALGR(i64 1, i64 109426321038016, i64 14, i64 30)
  call void @do_MEMSET(i64 0, i64 109426321038016, i64 14, i64 30)
  call void @do_MEMSET(i64 1, i64 109426321038016, i64 14, i64 30)
  call void @do_MOVi(i64 2, i64 109426321038016, i64 0, i64 30)
  call void @do_BRANCH(i64 2, i64 109426321038016, i64 6, i64 30)
  br label %init_outer_cond

init_outer_cond:                                  ; preds = %init_outer_inc, %app
  call void @do_CMP_LT(i64 10, i64 2, i64 32, i64 30)
  call void @do_BR_COND(i64 10, i64 2, i64 8, i64 19)
  %0 = load i64, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i32 0, i32 10), align 4
  %1 = trunc i64 %0 to i1
  br i1 %1, label %init_outer_body, label %main_loop_setup

init_outer_body:                                  ; preds = %init_outer_cond
  call void @do_MOVi(i64 3, i64 2, i64 0, i64 19)
  call void @do_BRANCH(i64 3, i64 2, i64 10, i64 19)
  br label %init_inner_cond

init_inner_cond:                                  ; preds = %init_inner_body, %init_outer_body
  call void @do_CMP_LT(i64 10, i64 3, i64 32, i64 19)
  call void @do_BR_COND(i64 10, i64 3, i64 12, i64 17)
  %2 = load i64, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i32 0, i32 10), align 4
  %3 = trunc i64 %2 to i1
  br i1 %3, label %init_inner_body, label %init_outer_inc

init_inner_body:                                  ; preds = %init_inner_cond
  call void @do_SIM_RAND(i64 4, i64 3, i64 12, i64 17)
  call void @do_ANDi(i64 4, i64 4, i64 1, i64 17)
  call void @do_SET_CELL(i64 0, i64 2, i64 3, i64 4)
  call void @do_ADDi(i64 3, i64 3, i64 1, i64 4)
  call void @do_BRANCH(i64 3, i64 3, i64 10, i64 4)
  br label %init_inner_cond

init_outer_inc:                                   ; preds = %init_inner_cond
  call void @do_ADDi(i64 2, i64 2, i64 1, i64 4)
  call void @do_BRANCH(i64 2, i64 2, i64 6, i64 4)
  br label %init_outer_cond

main_loop_setup:                                  ; preds = %init_outer_cond
  call void @do_MOVi(i64 9, i64 2, i64 0, i64 4)
  call void @do_BRANCH(i64 9, i64 2, i64 21, i64 4)
  br label %main_loop_cond

main_loop_cond:                                   ; preds = %draw_horizontal_end, %main_loop_setup
  call void @do_CMP_LT(i64 10, i64 9, i64 10000, i64 4)
  call void @do_BR_COND(i64 10, i64 9, i64 23, i64 157)
  %4 = load i64, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i32 0, i32 10), align 4
  %5 = trunc i64 %4 to i1
  br i1 %5, label %main_loop_body, label %exit_program

main_loop_body:                                   ; preds = %main_loop_cond
  call void @do_MOVi(i64 2, i64 9, i64 0, i64 157)
  call void @do_BRANCH(i64 2, i64 9, i64 25, i64 157)
  br label %build_outer_cond

build_outer_cond:                                 ; preds = %build_outer_inc, %main_loop_body
  call void @do_CMP_LT(i64 10, i64 2, i64 32, i64 157)
  call void @do_BR_COND(i64 10, i64 2, i64 27, i64 75)
  %6 = load i64, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i32 0, i32 10), align 4
  %7 = trunc i64 %6 to i1
  br i1 %7, label %build_outer_body, label %copy_grid

build_outer_body:                                 ; preds = %build_outer_cond
  call void @do_MOVi(i64 3, i64 2, i64 0, i64 75)
  call void @do_BRANCH(i64 3, i64 2, i64 29, i64 75)
  br label %build_inner_cond

build_inner_cond:                                 ; preds = %store_cell, %build_outer_body
  call void @do_CMP_LT(i64 10, i64 3, i64 32, i64 75)
  call void @do_BR_COND(i64 10, i64 3, i64 31, i64 73)
  %8 = load i64, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i32 0, i32 10), align 4
  %9 = trunc i64 %8 to i1
  br i1 %9, label %build_inner_body, label %build_outer_inc

build_inner_body:                                 ; preds = %build_inner_cond
  call void @do_MOVi(i64 5, i64 3, i64 0, i64 73)
  call void @do_MOVi(i64 6, i64 3, i64 -1, i64 73)
  call void @do_BRANCH(i64 6, i64 3, i64 34, i64 73)
  br label %dx_loop_cond

dx_loop_cond:                                     ; preds = %dx_loop_inc, %build_inner_body
  call void @do_CMP_LT(i64 10, i64 6, i64 2, i64 73)
  call void @do_BR_COND(i64 10, i64 6, i64 36, i64 57)
  %10 = load i64, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i32 0, i32 10), align 4
  %11 = trunc i64 %10 to i1
  br i1 %11, label %dx_loop_body, label %apply_rules

dx_loop_body:                                     ; preds = %dx_loop_cond
  call void @do_MOVi(i64 7, i64 6, i64 -1, i64 57)
  call void @do_BRANCH(i64 7, i64 6, i64 38, i64 57)
  br label %dy_loop_cond

dy_loop_cond:                                     ; preds = %dy_loop_inc, %dx_loop_body
  call void @do_CMP_LT(i64 10, i64 7, i64 2, i64 57)
  call void @do_BR_COND(i64 10, i64 7, i64 40, i64 55)
  %12 = load i64, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i32 0, i32 10), align 4
  %13 = trunc i64 %12 to i1
  br i1 %13, label %dy_loop_body, label %dx_loop_inc

dy_loop_body:                                     ; preds = %dy_loop_cond
  call void @do_CMP_EQ(i64 10, i64 6, i64 0, i64 55)
  call void @do_CMP_EQ(i64 11, i64 7, i64 0, i64 55)
  call void @do_AND(i64 10, i64 10, i64 11, i64 55)
  call void @do_BR_COND(i64 10, i64 10, i64 53, i64 44)
  %14 = load i64, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i32 0, i32 10), align 4
  %15 = trunc i64 %14 to i1
  br i1 %15, label %dy_loop_inc, label %calc_neighbor

calc_neighbor:                                    ; preds = %dy_loop_body
  call void @do_ADD(i64 8, i64 2, i64 7, i64 44)
  call void @do_ADDi(i64 8, i64 8, i64 32, i64 44)
  call void @do_ANDi(i64 8, i64 8, i64 31, i64 44)
  call void @do_ADD(i64 11, i64 3, i64 6, i64 44)
  call void @do_ADDi(i64 11, i64 11, i64 32, i64 44)
  call void @do_ANDi(i64 11, i64 11, i64 31, i64 44)
  call void @do_GET_CELL(i64 0, i64 8, i64 11, i64 12)
  call void @do_ADD(i64 5, i64 5, i64 12, i64 12)
  call void @do_BRANCH(i64 5, i64 5, i64 53, i64 12)
  br label %dy_loop_inc

dy_loop_inc:                                      ; preds = %calc_neighbor, %dy_loop_body
  call void @do_ADDi(i64 7, i64 7, i64 1, i64 12)
  call void @do_BRANCH(i64 7, i64 7, i64 38, i64 12)
  br label %dy_loop_cond

dx_loop_inc:                                      ; preds = %dy_loop_cond
  call void @do_ADDi(i64 6, i64 6, i64 1, i64 12)
  call void @do_BRANCH(i64 6, i64 6, i64 34, i64 12)
  br label %dx_loop_cond

apply_rules:                                      ; preds = %dx_loop_cond
  call void @do_GET_CELL(i64 0, i64 2, i64 3, i64 6)
  call void @do_CMP_EQ(i64 10, i64 6, i64 1, i64 6)
  call void @do_BR_COND(i64 10, i64 6, i64 60, i64 64)
  %16 = load i64, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i32 0, i32 10), align 4
  %17 = trunc i64 %16 to i1
  br i1 %17, label %live_cell, label %dead_cell

live_cell:                                        ; preds = %apply_rules
  call void @do_CMP_EQ(i64 10, i64 5, i64 2, i64 64)
  call void @do_CMP_EQ(i64 11, i64 5, i64 3, i64 64)
  call void @do_OR(i64 10, i64 10, i64 11, i64 64)
  call void @do_BR_COND(i64 10, i64 10, i64 66, i64 68)
  %18 = load i64, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i32 0, i32 10), align 4
  %19 = trunc i64 %18 to i1
  br i1 %19, label %set_alive, label %set_dead

dead_cell:                                        ; preds = %apply_rules
  call void @do_CMP_EQ(i64 10, i64 5, i64 3, i64 68)
  call void @do_BR_COND(i64 10, i64 5, i64 66, i64 68)
  %20 = load i64, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i32 0, i32 10), align 4
  %21 = trunc i64 %20 to i1
  br i1 %21, label %set_alive, label %set_dead

set_alive:                                        ; preds = %dead_cell, %live_cell
  call void @do_MOVi(i64 12, i64 5, i64 1, i64 68)
  call void @do_BRANCH(i64 12, i64 5, i64 70, i64 68)
  br label %store_cell

set_dead:                                         ; preds = %dead_cell, %live_cell
  call void @do_MOVi(i64 12, i64 5, i64 0, i64 68)
  call void @do_BRANCH(i64 12, i64 5, i64 70, i64 68)
  br label %store_cell

store_cell:                                       ; preds = %set_dead, %set_alive
  call void @do_SET_CELL(i64 1, i64 2, i64 3, i64 12)
  call void @do_ADDi(i64 3, i64 3, i64 1, i64 12)
  call void @do_BRANCH(i64 3, i64 3, i64 29, i64 12)
  br label %build_inner_cond

build_outer_inc:                                  ; preds = %build_inner_cond
  call void @do_ADDi(i64 2, i64 2, i64 1, i64 12)
  call void @do_BRANCH(i64 2, i64 2, i64 25, i64 12)
  br label %build_outer_cond

copy_grid:                                        ; preds = %build_outer_cond
  call void @do_MEMCPY(i64 0, i64 1, i64 25, i64 12)
  call void @do_MOVi(i64 13, i64 1, i64 0, i64 12)
  call void @do_BRANCH(i64 13, i64 1, i64 78, i64 12)
  br label %clear_outer_cond

clear_outer_cond:                                 ; preds = %clear_inner_end, %copy_grid
  call void @do_CMP_LT(i64 10, i64 13, i64 512, i64 12)
  call void @do_BR_COND(i64 10, i64 13, i64 80, i64 90)
  %22 = load i64, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i32 0, i32 10), align 4
  %23 = trunc i64 %22 to i1
  br i1 %23, label %clear_outer_body, label %clear_outer_end

clear_outer_body:                                 ; preds = %clear_outer_cond
  call void @do_MOVi(i64 14, i64 13, i64 0, i64 90)
  call void @do_BRANCH(i64 14, i64 13, i64 82, i64 90)
  br label %clear_inner_cond

clear_inner_cond:                                 ; preds = %clear_inner_body, %clear_outer_body
  call void @do_CMP_LT(i64 10, i64 14, i64 512, i64 90)
  call void @do_BR_COND(i64 10, i64 14, i64 84, i64 88)
  %24 = load i64, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i32 0, i32 10), align 4
  %25 = trunc i64 %24 to i1
  br i1 %25, label %clear_inner_body, label %clear_inner_end

clear_inner_body:                                 ; preds = %clear_inner_cond
  call void @do_MOVi(i64 15, i64 14, i64 -1, i64 88)
  call void @do_SCREEN_PUT_PIXEL(i64 14, i64 13, i64 15, i64 88)
  call void @do_ADDi(i64 14, i64 14, i64 1, i64 88)
  call void @do_BRANCH(i64 14, i64 14, i64 82, i64 88)
  br label %clear_inner_cond

clear_inner_end:                                  ; preds = %clear_inner_cond
  call void @do_ADDi(i64 13, i64 13, i64 1, i64 88)
  call void @do_BRANCH(i64 13, i64 13, i64 78, i64 88)
  br label %clear_outer_cond

clear_outer_end:                                  ; preds = %clear_outer_cond
  call void @do_MOVi(i64 2, i64 13, i64 0, i64 88)
  call void @do_BRANCH(i64 2, i64 13, i64 92, i64 88)
  br label %draw_outer_cond

draw_outer_cond:                                  ; preds = %draw_inner_end, %clear_outer_end
  call void @do_CMP_LT(i64 10, i64 2, i64 32, i64 88)
  call void @do_BR_COND(i64 10, i64 2, i64 94, i64 124)
  %26 = load i64, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i32 0, i32 10), align 4
  %27 = trunc i64 %26 to i1
  br i1 %27, label %draw_outer_body, label %draw_outer_end

draw_outer_body:                                  ; preds = %draw_outer_cond
  call void @do_MOVi(i64 3, i64 2, i64 0, i64 124)
  call void @do_BRANCH(i64 3, i64 2, i64 96, i64 124)
  br label %draw_inner_cond

draw_inner_cond:                                  ; preds = %draw_inner_inc, %draw_outer_body
  call void @do_CMP_LT(i64 10, i64 3, i64 32, i64 124)
  call void @do_BR_COND(i64 10, i64 3, i64 98, i64 122)
  %28 = load i64, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i32 0, i32 10), align 4
  %29 = trunc i64 %28 to i1
  br i1 %29, label %draw_inner_body, label %draw_inner_end

draw_inner_body:                                  ; preds = %draw_inner_cond
  call void @do_GET_CELL(i64 0, i64 2, i64 3, i64 4)
  call void @do_CMP_EQ(i64 10, i64 4, i64 1, i64 4)
  call void @do_BR_COND(i64 10, i64 4, i64 101, i64 120)
  %30 = load i64, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i32 0, i32 10), align 4
  %31 = trunc i64 %30 to i1
  br i1 %31, label %draw_cell, label %draw_inner_inc

draw_cell:                                        ; preds = %draw_inner_body
  call void @do_MOVi(i64 13, i64 4, i64 0, i64 120)
  call void @do_BRANCH(i64 13, i64 4, i64 103, i64 120)
  br label %draw_y_cond

draw_y_cond:                                      ; preds = %draw_x_end, %draw_cell
  call void @do_CMP_LT(i64 10, i64 13, i64 16, i64 120)
  call void @do_BR_COND(i64 10, i64 13, i64 105, i64 119)
  %32 = load i64, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i32 0, i32 10), align 4
  %33 = trunc i64 %32 to i1
  br i1 %33, label %draw_y_body, label %draw_y_end

draw_y_body:                                      ; preds = %draw_y_cond
  call void @do_MOVi(i64 14, i64 13, i64 0, i64 119)
  call void @do_BRANCH(i64 14, i64 13, i64 107, i64 119)
  br label %draw_x_cond

draw_x_cond:                                      ; preds = %draw_x_body, %draw_y_body
  call void @do_CMP_LT(i64 10, i64 14, i64 16, i64 119)
  call void @do_BR_COND(i64 10, i64 14, i64 109, i64 117)
  %34 = load i64, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i32 0, i32 10), align 4
  %35 = trunc i64 %34 to i1
  br i1 %35, label %draw_x_body, label %draw_x_end

draw_x_body:                                      ; preds = %draw_x_cond
  call void @do_SHL(i64 5, i64 3, i64 4, i64 117)
  call void @do_ADD(i64 5, i64 5, i64 14, i64 117)
  call void @do_SHL(i64 6, i64 2, i64 4, i64 117)
  call void @do_ADD(i64 6, i64 6, i64 13, i64 117)
  call void @do_MOVi(i64 15, i64 6, i64 6591981, i64 117)
  call void @do_SCREEN_PUT_PIXEL(i64 5, i64 6, i64 15, i64 117)
  call void @do_ADDi(i64 14, i64 14, i64 1, i64 117)
  call void @do_BRANCH(i64 14, i64 14, i64 107, i64 117)
  br label %draw_x_cond

draw_x_end:                                       ; preds = %draw_x_cond
  call void @do_ADDi(i64 13, i64 13, i64 1, i64 117)
  call void @do_BRANCH(i64 13, i64 13, i64 103, i64 117)
  br label %draw_y_cond

draw_y_end:                                       ; preds = %draw_y_cond
  call void @do_BRANCH(i64 13, i64 13, i64 120, i64 117)
  br label %draw_inner_inc

draw_inner_inc:                                   ; preds = %draw_y_end, %draw_inner_body
  call void @do_ADDi(i64 3, i64 3, i64 1, i64 117)
  call void @do_BRANCH(i64 3, i64 3, i64 96, i64 117)
  br label %draw_inner_cond

draw_inner_end:                                   ; preds = %draw_inner_cond
  call void @do_ADDi(i64 2, i64 2, i64 1, i64 117)
  call void @do_BRANCH(i64 2, i64 2, i64 92, i64 117)
  br label %draw_outer_cond

draw_outer_end:                                   ; preds = %draw_outer_cond
  call void @do_MOVi(i64 16, i64 2, i64 0, i64 117)
  call void @do_BRANCH(i64 16, i64 2, i64 126, i64 117)
  br label %draw_vertical_cond

draw_vertical_cond:                               ; preds = %draw_vertical_inner_end, %draw_outer_end
  call void @do_CMP_LT(i64 10, i64 16, i64 32, i64 117)
  call void @do_BR_COND(i64 10, i64 16, i64 128, i64 139)
  %36 = load i64, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i32 0, i32 10), align 4
  %37 = trunc i64 %36 to i1
  br i1 %37, label %draw_vertical_body, label %draw_vertical_end

draw_vertical_body:                               ; preds = %draw_vertical_cond
  call void @do_SHL(i64 17, i64 16, i64 4, i64 139)
  call void @do_MOVi(i64 18, i64 16, i64 0, i64 139)
  call void @do_BRANCH(i64 18, i64 16, i64 131, i64 139)
  br label %draw_vertical_inner_cond

draw_vertical_inner_cond:                         ; preds = %draw_vertical_inner_body, %draw_vertical_body
  call void @do_CMP_LT(i64 10, i64 18, i64 512, i64 139)
  call void @do_BR_COND(i64 10, i64 18, i64 133, i64 137)
  %38 = load i64, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i32 0, i32 10), align 4
  %39 = trunc i64 %38 to i1
  br i1 %39, label %draw_vertical_inner_body, label %draw_vertical_inner_end

draw_vertical_inner_body:                         ; preds = %draw_vertical_inner_cond
  call void @do_MOVi(i64 19, i64 18, i64 6908265, i64 137)
  call void @do_SCREEN_PUT_PIXEL(i64 17, i64 18, i64 19, i64 137)
  call void @do_ADDi(i64 18, i64 18, i64 1, i64 137)
  call void @do_BRANCH(i64 18, i64 18, i64 131, i64 137)
  br label %draw_vertical_inner_cond

draw_vertical_inner_end:                          ; preds = %draw_vertical_inner_cond
  call void @do_ADDi(i64 16, i64 16, i64 1, i64 137)
  call void @do_BRANCH(i64 16, i64 16, i64 126, i64 137)
  br label %draw_vertical_cond

draw_vertical_end:                                ; preds = %draw_vertical_cond
  call void @do_MOVi(i64 16, i64 16, i64 0, i64 137)
  call void @do_BRANCH(i64 16, i64 16, i64 141, i64 137)
  br label %draw_horizontal_cond

draw_horizontal_cond:                             ; preds = %draw_horizontal_inner_end, %draw_vertical_end
  call void @do_CMP_LT(i64 10, i64 16, i64 32, i64 137)
  call void @do_BR_COND(i64 10, i64 16, i64 143, i64 154)
  %40 = load i64, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i32 0, i32 10), align 4
  %41 = trunc i64 %40 to i1
  br i1 %41, label %draw_horizontal_body, label %draw_horizontal_end

draw_horizontal_body:                             ; preds = %draw_horizontal_cond
  call void @do_SHL(i64 17, i64 16, i64 4, i64 154)
  call void @do_MOVi(i64 18, i64 16, i64 0, i64 154)
  call void @do_BRANCH(i64 18, i64 16, i64 146, i64 154)
  br label %draw_horizontal_inner_cond

draw_horizontal_inner_cond:                       ; preds = %draw_horizontal_inner_body, %draw_horizontal_body
  call void @do_CMP_LT(i64 10, i64 18, i64 512, i64 154)
  call void @do_BR_COND(i64 10, i64 18, i64 148, i64 152)
  %42 = load i64, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i32 0, i32 10), align 4
  %43 = trunc i64 %42 to i1
  br i1 %43, label %draw_horizontal_inner_body, label %draw_horizontal_inner_end

draw_horizontal_inner_body:                       ; preds = %draw_horizontal_inner_cond
  call void @do_MOVi(i64 19, i64 18, i64 6908265, i64 152)
  call void @do_SCREEN_PUT_PIXEL(i64 18, i64 17, i64 19, i64 152)
  call void @do_ADDi(i64 18, i64 18, i64 1, i64 152)
  call void @do_BRANCH(i64 18, i64 18, i64 146, i64 152)
  br label %draw_horizontal_inner_cond

draw_horizontal_inner_end:                        ; preds = %draw_horizontal_inner_cond
  call void @do_ADDi(i64 16, i64 16, i64 1, i64 152)
  call void @do_BRANCH(i64 16, i64 16, i64 141, i64 152)
  br label %draw_horizontal_cond

draw_horizontal_end:                              ; preds = %draw_horizontal_cond
  call void @do_SCREEN_FLUSH(i64 16, i64 16, i64 141, i64 152)
  call void @do_ADDi(i64 9, i64 9, i64 1, i64 152)
  call void @do_BRANCH(i64 9, i64 9, i64 21, i64 152)
  br label %main_loop_cond

exit_program:                                     ; preds = %main_loop_cond
  call void @do_EXIT(i64 9, i64 9, i64 21, i64 152)
  ret void
}

declare void @do_EXIT(i64, i64, i64, i64)

declare void @do_ADD(i64, i64, i64, i64)

declare void @do_ADDi(i64, i64, i64, i64)

declare void @do_MOV(i64, i64, i64, i64)

declare void @do_MOVi(i64, i64, i64, i64)

declare void @do_BR_COND(i64, i64, i64, i64)

declare void @do_BRANCH(i64, i64, i64, i64)

declare void @do_CMP_EQ(i64, i64, i64, i64)

declare void @do_ANDi(i64, i64, i64, i64)

declare void @do_SIM_RAND(i64, i64, i64, i64)

declare void @do_SCREEN_FLUSH(i64, i64, i64, i64)

declare void @do_SCREEN_PUT_PIXEL(i64, i64, i64, i64)

declare void @do_SHL(i64, i64, i64, i64)

declare void @do_CMP_LT(i64, i64, i64, i64)

declare void @do_DUMP_REG(i64, i64, i64, i64)

declare void @do_DUMP_REGS(i64, i64, i64, i64)

declare void @do_INC_EQ(i64, i64, i64, i64)

declare void @do_ALGR(i64, i64, i64, i64)

declare void @do_MEMSET(i64, i64, i64, i64)

declare void @do_MEMCPY(i64, i64, i64, i64)

declare void @do_DUMP_GRID(i64, i64, i64, i64)

declare void @do_LT_START(i64, i64, i64, i64)

declare void @do_LT_END(i64, i64, i64, i64)

declare void @do_SET_CELL(i64, i64, i64, i64)

declare void @do_GET_CELL(i64, i64, i64, i64)

declare void @do_AND(i64, i64, i64, i64)

declare void @do_OR(i64, i64, i64, i64)

declare void @do_CMP_GE(i64, i64, i64, i64)
