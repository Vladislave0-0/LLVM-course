# Assembler to LLVM IR generator

## Описание
1) Написать свой набор инструкций из статистики для ASM и LLVM IR вашего графического приложения. 
2) Переписать приложение на ASM. 
3) Написать `ASM2IR` генератор:
    - С вызовами эмулирующих функций (кроме инструкций потока управления).
    - С генерацией IR-эквивалентов для всех инструкций.



Набор ассемблерных команд на основе LLVM IR и второго задания `02_LLVM_PASS`, в котором была собрана статистика часто повторяющихся паттернов инструкций:

| **№** |   **Инструкция**  |             **Формат ASM**            |                           **Назначение**                          |                                     **LLVM IR-эквивалент**                                    |
|:-----:|:-----------------:|:-------------------------------------:|:-----------------------------------------------------------------:|:---------------------------------------------------------------------------------------------:|
|   1   |        ADD        |          ADD dst, src1, src2          |                        Сложение целых чисел                       |                                  %dst = add i32 %src1, %src2                                  |
|   2   |        ADDI       |           ADDi dst, src, imm          |                       Сложение с константой                       |                                    %dst = add i32 %src, imm                                   |
|   3   |        SUB        |          SUB dst, src1, src2          |                       Вычитание целых чисел                       |                                  %dst = sub i32 %src1, %src2                                  |
|   4   |        ANDi       |           ANDi dst, src, imm          |                     Побитовое "И" с константой                    |                                    %dst = and i32 %src, imm                                   |
|   5   |       SREMi       |          SREMi dst, src, imm          |                  Остаток от деления на константу                  |                                   %dst = srem i32 %src, imm                                   |
|   6   |        SHL        |           SHL dst, src, imm           |                            Сдвиг влево                            |                                    %dst = shl i32 %src, imm                                   |
|   7   |       TRUNC       |             TRUNC dst, src            |      Усечение значения из более  широкого типа в более узкий      |                                  %dst = trunc i64 %src to i32                                 |
|   8   |        ZEXT       |             ZEXT dst, src             | Нулевое расширение значения из  более узкого типа в более широкий |                                  %dst = zext i32 %src to i64                                  |
|   9   |       CMP_EQ      |          CMP_EQ dst, src, imm         |                       Сравнение на равенство                      |                                  %dst = icmp eq i32 %src, imm                                 |
|   10  |       CMP_NE      |          CMP_NE dst, src, imm         |                      Сравнение на неравенство                     |                                  %dst = icmp ne i32 %src, imm                                 |
|   11  |       CMP_LT      |          CMP_LT dst, src, imm         |                         Сравнение "меньше"                        |                                 %dst = icmp slt i32 %src, imm                                 |
|   12  |       CMP_GT      |          CMP_GT dst, src, imm         |                         Сравнение "больше"                        |                                 %dst = icmp sgt i32 %src, imm                                 |
|   13  |       INC_EQ      |          INC_EQ dst, src, imm         |                 Инкремент + сравнение на равенство                |                     %temp = add i32 %src, 1 %dst = icmp eq i32 %temp, imm                     |
|   14  |  COUNT_NEIGHBOURS |    COUNT_NEIGHBOURS grid, x, y, dst   |                    Подсчет живых соседей клетки                   |                                          Многа букав                                          |
|   15  |       BRANCH      |              BRANCH label             |                        Безусловный переход                        |                                        br label %label                                        |
|   16  |      BR_COND      | BR_COND cond, label_true, label_false |                          Условный переход                         |                             br i1 %cond, label %true, label %false                            |
|   17  |        MOVi       |             MOVi dst, imm             |                         Загрузка константы                        |                                         %dst = i32 imm                                        |
|   18  |        MOV        |              MOV dst, src             |                        Копирование регистра                       |                                          %dst = %src                                          |
|   19  |    ALLOCA_GRID    |            ALLOCA_GRID dst            |                  Выделение памяти под сетку 32x32                 |                                %dst = alloca [32 x [32 x i32]]                                |
|   20  | ALLOCA_NEIGHBOURS |         ALLOCA_NEIGHBOURS dst         |                    Выделение памяти под соседей                   |                                 %dst = alloca [8 x [2 x i32]]                                 |
|   21  |       MEMSET      |               MEMSET ptr              |                          Обнуление памяти                         |                    call void @llvm.memset.p0.i64(ptr %ptr, i8 0, i64 size)                    |
|   22  |       MEMCPY      |            MEMCPY dst, src            |                         Копирование памяти                        |                 call void @llvm.memcpy.p0.p0.i64(ptr %dst, ptr %src, i64 size)                |
|   23  |      GET_CELL     |        GET_CELL grid, x, y, dst       |                     Получение значения клетки                     | %idx = getelementptr inbounds [32 x i32], ptr %grid, i64 %x, i64 %y %dst = load i32, ptr %idx |
|   24  |      SET_CELL     |        SET_CELL grid, x, y, src       |                     Установка значения клетки                     |  %idx = getelementptr inbounds [32 x i32], ptr %grid, i64 %x, i64 %y store i32 %src, ptr %idx |
|   25  |  SCREEN_PUT_PIXEL |      SCREEN_PUT_PIXEL x, y, color     |                         Нарисовать пиксель                        |                       call void @simPutPixel(i32 %x, i32 %y, i32 %color)                      |
|   26  |    SCREEN_FLUSH   |              SCREEN_FLUSH             |                           Обновить экран                          |                                     call void @simFlush()                                     |
|   27  |     DRAW_GRID     |             DRAW_GRID grid            |                        Отрисовка всей сетки                       |                                          Многа букав                                          |
|   28  |      SIM_RAND     |              SIM_RAND dst             |                     Генерация случайного числа                    |                                   %dst = call i32 @simRand()                                  |
|   29  |   LIFETIME_START  |           LIFETIME_START ptr          |                      Начало жизненного цикла                      |                     call void @llvm.lifetime.start.p0(i64 size, ptr %ptr)                     |
|   30  |    LIFETIME_END   |            LIFETIME_END ptr           |                       Конец жизненного цикла                      |                      call void @llvm.lifetime.end.p0(i64 size, ptr %ptr)                      |
|   31  |        EXIT       |                  EXIT                 |                        Завершение программы                       |                                            ret void                                           |
