; ModuleID = 'ASM2IR'
source_filename = "ASM2IR"

@reg_file = global [64 x i64] zeroinitializer

define void @app() {
app:
  call void @do_MOVi(i64 1, i64 0, i64 0, i64 140730999447696)
  call void @do_BRANCH(i64 1, i64 0, i64 2, i64 140730999447696)
  br label %label1

label1:                                           ; preds = %label7, %app
  call void @do_MOVi(i64 2, i64 0, i64 0, i64 140730999447696)
  call void @do_BRANCH(i64 2, i64 0, i64 4, i64 140730999447696)
  br label %label9

label9:                                           ; preds = %put_pixel, %label1
  call void @do_SIM_RAND(i64 3, i64 0, i64 4, i64 140730999447696)
  call void @do_ANDi(i64 3, i64 3, i64 1, i64 140730999447696)
  call void @do_CMP_EQ(i64 0, i64 3, i64 0, i64 140730999447696)
  call void @do_BR_COND(i64 0, i64 3, i64 14, i64 8)
  %0 = load i64, ptr @reg_file, align 4
  %1 = trunc i64 %0 to i1
  br i1 %1, label %set_black, label %set_color

set_color:                                        ; preds = %label9
  call void @do_MOV(i64 4, i64 2, i64 14, i64 8)
  call void @do_SHL(i64 4, i64 4, i64 9, i64 8)
  call void @do_ADD(i64 4, i64 4, i64 1, i64 8)
  call void @do_SHL(i64 4, i64 4, i64 7, i64 8)
  call void @do_ADDi(i64 4, i64 4, i64 16711680, i64 8)
  call void @do_BRANCH(i64 4, i64 4, i64 16, i64 8)
  br label %put_pixel

set_black:                                        ; preds = %label9
  call void @do_MOVi(i64 4, i64 4, i64 -16777216, i64 8)
  call void @do_BRANCH(i64 4, i64 4, i64 16, i64 8)
  br label %put_pixel

put_pixel:                                        ; preds = %set_black, %set_color
  call void @do_SCREEN_PUT_PIXEL(i64 1, i64 2, i64 4, i64 8)
  call void @do_ADDi(i64 2, i64 2, i64 1, i64 8)
  call void @do_CMP_EQ(i64 0, i64 2, i64 256, i64 8)
  call void @do_BR_COND(i64 0, i64 2, i64 4, i64 20)
  %2 = load i64, ptr @reg_file, align 4
  %3 = trunc i64 %2 to i1
  br i1 %3, label %label9, label %label4

label4:                                           ; preds = %put_pixel
  call void @do_ADDi(i64 1, i64 1, i64 1, i64 20)
  call void @do_CMP_EQ(i64 0, i64 1, i64 512, i64 20)
  call void @do_BR_COND(i64 0, i64 1, i64 26, i64 23)
  %4 = load i64, ptr @reg_file, align 4
  %5 = trunc i64 %4 to i1
  br i1 %5, label %label7, label %flush

flush:                                            ; preds = %label4
  call void @do_SCREEN_FLUSH(i64 0, i64 1, i64 26, i64 23)
  call void @do_MOVi(i64 1, i64 1, i64 0, i64 23)
  call void @do_BRANCH(i64 1, i64 1, i64 26, i64 23)
  br label %label7

label7:                                           ; preds = %flush, %label4
  call void @do_BRANCH(i64 1, i64 1, i64 2, i64 23)
  br label %label1
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