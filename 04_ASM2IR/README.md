# Assembler to LLVM IR generator

## Описание
1) Написать свой набор инструкций из статистики для ASM и LLVM IR вашего графического приложения. 
2) Переписать приложение на ASM. 
3) Написать `ASM2IR` генератор:
    - С вызовами эмулирующих функций (кроме инструкций потока управления).
    - С генерацией IR-эквивалентов для всех инструкций.

## Ход работы:

1) Для начала составим примерный набор ассемблерных команд на основе LLVM IR и второго задания `02_LLVM_PASS`, в котором была собрана статистика часто повторяющихся паттернов инструкций:

|  № | Инструкция |             Формат ASM            |              Назначение              |                LLVM IR-эквивалент               |
|:--:|:----------:|:---------------------------------:|:------------------------------------:|:-----------------------------------------------:|
|  1 |     ADD    |        ADD dst, src1, src2        |         Сложение целых чисел         |           %dst = add i32 %src1, %src2           |
|  2 |     SUB    |        SUB dst, src1, src2        |         Вычитание целых чисел        |           %dst = sub i32 %src1, %src2           |
|  3 |     SHL    |         SHL dst, src, imm         |              Сдвиг влево             |             %dst = shl i32 %src, imm            |
|  4 |     AND    |        AND dst, src1, src2        |             Побитовое "И"            |           %dst = and i32 %src1, %src2           |
|  5 |     OR     |         OR dst, src1, src2        |            Побитовое "ИЛИ"           |            %dst = or i32 %src1, %src2           |
|  6 |     CMP    |      CMP dst, src1, src2, op      |  Сравнение (eq, ne, lt, gt, le, ge)  |         %dst = icmp op i32 %src1, %src2         |
|  7 |     BR     |              BR label             |          Безусловный переход         |                   br label %L                   |
|  8 |     BRZ    | BRZ cond, label_true, label_false |           Условный переход           |      br i1 %cond, label %then, label %else      |
|  9 |     MOV    |            MOV dst, imm           |          Загрузка константы          |                  %dst = i32 imm                 |
| 10 |    ALLOC   |          ALLOC dst, size          |        Выделение блока памяти        |            %dst = alloca [size x i32]           |
| 11 |     LEA    |       LEA dst, base, offset       |           Вычисление адреса          | %dst = getelementptr inbounds %base, i64 offset |
| 12 |     LD     |           LD dst, [addr]          |          Загрузка из памяти          |            %dst = load i32, ptr %addr           |
| 13 |     ST     |           ST [addr], src          |          Сохранение в память         |            store i32 %src, ptr %addr            |
| 14 |    CALL    |           CALL fn, args…          |             Вызов функции            |                call void @fn(...)               |
| 15 |     RET    |                RET                |          Завершение функции          |                     ret void                    |
| 16 |   PUTPIX   |         PUTPIX x, y, color        |          Нарисовать пиксель          | call void @simPutPixel(i32 x, i32 y, i32 color) |
| 17 |    FLUSH   |               FLUSH               |            Обновить экран            |              call void @simFlush()              |
| 18 |    RAND    |              RAND dst             |       Получить случайное число       |            %dst = call i32 @simRand()           |
| 19 |     PHI    |    PHI dst, srcA, srcB, labels    | Объединение значений из разных веток |     %dst = phi i32 [ %a, %L1 ], [ %b, %L2 ]     |



<!-- 2) На данном этапе постараюсь написать парсер ассемблера для команд из пункта 1. 

3) Перепишу LLVM IR в ASM файл, параллельно дописывая набор команд и сам ассемблер. 

4) 

5)  -->