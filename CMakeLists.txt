cmake_minimum_required(VERSION 3.24)
project(BasicCompiler)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(MAIN
        main.cpp
        )

set(SRC
        sources/scanner/token/token.cpp
        sources/scanner/automata/automata.cpp
        sources/scanner/scanner.cpp
        sources/scanner/automata/state.cpp
        sources/scanner/exceptions/error_state_reached.h
        sources/scanner/exceptions/cannot_create_token_not_from_finishing_state.h
        )

set(COMPILER_FLAGS
        -Wall -Wextra -Werror -Wcast-align -Wshadow -Wold-style-cast -Wpointer-arith -pedantic -Wconversion -O3 -std=c++20
        )

add_subdirectory(includes)

include_directories(includes/)
include_directories(sources/scanner)
include_directories(sources/scanner/token)
include_directories(sources/scanner/exceptions)
include_directories(sources/scanner/automata)
include_directories(sources/)

add_library(${PROJECT_NAME}-lib ${SRC})

add_executable(${PROJECT_NAME} ${MAIN})

target_link_libraries(${PROJECT_NAME} PRIVATE ${PROJECT_NAME}-lib)

target_compile_options(${PROJECT_NAME} PRIVATE ${COMPILER_FLAGS})
target_compile_options(${PROJECT_NAME}-lib PRIVATE ${COMPILER_FLAGS})
