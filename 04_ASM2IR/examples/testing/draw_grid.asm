app
    MOVi x0 0
    BRANCH main_loop

main_loop
    CMP_EQ x2 x0 10000
    BR_COND x2 finish draw_grid_block

draw_grid_block
    MOVi x10 0
    MOVi x13 6908265
    BRANCH vert_loop

vert_loop
    CMP_EQ x14 x10 32
    BR_COND x14 horiz_start vert_loop_body

vert_loop_body
    SHL x15 x10 4
    MOVi x16 0
    BRANCH vert_inner_loop

vert_inner_loop
    CMP_EQ x18 x16 512
    BR_COND x18 vert_inner_end vert_inner_body

vert_inner_body
    SCREEN_PUT_PIXEL x15 x16 x13
    ADDi x16 x16 1
    BRANCH vert_inner_loop

vert_inner_end
    ADDi x10 x10 1
    BRANCH vert_loop

horiz_start
    MOVi x10 0
    BRANCH horiz_loop

horiz_loop
    CMP_EQ x14 x10 32
    BR_COND x14 draw_grid_end horiz_loop_body

horiz_loop_body
    SHL x15 x10 4
    MOVi x16 0
    BRANCH horiz_inner_loop

horiz_inner_loop
    CMP_EQ x18 x16 512
    BR_COND x18 horiz_inner_end horiz_inner_body

horiz_inner_body
    SCREEN_PUT_PIXEL x16 x15 x13
    ADDi x16 x16 1
    BRANCH horiz_inner_loop

horiz_inner_end
    ADDi x10 x10 1
    BRANCH horiz_loop

draw_grid_end
    SCREEN_FLUSH
    ADDi x0 x0 1
    BRANCH main_loop

finish
    EXIT
