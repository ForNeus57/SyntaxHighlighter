project(Includes)

add_subdirectory(googletest)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

set(TEST
        ../tests/scanner/scanner_test.cpp
        ../tests/scanner/token_test.cpp
        ../tests/scanner/automata_test.cpp
        ../tests/scanner/state_test.cpp
        ../tests/scanner/run_tests.cpp
        )

add_executable(Google_Tests_run ${TEST})
target_link_libraries(Google_Tests_run gtest gtest_main)