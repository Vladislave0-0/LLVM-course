app
    MOVi x0 -1
    BRANCH main_loop

main_loop
    INC_EQ x2 x0 10000  ; x0 += 1; x2 = (x0 == 10000)
    BR_COND x2 finish draw_grid_block

draw_grid_block
    MOVi x13 6908265
    MOVi x10 -1
    BRANCH vert_loop

vert_loop
    INC_EQ x14 x10 32   ; x10 += 1; x14 = (x10 == 32)
    BR_COND x14 horiz_start vert_loop_body

vert_loop_body
    SHL x15 x10 4
    MOVi x16 -1
    BRANCH vert_inner_loop

vert_inner_loop
    INC_EQ x18 x16 512  ; x16 += 1; x18 = (x16 == 512)
    BR_COND x18 vert_inner_end vert_inner_body

vert_inner_body
    SCREEN_PUT_PIXEL x15 x16 x13
    BRANCH vert_inner_loop

vert_inner_end
    BRANCH vert_loop

horiz_start
    MOVi x10 -1
    BRANCH horiz_loop

horiz_loop
    INC_EQ x14 x10 32   ; x10 += 1; x14 = (x10 == 32)
    BR_COND x14 draw_grid_end horiz_loop_body

horiz_loop_body
    SHL x15 x10 4
    MOVi x16 -1
    BRANCH horiz_inner_loop

horiz_inner_loop
    INC_EQ x18 x16 512  ; x16 += 1; x18 = (x16 == 512)
    BR_COND x18 horiz_inner_end horiz_inner_body

horiz_inner_body
    SCREEN_PUT_PIXEL x16 x15 x13
    BRANCH horiz_inner_loop

horiz_inner_end
    BRANCH horiz_loop

draw_grid_end
    SCREEN_FLUSH
    BRANCH main_loop

finish
    EXIT
