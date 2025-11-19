; // Colors.
; #define DEAD_CLR 0xFFFFFFFF  // white
; #define ALIVE_CLR 0x808080FF // blue
; #define GRID_CLR 0x696969    // dark grey
; 
; static inline int validCell(int x, int y) {
;   if (x < 0 || x >= 32 || y < 0 || y >= 32)
;     return 0;
; 
;   return 1;
; }
; 
; // The function was used to count the number of living neighbors.
; static int countNeighbors(int x, int y, int grid[][32]) {
;   int count = 0;
; 
;   for (int dx = -1; dx <= 1; ++dx) {
;     for (int dy = -1; dy <= 1; ++dy) {
;       // Skip the cell itself, for which we count the neighbors.
;       if (dx == 0 && dy == 0)
;         continue;
; 
;       int nx = x + dx;
;       int ny = y + dy;
; 
;       nx = (nx + 32) % 32;
;       ny = (ny + 32) % 32;
; 
;       count += grid[ny][nx];
;     }
;   }
; 
;   return count;
; }
; 
; // A function that renders a live cell.
; static void drawLiveCell(int grid_x, int grid_y, int color) {
;   if (!validCell(grid_x, grid_y))
;     return;
; 
;   int start_x = grid_x * 16;
;   int start_y = grid_y * 16;
; 
;   for (int y = 0; y < 16; ++y) {
;     for (int x = 0; x < 16; ++x)
;       simPutPixel(start_x + x, start_y + y, color);
;   }
; }
; 
; // The function that renders the grid lines.
; static void drawGrid() {
;   for (int x = 0; x < 32; ++x) {
;     int line_x = x * 16;
; 
;     for (int y = 0; y < SIM_Y_SIZE; ++y)
;       simPutPixel(line_x, y, GRID_CLR);
;   }
; 
;   for (int y = 0; y < 32; ++y) {
;     int line_y = y * 16;
; 
;     for (int x = 0; x < SIM_X_SIZE; ++x)
;       simPutPixel(x, line_y, GRID_CLR);
;   }
; }
; 
; void app() {
;   int grid[32][32] = {0};
;   int tmp_grid[32][32] = {0};
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
;         int neighbors = countNeighbors(j, i, grid);
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
;     for (int i = 0; i < SIM_Y_SIZE; ++i) {
;       for (int j = 0; j < SIM_X_SIZE; ++j)
;         simPutPixel(j, i, DEAD_CLR);
;     }
; 
;     // Drawing live cells.
;     for (int i = 0; i < 32; ++i) {
;       for (int j = 0; j < 32; ++j) {
;         if (grid[i][j])
;           drawLiveCell(j, i, ALIVE_CLR);
;       }
;     }
; 
;     drawGrid();
;     simFlush();
;   }
; }

; ======================================================================

app
    ; Выделение памяти под две сетки 32x32
    ; x0 = grid (текущее поколение), x1 = tmp_grid (следующее поколение)
    ALGR x0
    ALGR x1
    MEMSET x0
    MEMSET x1
    
    ; Инициализация grid случайными значениями (0 или 1)
    MOVi x2 0                      ; i = 0
    BRANCH init_outer_cond

init_outer_cond
    CMP_LT x10 x2 32               ; Проверка i < 32
    BR_COND x10 init_outer_body main_loop_setup

init_outer_body
    MOVi x3 0                      ; j = 0
    BRANCH init_inner_cond

init_inner_cond
    CMP_LT x10 x3 32               ; Проверка j < 32
    BR_COND x10 init_inner_body init_outer_inc

init_inner_body
    ; Заполнение grid[i][j] случайным значением 0 или 1
    SIM_RAND x4                    ; Генерация случайного числа
    ANDi x4 x4 1                   ; x4 = x4 % 2 (0 или 1)
    SET_CELL x0 x2 x3 x4           ; grid[i][j] = случайное значение
    ADDi x3 x3 1                   ; j++
    BRANCH init_inner_cond

init_outer_inc
    ADDi x2 x2 1                   ; i++
    BRANCH init_outer_cond

main_loop_setup
    ; Настройка основного цикла эволюции
    MOVi x9 0                      ; step = 0
    BRANCH main_loop_cond

main_loop_cond
    CMP_LT x10 x9 10000            ; Проверка step < 10000
    BR_COND x10 main_loop_body exit_program

main_loop_body
    ; Основной цикл вычисления следующего поколения
    MOVi x2 0                      ; i = 0
    BRANCH build_outer_cond

build_outer_cond
    CMP_LT x10 x2 32               ; Проверка i < 32
    BR_COND x10 build_outer_body copy_grid

