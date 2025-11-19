; void app() {
;   int grid[32][32];
;   int tmp_grid[32][32];
; 
;   for (int i = 0; i < 32; ++i) {
;     for (int j = 0; j < 32; ++j)
;       grid[i][j] = simRand() % 2;
;   }
; 
;   for (int step = 0; step < 10000; ++step) {
;     // Building the next generation.
;     for (int i = 0; i < 32; ++i) {
;       for (int j = 0; j < 32; ++j) {
;         int neighbors = 0;
; 
;         for (int dx = -1; dx <= 1; ++dx) {
;           for (int dy = -1; dy <= 1; ++dy) {
;             // Skip the cell itself, for which we count the neighbors.
;             if (dx == 0 && dy == 0)
;               continue;
; 
;             neighbors += grid[(i + dy + 32) % 32][(j + dx + 32) % 32];
;           }
;         }
; 
;         int cell = grid[i][j];
; 
;         // The rules of the "game of life".
;         if (cell) {
;           // The cell continues to live.
;           tmp_grid[i][j] = (neighbors == 2 || neighbors == 3) ? 1 : 0;
;         } else {
;           // The cell is dying.
;           tmp_grid[i][j] = (neighbors == 3) ? 1 : 0;
;         }
;       }
;     }
; 
;     // Making the tmp_grid the main one.
;     for (int i = 0; i < 32; ++i) {
;       for (int j = 0; j < 32; ++j)
;         grid[i][j] = tmp_grid[i][j];
;     }
; 
;     // Cleaning the screen from the previous generation.
;     for (int i = 0; i < 512; ++i) {
;       for (int j = 0; j < 512; ++j)
;         simPutPixel(j, i, 0xFFFFFFFF);
;     }
; 
;     // Drawing live cells.
;     for (int i = 0; i < 32; ++i) {
;       for (int j = 0; j < 32; ++j) {
;         if (grid[i][j]) {
; 
;           if (j > 0 && j <= 32 && i > 0 && i <= 32) {
; 
;             for (int y = 0; y < 16; ++y) {
;               for (int x = 0; x < 16; ++x)
;                 simPutPixel(j * 16 + x, i * 16 + y, 0x808080FF);
;             }
;           }
;         }
;       }
;     }
; 
;     dumpGrid(tmp_grid);
;     simFlush();
;   }
; }

app
    ALGR x0
    ALGR x1
    MEMSET x0
    MEMSET x1
    MOVi x2 0
    BRANCH init_outer_cond

init_outer_cond
    CMP_LT x10 x2 32
    BR_COND x10 init_outer_body main_loop_setup

init_outer_body
    MOVi x3 0
    BRANCH init_inner_cond

init_inner_cond
    CMP_LT x10 x3 32
    BR_COND x10 init_inner_body init_outer_inc

init_inner_body
    SIM_RAND x4
    ANDi x4 x4 1
    SET_CELL x0 x2 x3 x4
    ADDi x3 x3 1
    BRANCH init_inner_cond

init_outer_inc
    ADDi x2 x2 1
    BRANCH init_outer_cond

main_loop_setup
    MOVi x9 0
    BRANCH main_loop_cond

main_loop_cond
    CMP_LT x10 x9 10000
    BR_COND x10 main_loop_body exit_program

main_loop_body
    MOVi x2 0
    BRANCH build_outer_cond

build_outer_cond
    CMP_LT x10 x2 32
    BR_COND x10 build_outer_body copy_grid

build_outer_body
    MOVi x3 0
    BRANCH build_inner_cond

build_inner_cond
    CMP_LT x10 x3 32
    BR_COND x10 build_inner_body build_outer_inc

build_inner_body
    MOVi x5 0
    MOVi x6 -1
    BRANCH dx_loop_cond

dx_loop_cond
    CMP_LT x10 x6 2
    BR_COND x10 dx_loop_body apply_rules

dx_loop_body
    MOVi x7 -1
    BRANCH dy_loop_cond

dy_loop_cond
    CMP_LT x10 x7 2
    BR_COND x10 dy_loop_body dx_loop_inc

dy_loop_body
    CMP_EQ x10 x6 0
    CMP_EQ x11 x7 0
    AND x10 x10 x11
    BR_COND x10 dy_loop_inc calc_neighbor

