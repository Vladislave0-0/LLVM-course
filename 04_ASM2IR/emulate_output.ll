; ModuleID = 'ASM2IR'
source_filename = "ASM2IR"

@reg_file = external global [64 x i64]

define void @app() {
app:
  call void @do_MOVi(i64 1, i64 0, i64 100, i64 140723542591344)
  call void @do_MOVi(i64 2, i64 0, i64 100, i64 140723542591344)
  call void @do_MOVi(i64 6, i64 0, i64 0, i64 140723542591344)
  call void @do_MOVi(i64 8, i64 0, i64 -65536, i64 140723542591344)
  call void @do_BRANCH(i64 8, i64 0, i64 5, i64 140723542591344)
  br label %outer_loop

outer_loop:                                       ; preds = %continue_outer, %app
  call void @do_MOVi(i64 7, i64 0, i64 0, i64 140723542591344)
  call void @do_BRANCH(i64 7, i64 0, i64 7, i64 140723542591344)
  br label %inner_loop

inner_loop:                                       ; preds = %inner_loop, %outer_loop
  call void @do_ADD(i64 3, i64 1, i64 7, i64 140723542591344)
  call void @do_ADD(i64 4, i64 2, i64 6, i64 140723542591344)
  call void @do_SCREEN_PUT_PIXEL(i64 3, i64 4, i64 8, i64 140723542591344)
  call void @do_ADDi(i64 7, i64 7, i64 1, i64 140723542591344)
  call void @do_CMP_LT(i64 9, i64 7, i64 100, i64 140723542591344)
  call void @do_BR_COND(i64 9, i64 7, i64 7, i64 13)
  %0 = load i64, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i32 0, i32 9), align 4
  %1 = trunc i64 %0 to i1
  br i1 %1, label %inner_loop, label %continue_outer

continue_outer:                                   ; preds = %inner_loop
  call void @do_ADDi(i64 6, i64 6, i64 1, i64 13)
  call void @do_CMP_LT(i64 9, i64 6, i64 100, i64 13)
  call void @do_BR_COND(i64 9, i64 6, i64 5, i64 16)
  %2 = load i64, ptr getelementptr inbounds ([64 x i64], ptr @reg_file, i32 0, i32 9), align 4
  %3 = trunc i64 %2 to i1
  br i1 %3, label %outer_loop, label %finish

finish:                                           ; preds = %continue_outer
  call void @do_SCREEN_FLUSH(i64 9, i64 6, i64 5, i64 16)
  call void @do_EXIT(i64 9, i64 6, i64 5, i64 16)
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
