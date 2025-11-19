; void app() {
;   int grid[32][32];
;
;   for (int i = 0; i < 32; ++i) {
;     for (int j = 0; j < 32; ++j)
;       grid[i][j] = simRand() % 2;
;   }
;
;   dumpGrid();
;   simFlush();
; }

app
    ALGR x0
    MEMSET x0
    MOVi x1 0
    BRANCH outer_loop_cond

outer_loop_cond
    CMP_LT x5 x1 32
    BR_COND x5 outer_loop_body dump_grid

outer_loop_body
    MOVi x2 0
    BRANCH inner_loop_cond

inner_loop_cond
    CMP_LT x6 x2 32
    BR_COND x6 inner_loop_body outer_loop_inc

inner_loop_body
    SIM_RAND x3
    ANDi x4 x3 1
    SET_CELL x0 x1 x2 x4
    ADDi x2 x2 1
    BRANCH inner_loop_cond

outer_loop_inc
    ADDi x1 x1 1
    BRANCH outer_loop_cond

dump_grid
    DUMP_GRID x0
    EXIT
