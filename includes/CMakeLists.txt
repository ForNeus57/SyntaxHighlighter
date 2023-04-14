set(LIB_DIRECTORY
		${PROJECT_SOURCE_DIR}/includes/syntax_colorizer_lib
		)

# comented method are no tested / implemented in moder way
set(SRC
		#${LIB_DIRECTORY}/sources/common/run.cpp
		${LIB_DIRECTORY}/sources/common/file_wrapper.cpp
		${LIB_DIRECTORY}/sources/common/statistics.cpp
		#${LIB_DIRECTORY}/sources/model/scanner.cpp
		#${LIB_DIRECTORY}/sources/model/automata/automata.cpp
		${LIB_DIRECTORY}/sources/model/automata/state.cpp
		${LIB_DIRECTORY}/sources/model/token/base_token.cpp
		#${LIB_DIRECTORY}/sources/model/token/token.cpp
		)

set(COMPILER_FLAGS
		-g -std=c++23 -Wall -Wextra -Werror -Wcast-align -Wshadow -Wold-style-cast -Wpointer-arith -pedantic -Wconversion -O3 -pipe
		)

add_subdirectory(googletest)

add_library(${PROJECT_NAME}-lib STATIC ${SRC})

target_include_directories(${PROJECT_NAME}-lib PUBLIC ${PROJECT_SOURCE_DIR}/config)

target_compile_options(${PROJECT_NAME}-lib PRIVATE ${COMPILER_FLAGS})