set(TEST_MAIN
		main_tests.cpp
		)

set(TEST
		model/scanner_test.cpp
		model/token_test.cpp
		model/automata_test.cpp
		model/state_test.cpp
		main_tests.cpp
		model/start_tests.cpp
		model/primitive_token_test.cpp
        )

set(COMPILER_FLAGS
        -g -std=c++23 -Wall -Wextra -Werror -Wcast-align -Wshadow -Wold-style-cast -Wpointer-arith -pedantic -Wconversion -O3 -pipe
        )

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR} ${gmock_SOURCE_DIR}/include ${gmock_SOURCE_DIR})


add_executable(Google_Tests_run ${TEST_MAIN} ${TEST})
target_link_libraries(Google_Tests_run gtest gtest_main gmock ${PROJECT_NAME}-lib)
target_compile_options(Google_Tests_run PRIVATE ${COMPILER_FLAGS})