cmake_minimum_required(VERSION 3.14)
project(lang2ir LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(LLVM REQUIRED CONFIG)

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

# Необходимые флаги LLVM
include_directories(${LLVM_INCLUDE_DIRS})
separate_arguments(LLVM_DEFINITIONS_LIST NATIVE_COMMAND ${LLVM_DEFINITIONS})
add_definitions(${LLVM_DEFINITIONS_LIST})

file(GLOB_RECURSE SOURCES
    src/*.cpp
    src/*.c
    generated/*.cpp
)

add_executable(lang2ir ${SOURCES})

target_include_directories(lang2ir PRIVATE
    /usr/local/include/antlr4-runtime
    generated
)

# Линкуем с ANTLR4 runtime
target_link_directories(lang2ir PRIVATE /usr/local/lib)
target_link_libraries(lang2ir PRIVATE antlr4-runtime)

# Линкуем с LLVM
target_link_libraries(lang2ir PRIVATE ${LLVM_LIBRARIES})
