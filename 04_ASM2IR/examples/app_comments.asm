app:
    MOVi x1, 0          ; Инициализация x
    BRANCH label_1

label_1:
    MOVi x2, 0          ; Инициализация y
    BRANCH label_9

label_9:
    SIM_RAND x3         ; Генерируем случайное число
    ANDi x3, x3, 1      ; Берем остаток от деления на 2
    CMP_EQ x0, x3, 0    ; Сравниваем с нулем
    BR_COND x0, set_black, set_color  ; Если равно 0 - черный, иначе цветной

set_color:
    MOV x4, x2          ; Копируем y в x4
    SHL x4, x4, 9       ; x4 = y * 512
    ADD x4, x4, x1      ; x4 = y * 512 + x
    SHL x4, x4, 7       ; x4 = (y * 512 + x) * 128
    ADDi x4, x4, 16711680  ; Добавляем красный цвет (0xFF0000)
    BRANCH put_pixel

set_black:
    MOVi x4, -16777216  ; Черный цвет (0xFF000000)
    BRANCH put_pixel

put_pixel:
    SCREEN_PUT_PIXEL x1, x2, x4  ; Рисуем пиксель

    ADDi x2, x2, 1      ; y = y + 1
    CMP_EQ x0, x2, 512  ; Проверяем, достигли ли конца по y
    BR_COND x0, label_9, label_4  ; Если не достигли - следующий пиксель, иначе новая строка

label_4:
    ADDi x1, x1, 1      ; x = x + 1
    CMP_EQ x0, x1, 512  ; Проверяем, достигли ли конца по x
    BR_COND x0, label_7, flush  ; Если не достигли - следующая строка, иначе обновляем экран

flush:
    SCREEN_FLUSH        ; Обновляем экран
    MOVi x1, 0          ; Сбрасываем x в 0
    BRANCH label_7

label_7:
    BRANCH label_1      ; Бесконечный цикл
    