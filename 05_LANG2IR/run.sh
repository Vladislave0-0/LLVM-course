#!/bin/bash

set -eo pipefail

show_help() {
    echo "Usage: $0 [MODE]"
    echo ""
    echo "MODE options (optional):"
    echo "  --parse    : Only generate parser"
    echo "  --compile  : Only compile"
    echo "  --all      : Generate parser and compile (default behavior)"
    echo ""
    echo "Example:"
    echo "  $0              # Generate parser for grammar/lang.g4 and compile"
    echo "  $0 --parse      # Only generate parser for grammar/lang.g4"
    echo "  $0 --compile    # Only compile (assume parser already generated)"
    exit 0
}

# Проверка аргументов
if [ $# -gt 1 ] || [ "$1" == "--help" ] || [ "$1" == "-h" ]; then
    show_help
fi

# Определение режима
MODE="--all"
if [ $# -eq 1 ]; then
    MODE="$1"
    # Проверка валидности режима
    if [[ "$MODE" != "--parse" && "$MODE" != "--compile" && "$MODE" != "--all" ]]; then
        echo "Error: Invalid mode '$MODE'"
        show_help
    fi
fi

# Проверка существования файла грамматики (всегда используем lang.g4)
GRAMMAR_PAHT="grammar/lang.g4"
GRAMMAR_NAME="lang"
if [ ! -f "${GRAMMAR_PAHT}" ]; then
    echo "Error: Grammar file '${GRAMMAR_PAHT}' not found"
    exit 1
fi

# Генерация парсера
if [[ "$MODE" == "--parse" || "$MODE" == "--all" ]]; then
    echo "Generating parser for grammar/${GRAMMAR_NAME}.g4..."
    rm -rf generated/*

    cd grammar/
    java -jar ../tools/antlr-4.13.1-complete.jar -Dlanguage=Cpp -visitor -no-listener -o ../generated "${GRAMMAR_NAME}.g4"
    cd ..
    
    echo "Parser generated successfully in './generated/'"
fi

# Компиляция
if [[ "$MODE" == "--compile" || "$MODE" == "--all" ]]; then
    echo "Compiling with ANTLR 4.13.1..."

    cmake --build ./build
    
    # clang++                                         \
    #   src/*.cpp src/*.c generated/*.cpp             \
    #   -I /usr/local/include/antlr4-runtime          \
    #   -I generated                                  \
    #   -L /usr/local/lib                             \
    #   -lantlr4-runtime                              \
    #   $(llvm-config --cppflags --ldflags --libs)    \
    #   -std=c++17                                    \
    #   -o lang2ir
    
    echo ""
    echo "Compilation successful. Executable: ./lang2ir"
fi
