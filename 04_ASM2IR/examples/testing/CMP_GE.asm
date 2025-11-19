app
    MOVi x1 10
    CMP_GE x10 x1 100
    BR_COND x10 init_outer_body exit_program

init_outer_body
    DUMP_REG x1
    BRANCH exit_program

exit_program
    EXIT
