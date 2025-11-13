app
MOVi x1 100
MOVi x2 100
MOVi x6 0
MOVi x8 -65536
BRANCH outer_loop

outer_loop
MOVi x7 0
BRANCH inner_loop

inner_loop
ADD x3 x1 x7
ADD x4 x2 x6
SCREEN_PUT_PIXEL x3 x4 x8
ADDi x7 x7 1
CMP_LT x9 x7 100
BR_COND x9 inner_loop continue_outer

continue_outer
ADDi x6 x6 1
CMP_LT x9 x6 100
BR_COND x9 outer_loop finish

finish
SCREEN_FLUSH
EXIT
