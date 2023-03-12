cmake_minimum_required(VERSION 3.24)
project(Compilation_theory_and_compilers)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(MAIN
        main.cpp
        )

set(SRC
        sources/scanner/token/Token.cpp
        sources/scanner/automata/Automata.cpp
        sources/scanner/Scanner.cpp
        sources/scanner/exceptions/WrongInputAlphabet.cpp
        sources/scanner/automata/State.cpp sources/scanner/automata/State.h)

set(COMPILER_FLAGS
        -Wall -Wextra -Werror -Wcast-align -Wshadow -Wold-style-cast -Wpointer-arith -pedantic -Wconversion -O3 -std=c++20
        )

include_directories(sources/scanner)
include_directories(sources/scanner/token)
include_directories(sources/scanner/exceptions)
include_directories(sources/scanner/automata)

add_library(${PROJECT_NAME}-lib ${SRC})

add_executable(${PROJECT_NAME} ${MAIN})

target_link_libraries(${PROJECT_NAME} PRIVATE ${PROJECT_NAME}-lib)

target_compile_options(${PROJECT_NAME} PRIVATE ${COMPILER_FLAGS})
target_compile_options(${PROJECT_NAME}-lib PRIVATE ${COMPILER_FLAGS})