build_outer_body
    MOVi x3 0                      ; j = 0
    BRANCH build_inner_cond

build_inner_cond
    CMP_LT x10 x3 32               ; Проверка j < 32
    BR_COND x10 build_inner_body build_outer_inc

build_inner_body
    ; Подсчет живых соседей для клетки [i][j]
    MOVi x5 0                      ; neighbors = 0
    MOVi x6 -1                     ; dx = -1
    BRANCH dx_loop_cond

dx_loop_cond
    CMP_LT x10 x6 2                ; Проверка dx <= 1
    BR_COND x10 dx_loop_body apply_rules

dx_loop_body
    MOVi x7 -1                     ; dy = -1
    BRANCH dy_loop_cond

dy_loop_cond
    CMP_LT x10 x7 2                ; Проверка dy <= 1
    BR_COND x10 dy_loop_body dx_loop_inc

dy_loop_body
    ; Пропуск центральной клетки (dx=0 && dy=0)
    CMP_EQ x10 x6 0
    CMP_EQ x11 x7 0
    AND x10 x10 x11
    BR_COND x10 dy_loop_inc calc_neighbor

calc_neighbor
    ; Вычисление координат соседа с учетом торичности
    ADD x8 x2 x7                   ; ny = i + dy
    ADDi x8 x8 32                  ; ny + 32 для положительности
    ANDi x8 x8 31                  ; ny = (ny + 32) % 32
    ADD x11 x3 x6                  ; nx = j + dx
    ADDi x11 x11 32                ; nx + 32 для положительности
    ANDi x11 x11 31                ; nx = (nx + 32) % 32
    GET_CELL x0 x8 x11 x12         ; Получение значения соседа
    ADD x5 x5 x12                  ; neighbors += grid[ny][nx]
    BRANCH dy_loop_inc

dy_loop_inc
    ADDi x7 x7 1                   ; dy++
    BRANCH dy_loop_cond

dx_loop_inc
    ADDi x6 x6 1                   ; dx++
    BRANCH dx_loop_cond

apply_rules
    ; Применение правил игры "Жизнь"
    GET_CELL x0 x2 x3 x6           ; cell = grid[i][j]
    CMP_EQ x10 x6 1                ; Проверка cell == 1
    BR_COND x10 live_cell dead_cell

live_cell
    ; Правило для живой клетки: выживает при 2 или 3 соседях
    CMP_EQ x10 x5 2                ; neighbors == 2
    CMP_EQ x11 x5 3                ; neighbors == 3
    OR x10 x10 x11                 ; neighbors == 2 || neighbors == 3
    BR_COND x10 set_alive set_dead

dead_cell
    ; Правило для мертвой клетки: оживает при 3 соседях
    CMP_EQ x10 x5 3                ; neighbors == 3
    BR_COND x10 set_alive set_dead

set_alive
    MOVi x12 1                     ; Новое состояние = 1 (живая)
    BRANCH store_cell

set_dead
    MOVi x12 0                     ; Новое состояние = 0 (мертвая)
    BRANCH store_cell

store_cell
    SET_CELL x1 x2 x3 x12          ; tmp_grid[i][j] = новое состояние
    ADDi x3 x3 1                   ; j++
    BRANCH build_inner_cond

build_outer_inc
    ADDi x2 x2 1                   ; i++
    BRANCH build_outer_cond

copy_grid
    ; Копирование tmp_grid в grid
    MEMCPY x0 x1
    
    ; Очистка экрана (заливка белым цветом 0xFFFFFFFF)
    MOVi x13 0                     ; y = 0
    BRANCH clear_outer_cond

clear_outer_cond
    CMP_LT x10 x13 512             ; Проверка y < 512
    BR_COND x10 clear_outer_body clear_outer_end

clear_outer_body
    MOVi x14 0                     ; x = 0
    BRANCH clear_inner_cond

clear_inner_cond
    CMP_LT x10 x14 512             ; Проверка x < 512
    BR_COND x10 clear_inner_body clear_inner_end

clear_inner_body
    MOVi x15 -1                    ; Белый цвет: 0xFFFFFFFF
    SCREEN_PUT_PIXEL x14 x13 x15   ; simPutPixel(x, y, WHITE)
    ADDi x14 x14 1                 ; x++
    BRANCH clear_inner_cond

clear_inner_end
    ADDi x13 x13 1                 ; y++
    BRANCH clear_outer_cond

clear_outer_end
    ; Отрисовка живых клеток (синие квадраты 16x16)
    MOVi x2 0                      ; i = 0
    BRANCH draw_outer_cond

