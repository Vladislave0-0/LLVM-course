app
    MOVi x1 11
    CMP_LT x10 x1 100
    BR_COND x10 init_outer_body exit_program

init_outer_body
    MOVi x3 0
    BRANCH exit_program

exit_program
    EXIT
