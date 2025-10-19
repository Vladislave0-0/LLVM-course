# LLVM IR Generator

## Описание

Это пример реализации LLVM пасса, который в runtime'е собирает трассу исполненных IR инструкций (`User <- Operand`) графического приложения (только для логического модуля `../01_SDL/src/app.c`) на `-O2`.

Если `User` это `phi`, то `User` не логируется. Если же `phi` является операндом в какой либо инструкции, то логируются интрукции, используемые в операндах этого `phi`.

**Пример**: запись `shl <- phi` заменяется на две записи `shl <- add` и `shl <- sub`, если этот `phi` использует в качестве операндов `add` и `sub`.

## Компиляция и запуск
1. Компиляция пасса:
```powershell
clang++ pass_trace.cpp -fPIC -shared -I$(llvm-config --includedir) -o libPass.so
```

2. Генерация LLVM IR из исходного C-кода:
```powershell
clang -O2 ../01_SDL/src/app.c -emit-llvm -S -o app.ll
```

3. Применение пасса к полученному IR:
```powershell
clang -O2 -fpass-plugin=./libPass.so app.ll -emit-llvm -S -o app.after_pass.ll
```

4. Компиляция и линковка финальной программы
```powershell
clang -O2 log.c app.after_pass.ll ../01_SDL/src/start.c ../01_SDL/src/sim.c -lSDL2 -o get_log.out
```
<br> 

Можно запустить скрипт `run.sh` для выполнения всех этих команд вместе:
```powershell
bash ./run.sh ../01_SDL/src/app.c ../01_SDL/src/start.c ../01_SDL/src/sim.c -lSDL2
```

На выходе получим файл `get_log.out`.
