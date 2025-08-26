add_library(
	tictactoe
	STATIC
	src/tictactoe.c
)

target_include_directories(
	tictactoe
	PUBLIC
	include
)

add_executable(
	libtictactoe_test
	test/libtictactoe_test.c
)

target_link_libraries(
	libtictactoe_test
	tictactoe
	cmocka
)

target_include_directories(
	libtictactoe_test
	PUBLIC
	include
)
