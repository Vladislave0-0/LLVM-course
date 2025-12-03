cmake_minimum_required(VERSION 3.14)
project(lang2ir LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

find_program(LLVM_CONFIG llvm-config REQUIRED)

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
    COMMAND ${LLVM_CONFIG} --libs
    OUTPUT_VARIABLE LLVM_LIBS
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

separate_arguments(LLVM_CPPFLAGS_LIST NATIVE_COMMAND ${LLVM_CPPFLAGS})
add_compile_options(${LLVM_CPPFLAGS_LIST})

find_package(SDL2 QUIET)
if(NOT SDL2_FOUND)
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(SDL2 REQUIRED sdl2)
    add_compile_options(${SDL2_CFLAGS_OTHER})
endif()

# Исходники.
file(GLOB SOURCES
    src/*.cpp
    src/*.c
    generated/*.cpp
)

add_executable(lang2ir ${SOURCES})

target_include_directories(lang2ir PRIVATE
    /usr/local/include/antlr4-runtime
    generated
    ${SDL2_INCLUDE_DIRS}
)

# Библиотеки.
target_link_directories(lang2ir PRIVATE /usr/local/lib)

# ANTLR4.
target_link_libraries(lang2ir PRIVATE antlr4-runtime)

# SDL2.
if(SDL2_LIBRARIES)
    target_link_libraries(lang2ir PRIVATE ${SDL2_LIBRARIES})
else()
    target_link_libraries(lang2ir PRIVATE ${SDL2_LDFLAGS})
endif()

# LLVM.
target_link_options(lang2ir PRIVATE ${LLVM_LDFLAGS})
target_link_libraries(lang2ir PRIVATE ${LLVM_LIBS})
