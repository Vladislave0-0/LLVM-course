#!/bin/bash

set -eo pipefail

show_help() {
    echo "Usage: $0 [MODE]"
    echo ""
    echo "MODE options (optional):"
    echo "  --parse    : Only generate parser"
    echo "  --compile  : Only compile"
    echo "  --all      : Generate parser and compile (default behavior)"
    echo "  --rus      : Enable Rus Target (defines __rus__)"
    echo "  --help, -h : Show this help"
    echo ""
    echo "Example:"
    echo "  $0              # Generate parser for grammar/lang.g4 and compile"
    echo "  $0 --parse      # Only generate parser for grammar/lang.g4"
    echo "  $0 --compile    # Only compile (assume parser already generated)"
    exit 0
}

# Определение режима
MODE="--all"
USE_RUS="OFF"
while [[ $# -gt 0 ]]; do
    case "$1" in
        --parse)   MODE="parse"; shift ;;
        --compile) MODE="compile"; shift ;;
        --all)     MODE="all"; shift ;;
        --rus)     USE_RUS="ON"; shift ;;
        --help|-h) show_help ;;
        *) echo "Unknown option: $1"; show_help ;;
    esac
done

# Проверка существования файла грамматики (всегда используем lang.g4)
GRAMMAR_PAHT="grammar/lang.g4"
GRAMMAR_NAME="lang"
if [ ! -f "${GRAMMAR_PAHT}" ]; then
    echo "Error: Grammar file '${GRAMMAR_PAHT}' not found"
    exit 1
fi

# Генерация парсера
if [[ "$MODE" == "parse" || "$MODE" == "all" ]]; then
    echo "Generating parser for grammar/${GRAMMAR_NAME}.g4..."
    rm -rf generated/*

    cd grammar/
    java -jar ../tools/antlr-4.13.1-complete.jar -Dlanguage=Cpp -visitor -no-listener -o ../generated "${GRAMMAR_NAME}.g4"
    cd ..
    
    echo "Parser generated successfully in './generated/'"
fi

# Компиляция
if [[ "$MODE" == "compile" || "$MODE" == "all" ]]; then
    echo "Compiling with ANTLR 4.13.1..."

    mkdir -p build
    cmake -S . -B build -DENABLE_RUS_TARGET=${USE_RUS}
    cmake --build ./build
    
    echo ""
    echo "Compilation successful. Executable: ./build/lang2ir"
fi
