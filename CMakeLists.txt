cmake_minimum_required(VERSION 3.24 FATAL_ERROR)
project(Syntax_Highlighter VERSION 0.3.2.1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(MAIN
        main.cpp
        )

set(COMPILER_FLAGS
        -g -std=c++23 -Wall -Wextra -Werror -Wcast-align -Wshadow -Wold-style-cast -Wpointer-arith -pedantic -Wconversion -O3 -pipe
        )

configure_file(${PROJECT_SOURCE_DIR}/config/config.h.in ${PROJECT_SOURCE_DIR}/config/config.h)

add_subdirectory(includes)
add_subdirectory(tests)

add_executable(${PROJECT_NAME} ${MAIN})

target_link_libraries(${PROJECT_NAME} PUBLIC ${PROJECT_NAME}-lib)

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/includes/syntax_colorizer_lib)

target_compile_options(${PROJECT_NAME} PRIVATE ${COMPILER_FLAGS})