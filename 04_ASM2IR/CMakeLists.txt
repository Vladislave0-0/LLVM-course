cmake_minimum_required(VERSION 3.14)
project(asm2ir)

find_program(LLVM_CONFIG NAMES "llvm-config-18" "llvm-config")

if(NOT LLVM_CONFIG)
    message(FATAL_ERROR "LLVM config not found")
endif()

execute_process(
    COMMAND ${LLVM_CONFIG} --cppflags
    OUTPUT_VARIABLE LLVM_CPPFLAGS
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

execute_process(
    COMMAND ${LLVM_CONFIG} --ldflags
    OUTPUT_VARIABLE LLVM_LDFLAGS
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

execute_process(
    COMMAND ${LLVM_CONFIG} --libs core support executionengine interpreter native
    OUTPUT_VARIABLE LLVM_LIBS
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

execute_process(
    COMMAND ${LLVM_CONFIG} --includedir
    OUTPUT_VARIABLE LLVM_INCLUDE_DIR
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

# Поиск SDL2
find_package(PkgConfig REQUIRED)
pkg_check_modules(SDL2 REQUIRED sdl2)

# Создаем исполняемый файл
add_executable(asm2ir
    src/AsmParser.cpp
    src/CPU.cpp
    src/EmulateIR.cpp
    src/FullIR.cpp
    src/IRGenerator.cpp
    src/main.cpp
    src/sim.c
)

target_include_directories(asm2ir PRIVATE 
    include
    ${LLVM_INCLUDE_DIR}
    ${SDL2_INCLUDE_DIRS}
)

# Флаги компиляции для LLVM и SDL.
target_compile_options(asm2ir PRIVATE 
    ${LLVM_CPPFLAGS}
    ${SDL2_CFLAGS_OTHER}
)

target_link_libraries(asm2ir PRIVATE 
    ${LLVM_LIBS}
    ${LLVM_LDFLAGS}
    ${SDL2_LIBRARIES}
)

set_target_properties(asm2ir PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)
