#include <tictactoe.h>
#include <stdlib.h>

#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <setjmp.h>
#include <cmocka.h>
 
int setup(void **state)
{
	*state = tictactoe_new();
	if (*state == NULL)
	{
		return -ETTT_MALLOC;
	}
	return tictactoe_ctor((tictactoe_t*) *state);
}

int teardown(void **state)
{
	int res = tictactoe_dtor(*state);
	if (res != TTT_OKAY) {
		return res;
	}
	tictactoe_del((tictactoe_t*) *state);
	return TTT_OKAY;
}

static void test_tictactoe_new(void **state)
{
	tictactoe_t* ttt = tictactoe_new();
	assert_non_null(ttt);
	free(ttt);
}
 
static void test_tictactoe_del(void **state)
{
	tictactoe_t* ttt = tictactoe_new();
	assert_non_null(ttt);
	tictactoe_del(ttt);
}

static void test_tictactoe_ctor_null(void **state)
{
	int res = tictactoe_ctor(NULL);
	assert_true(res == -ETTT_NULLCTOR);
}

static void test_tictactoe_dtor_null(void **state)
{
	int res = tictactoe_dtor(NULL);
	assert_true(res == -ETTT_NULLDTOR);
}

static void test_tictactoe_ctor_valid(void **state)
{
	tictactoe_t ttt;
	ttt.last_player = PLAYER_X;
	ttt.cells[1][2] = PLAYER_X;
	tictactoe_ctor(&ttt);
	assert_true(ttt.last_player == PLAYER_NONE);
	for (int r = 0; r < NUM_ROWS; r++)
	{
		for (int c = 0; c < NUM_COLS; c++)
		{
			assert_true(ttt.cells[r][c] == PLAYER_NONE);
		}
	}
}

static void test_tictactoe_dtor_valid(void **state)
{
	tictactoe_t ttt;
	ttt.last_player = PLAYER_X;
	ttt.cells[1][2] = PLAYER_X;
	tictactoe_dtor(&ttt);
	assert_true(ttt.last_player == PLAYER_NONE);
	for (int r = 0; r < NUM_ROWS; r++)
	{
		for (int c = 0; c < NUM_COLS; c++)
		{
			assert_true(ttt.cells[r][c] == PLAYER_NONE);
		}
	}
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_tictactoe_new),
    	cmocka_unit_test(test_tictactoe_del),
    	cmocka_unit_test(test_tictactoe_ctor_null),
    	cmocka_unit_test(test_tictactoe_dtor_null),
    	cmocka_unit_test(test_tictactoe_ctor_valid),
    	cmocka_unit_test(test_tictactoe_dtor_valid),
    };
 
    return cmocka_run_group_tests(tests, setup, teardown);
}

