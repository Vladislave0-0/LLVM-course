app
    MOVi x1 0
    BRANCH label1

label1
    MOVi x2 0
    BRANCH label9

label9
    SIM_RAND x3
    ANDi x3 x3 1
    CMP_EQ x0 x3 0
    BR_COND x0 set_black set_color

set_color
    MOV x4 x2
    SHL x4 x4 9
    ADD x4 x4 x1
    SHL x4 x4 7
    ADDi x4 x4 16711680
    BRANCH put_pixel

set_black
    MOVi x4 -16777216
    BRANCH put_pixel

put_pixel
    SCREEN_PUT_PIXEL x1 x2 x4

    ADDi x2 x2 1
    CMP_EQ x0 x2 256
    BR_COND x0 label9 label4

label4
    ADDi x1 x1 1
    CMP_EQ x0 x1 512
    BR_COND x0 label7 flush

flush
    SCREEN_FLUSH
    MOVi x1 0
    BRANCH label7

label7
    BRANCH label1
