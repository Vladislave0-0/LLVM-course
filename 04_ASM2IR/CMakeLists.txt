cmake_minimum_required(VERSION 3.14)
project(asm2ir)

# Поиск LLVM
find_package(LLVM REQUIRED CONFIG)
include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})

# Важно: явно указываем компоненты LLVM, которые нам нужны
set(LLVM_LINK_COMPONENTS
    core
    support
    irreader
    bitwriter
)

# Создаем исполняемый файл
add_executable(asm2ir
    src/main.cpp
    src/AsmParser.cpp
    src/IRGenerator.cpp
)

# Подключаем заголовочные файлы
target_include_directories(asm2ir PRIVATE include)

# Линкуем с LLVM
llvm_map_components_to_libnames(LLVM_LIBS ${LLVM_LINK_COMPONENTS})
target_link_libraries(asm2ir PRIVATE ${LLVM_LIBS})

# Устанавливаем стандарт C++17
set_target_properties(asm2ir PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)
