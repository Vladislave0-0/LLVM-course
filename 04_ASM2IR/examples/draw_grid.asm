draw_vertical_lines
    MOVi x0 0          ; x0 = счетчик внешнего цикла (номер вертикальной линии)
    MOVi x1 32         ; x1 = общее количество вертикальных линий
    MOVi x2 4          ; x2 = сдвиг на 4 бита = умножение на 16
    MOVi x7 6908265    ; x7 = цвет линии (темно-серый, 0x696969)

outer_vert_loop
    SHL x3 x0 x2      ; x3 = x0 * 16 (координата X вертикальной линии)
    MOVi x4 0          ; x4 = счетчик внутреннего цикла (координата Y)
    MOVi x5 512        ; x5 = высота экрана в пикселях

inner_vert_loop
    SCREEN_PUT_PIXEL x3 x4 x7  ; Рисуем точку вертикальной линии
    
    ADDi x4 x4 1      ; y = y + 1
    CMP_EQ x6 x4 x5   ; Сравниваем y с высотой экрана
    BR_COND x6 check_next_vert_line, inner_vert_loop

check_next_vert_line:
    ADDi x0 x0 1      ; i = i + 1 (переходим к следующей вертикальной линии)
    CMP_EQ x6 x0 x1   ; Сравниваем i с количеством линий
    BR_COND x6 draw_horizontal_lines outer_vert_loop

draw_horizontal_lines
    MOVi x0 0          ; x0 = счетчик внешнего цикла (номер горизонтальной линии)

outer_horiz_loop
    SHL x3 x0 x2      ; x3 = x0 * 16 (координата Y горизонтальной линии)
    MOVi x4 0          ; x4 = счетчик внутреннего цикла (координата X)

inner_horiz_loop
    SCREEN_PUT_PIXEL x4 x3 x7  ; Рисуем точку горизонтальной линии
    
    ADDi x4 x4 1      ; x = x + 1
    CMP_EQ x6 x4 x5   ; Сравниваем x с шириной экрана
    BR_COND x6 check_next_horiz_line inner_horiz_loop

check_next_horiz_line
    ADDi x0 x0 1      ; i = i + 1 (переходим к следующей горизонтальной линии)
    CMP_EQ x6 x0 x1   ; Сравниваем i с количеством линий
    BR_COND x6 finish_drawing_grid outer_horiz_loop

finish_drawing_grid
