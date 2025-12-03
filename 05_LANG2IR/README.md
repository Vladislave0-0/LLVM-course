# Language to LLVM IR generator

## Описание
1) Придумать грамматику своего ЯП, ориентируясь на графическое приложение и полученные в предыдущем задании `ISA` и `ASM`. 
2) Написать небольшие тесты для подмножеств полученной грамматики.
3) Реализовать FrontEnd на `FlexBison`/`ANTLR` из ЯП в `LLVM IR`. Поддержать графическое приложение.
4) Подтянуть исполнение на `ExecutionEngine` полученного `LLVM IR` с графической библиотекой.

## Требования к зависимостям
Для корректной работы программы необходимо установить следующие библиотеки:
```bash
antlr4, libantlr4-runtime-dev
```

В Ubuntu может возникнуть проблема версий. По умолчанию установятся `antlr4 v4.10.1` и `antlr4-runtime v4.9.2`. Они не совместимы.

Поэтому в директории `./tools/` находятся две версии `antlr4`: `antlr-4.10.1` и `antlr-4.13.1`. Ориентироваться будем на последнюю версию `4.13.1`.

Установка `antlr4-runtime v4.13.1`:
```powershell
git clone https://github.com/antlr/antlr4.git
cd antlr4
git checkout 4.13.1
cd runtime/Cpp
mkdir build && cd build
cmake .. -DANTLR4_INSTALL=ON -DCMAKE_INSTALL_PREFIX=/usr/local
make -j$(nproc)
sudo make install
sudo ldconfig
cd ../../../../
```

## Генерация парсера и компиляция
В корне проекта есть скрипт `run.sh`, который опционально генерирует парсер и компилирует проект. Для начала выполним:
```powershell
cmake -S ./ -B build/ -DCMAKE_BUILD_TYPE=Release
```

```bash
chmod +x run.sh
```

```powershell
Usage: ./run.sh [MODE]

MODE options (optional):
  --parse    : Only generate parser
  --compile  : Only compile
  --all      : Generate parser and compile (default behavior)

Example:
  ./run.sh              # Generate parser for grammar/lang.g4 and compile
  ./run.sh --parse      # Only generate parser for grammar/lang.g4
  ./run.sh --compile    # Only compile (assume parser already generated)  
```

**Запуск проекта**:
```bash
./build/lang2ir ./test.txt
```


## Ход работы
1) **Language grammar with ANTLR**.

Грамматику для языка, поддерживающего графическое приложение, будем писать итеративно. Всю эволюцию написания грамматики можно проследить в директории `./grammar/`.