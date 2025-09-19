## Описание
Это пример реализации игры "Жизнь" Джона Конвея как простого графического приложения, основанного на `SDL 2.0`.

С правилами игры "Жизнь" можно ознакомиться [тут](https://ru.wikipedia.org/wiki/%D0%98%D0%B3%D1%80%D0%B0_%C2%AB%D0%96%D0%B8%D0%B7%D0%BD%D1%8C%C2%BB).
<br><br>

## Требования к зависимостям
Для корректной работы программы необходимо установить следующую библиотеку:
```bash
sudo apt install libsdl2-dev
```

## Компиляция и запуск
```bash
clang start.c sim.c app.c -lSDL2
./a.out
```

## Генерация LLVM IR
Для модуля `app.c` (в котором производится расчёт фрейма) был сгенерирован  `LLVM IR` в директории `./IR/` с разными уровнями оптимизации (`-O1/-Os`).

Файл `./IR/combined.bc` — это связанный модуль, содержащий весь код программы, готовый к интерпретации через `lli`. Вот как его можно получить и запустить:

```bash
# Генерация .ll файлов
clang start.c sim.c app.c -emit-llvm -S -O1
```
```bash
# Связка модулей в один
llvm-link start.ll sim.ll app.ll -o combined.bc
```
```bash
# Интерпретация с загрузкой SDL2
lli --load=$(find /usr -name "libSDL2.so" 2>/dev/null | head -n1) combined.bc
```

## Пример запуска
<video controls src="gif/Example.mp4" title="Title"></video>
