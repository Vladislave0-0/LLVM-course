#!/bin/bash

set -eo pipefail

cd "$(dirname "$0")"

if [ $# -eq 0 ]; then
    echo "Error: Need arguments with source code" >&2
    exit 1
fi

# set -x

TIMEOUT=""
CLANG_ARGS=()
for arg in "$@"; do
    if [[ $arg == time=* ]]; then
        TIMEOUT="${arg#time=}"
        if ! [[ "$TIMEOUT" =~ ^[0-9]+$ ]] || [ "$TIMEOUT" -eq 0 ]; then
            echo "Error: time must be a positive integer (seconds)" >&2
            exit 1
        fi
    else
        CLANG_ARGS+=("$arg")
    fi
done

SRC_FILE="${CLANG_ARGS[0]}"

if [ -z "$SRC_FILE" ] || [ ! -f "$SRC_FILE" ]; then
    echo "Error: source file not found or not specified!" >&2
    exit 1
fi

NAME=$(basename -- "$SRC_FILE")
NAME="${NAME%.*}"

clang++ pass_trace.cpp -fPIC -shared -I$(llvm-config --includedir) -o libPass.so || exit 1
clang -O2 "$SRC_FILE" -emit-llvm -S -o "$NAME.ll" || exit 1
clang -O2 -fpass-plugin=./libPass.so "$SRC_FILE" -emit-llvm -S -o "$NAME.after_pass.ll" || exit 1
clang -O2 log.c "$NAME.after_pass.ll" "${CLANG_ARGS[@]:1}" -o get_log.out || exit 1

if [ -n "$TIMEOUT" ]; then
    timeout "$TIMEOUT"s ./get_log.out > trace.log
# else
    # ./get_log.out > trace.log
fi