calc_neighbor
    ADD x8 x2 x7
    ADDi x8 x8 32
    ANDi x8 x8 31
    ADD x11 x3 x6
    ADDi x11 x11 32
    ANDi x11 x11 31
    GET_CELL x0 x8 x11 x12
    ADD x5 x5 x12
    BRANCH dy_loop_inc

dy_loop_inc
    ADDi x7 x7 1
    BRANCH dy_loop_cond

dx_loop_inc
    ADDi x6 x6 1
    BRANCH dx_loop_cond

apply_rules
    GET_CELL x0 x2 x3 x6
    CMP_EQ x10 x6 1
    BR_COND x10 live_cell dead_cell

live_cell
    CMP_EQ x10 x5 2
    CMP_EQ x11 x5 3
    OR x10 x10 x11
    BR_COND x10 set_alive set_dead

dead_cell
    CMP_EQ x10 x5 3
    BR_COND x10 set_alive set_dead

set_alive
    MOVi x12 1
    BRANCH store_cell

set_dead
    MOVi x12 0
    BRANCH store_cell

store_cell
    SET_CELL x1 x2 x3 x12
    ADDi x3 x3 1
    BRANCH build_inner_cond

build_outer_inc
    ADDi x2 x2 1
    BRANCH build_outer_cond

copy_grid
    MEMCPY x0 x1
    
    ; Очистка экрана (заливка белым цветом)
    MOVi x13 0
    BRANCH clear_outer_cond

clear_outer_cond
    CMP_LT x10 x13 512
    BR_COND x10 clear_outer_body clear_outer_end

clear_outer_body
    MOVi x14 0
    BRANCH clear_inner_cond

clear_inner_cond
    CMP_LT x10 x14 512
    BR_COND x10 clear_inner_body clear_inner_end

clear_inner_body
    MOVi x15 -1  ; Белый цвет: 0xFFFFFFFF
    SCREEN_PUT_PIXEL x14 x13 x15
    ADDi x14 x14 1
    BRANCH clear_inner_cond

clear_inner_end
    ADDi x13 x13 1
    BRANCH clear_outer_cond

clear_outer_end
    ; Отрисовка живых клеток
    MOVi x2 0
    BRANCH draw_outer_cond

draw_outer_cond
    CMP_LT x10 x2 32
    BR_COND x10 draw_outer_body draw_outer_end

draw_outer_body
    MOVi x3 0
    BRANCH draw_inner_cond

draw_inner_cond
    CMP_LT x10 x3 32
    BR_COND x10 draw_inner_body draw_inner_end

draw_inner_body
    GET_CELL x0 x2 x3 x4
    CMP_EQ x10 x4 1
    BR_COND x10 draw_cell draw_inner_inc

draw_cell
    ; Рисуем квадрат 16x16 для живой клетки
    MOVi x13 0
    BRANCH draw_y_cond

draw_y_cond
    CMP_LT x10 x13 16
    BR_COND x10 draw_y_body draw_y_end

draw_y_body
    MOVi x14 0
    BRANCH draw_x_cond

draw_x_cond
    CMP_LT x10 x14 16
    BR_COND x10 draw_x_body draw_x_end

draw_x_body
    ; Вычисляем координаты пикселя
    SHL x5 x3 4      ; x5 = j * 16
    ADD x5 x5 x14    ; x5 = j*16 + x
    SHL x6 x2 4      ; x6 = i * 16  
    ADD x6 x6 x13    ; x6 = i*16 + y
    MOVi x15 -2139062145  ; Серый цвет: 0x808080FF
    SCREEN_PUT_PIXEL x5 x6 x15
    ADDi x14 x14 1
    BRANCH draw_x_cond

draw_x_end
    ADDi x13 x13 1
    BRANCH draw_y_cond

draw_y_end
    BRANCH draw_inner_inc

draw_inner_inc
    ADDi x3 x3 1
    BRANCH draw_inner_cond

draw_inner_end
    ADDi x2 x2 1
    BRANCH draw_outer_cond

draw_outer_end
    SCREEN_FLUSH
    ADDi x9 x9 1
    BRANCH main_loop_cond

exit_program
    EXIT