draw_outer_cond
    CMP_LT x10 x2 32               ; Проверка i < 32
    BR_COND x10 draw_outer_body draw_outer_end

draw_outer_body
    MOVi x3 0                      ; j = 0
    BRANCH draw_inner_cond

draw_inner_cond
    CMP_LT x10 x3 32               ; Проверка j < 32
    BR_COND x10 draw_inner_body draw_inner_end

draw_inner_body
    GET_CELL x0 x2 x3 x4           ; Получение grid[i][j]
    CMP_EQ x10 x4 1                ; Проверка grid[i][j] == 1
    BR_COND x10 draw_cell draw_inner_inc

draw_cell
    ; Отрисовка квадрата 16x16 для живой клетки
    MOVi x13 0                     ; dy = 0
    BRANCH draw_y_cond

draw_y_cond
    CMP_LT x10 x13 16              ; Проверка dy < 16
    BR_COND x10 draw_y_body draw_y_end

draw_y_body
    MOVi x14 0                     ; dx = 0
    BRANCH draw_x_cond

draw_x_cond
    CMP_LT x10 x14 16              ; Проверка dx < 16
    BR_COND x10 draw_x_body draw_x_end

draw_x_body
    ; Вычисление координат пикселя
    SHL x5 x3 4                    ; x5 = j * 16
    ADD x5 x5 x14                  ; x5 = j*16 + dx (экранная координата X)
    SHL x6 x2 4                    ; x6 = i * 16
    ADD x6 x6 x13                  ; x6 = i*16 + dy (экранная координата Y)
    MOVi x15 6591981               ; Синий цвет: 0x808080FF
    SCREEN_PUT_PIXEL x5 x6 x15     ; Отрисовка пикселя
    ADDi x14 x14 1                 ; dx++
    BRANCH draw_x_cond

draw_x_end
    ADDi x13 x13 1                 ; dy++
    BRANCH draw_y_cond

draw_y_end
    BRANCH draw_inner_inc

draw_inner_inc
    ADDi x3 x3 1                   ; j++
    BRANCH draw_inner_cond

draw_inner_end
    ADDi x2 x2 1                   ; i++
    BRANCH draw_outer_cond

draw_outer_end
    ; Отрисовка вертикальных линий сетки
    MOVi x16 0                     ; x = 0
    BRANCH draw_vertical_cond

draw_vertical_cond
    CMP_LT x10 x16 32              ; Проверка x < 32
    BR_COND x10 draw_vertical_body draw_vertical_end

draw_vertical_body
    SHL x17 x16 4                  ; line_x = x * 16
    MOVi x18 0                     ; y = 0
    BRANCH draw_vertical_inner_cond

draw_vertical_inner_cond
    CMP_LT x10 x18 512             ; Проверка y < 512
    BR_COND x10 draw_vertical_inner_body draw_vertical_inner_end

draw_vertical_inner_body
    MOVi x19 6908265               ; Цвет сетки: 0x696969 (темно-серый)
    SCREEN_PUT_PIXEL x17 x18 x19   ; Отрисовка вертикальной линии
    ADDi x18 x18 1                 ; y++
    BRANCH draw_vertical_inner_cond

draw_vertical_inner_end
    ADDi x16 x16 1                 ; x++
    BRANCH draw_vertical_cond

draw_vertical_end
    ; Отрисовка горизонтальных линий сетки
    MOVi x16 0                     ; y = 0
    BRANCH draw_horizontal_cond

draw_horizontal_cond
    CMP_LT x10 x16 32              ; Проверка y < 32
    BR_COND x10 draw_horizontal_body draw_horizontal_end

draw_horizontal_body
    SHL x17 x16 4                  ; line_y = y * 16
    MOVi x18 0                     ; x = 0
    BRANCH draw_horizontal_inner_cond

draw_horizontal_inner_cond
    CMP_LT x10 x18 512             ; Проверка x < 512
    BR_COND x10 draw_horizontal_inner_body draw_horizontal_inner_end

draw_horizontal_inner_body
    MOVi x19 6908265               ; Цвет сетки: 0x696969 (темно-серый)
    SCREEN_PUT_PIXEL x18 x17 x19   ; Отрисовка горизонтальной линии
    ADDi x18 x18 1                 ; x++
    BRANCH draw_horizontal_inner_cond

draw_horizontal_inner_end
    ADDi x16 x16 1                 ; y++
    BRANCH draw_horizontal_cond

draw_horizontal_end
    ; Обновление экрана и переход к следующему поколению
    SCREEN_FLUSH                   ; simFlush()
    ADDi x9 x9 1                   ; step++
    BRANCH main_loop_cond

exit_program
    EXIT
