cmake_minimum_required(VERSION 3.11)
project("LLVM_IRGen")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Найти LLVM
find_package(LLVM REQUIRED CONFIG)
find_package(SDL2 REQUIRED)

# Вывести версию (опционально)
message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

# Добавить пути к заголовкам LLVM
include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})

# Источники
set(GENERATOR_SOURCES
    src/main.cpp
    src/generator.cpp
    src/sim.c
)

# Исполняемый файл
add_executable(gen ${GENERATOR_SOURCES})

# Подключить библиотеки LLVM
target_link_libraries(gen PRIVATE LLVM)
target_link_libraries(gen PRIVATE SDL2::SDL2)

