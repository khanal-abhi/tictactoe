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
	ttt.last_player = TTT_PLAYER_X;
	ttt.cells[1][2] = TTT_PLAYER_X;
	tictactoe_ctor(&ttt);
	assert_true(ttt.last_player == TTT_PLAYER_NONE);
	for (int r = 0; r < NUM_ROWS; r++)
	{
		for (int c = 0; c < NUM_COLS; c++)
		{
			assert_true(ttt.cells[r][c] == TTT_PLAYER_NONE);
		}
	}
}

static void test_tictactoe_dtor_valid(void **state)
{
	tictactoe_t ttt;
	ttt.last_player = TTT_PLAYER_X;
	ttt.cells[1][2] = TTT_PLAYER_X;
	tictactoe_dtor(&ttt);
	assert_true(ttt.last_player == TTT_PLAYER_NONE);
	for (int r = 0; r < NUM_ROWS; r++)
	{
		for (int c = 0; c < NUM_COLS; c++)
		{
			assert_true(ttt.cells[r][c] == TTT_PLAYER_NONE);
		}
	}
}

static void test_tictactoe_play_move_invalid_cell(void **state)
{
	tictactoe_t* ttt = (tictactoe_t*)*state;
	int res = tictactoe_play_move(ttt, TTT_PLAYER_O, 0, NUM_COLS);
	assert_true(res == -ETTT_INVALIDCELL);
	res = tictactoe_play_move(ttt, TTT_PLAYER_O, NUM_ROWS, 0);
	assert_true(res == -ETTT_INVALIDCELL);
	res = tictactoe_play_move(ttt, TTT_PLAYER_O, NUM_ROWS, NUM_COLS);
	assert_true(res == -ETTT_INVALIDCELL);
	ttt->cells[0][0] = TTT_PLAYER_O;
	res = tictactoe_play_move(ttt, TTT_PLAYER_O, 0, 0);
	assert_true(res == -ETTT_INVALIDCELL);
	ttt->cells[0][0] = TTT_PLAYER_X;
	res = tictactoe_play_move(ttt, TTT_PLAYER_O, 0, 0);
	assert_true(res == -ETTT_INVALIDCELL);
}

static void test_tictactoe_play_move_gameover(void **state)
{
	tictactoe_t* ttt = (tictactoe_t*)*state;
	ttt->game_state = TTT_ENDED_WINO;
	int res = tictactoe_play_move(ttt, TTT_PLAYER_O, 0, 0);
	assert_true(res == -ETTT_GAMEOVER);
}

static void test_tictactoe_play_move_invalid_player(void **state)
{
	tictactoe_t* ttt = (tictactoe_t*)*state;
	tictactoe_ctor(ttt);
	int res = tictactoe_play_move(ttt, TTT_PLAYER_NONE, 0, 0);
	assert_true(res == -ETTT_INVALIDPLAYER);
	tictactoe_ctor(ttt);
	ttt->last_player = TTT_PLAYER_O;
	res = tictactoe_play_move(ttt, TTT_PLAYER_O, 0, 0);
	assert_true(res == -ETTT_INVALIDPLAYER);
	ttt->last_player = TTT_PLAYER_X;
	res = tictactoe_play_move(ttt, TTT_PLAYER_X, 0, 0);
	assert_true(res == -ETTT_INVALIDPLAYER);
	ttt->last_player = TTT_PLAYER_NONE;
	res = tictactoe_play_move(ttt, 77, 0, 0);
	assert_true(res == -ETTT_INVALIDPLAYER);
	res = tictactoe_play_move(ttt, -27, 0, 0);
	assert_true(res == -ETTT_INVALIDPLAYER);
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_tictactoe_new),
    	cmocka_unit_test(test_tictactoe_del),
    	cmocka_unit_test(test_tictactoe_ctor_null),
    	cmocka_unit_test(test_tictactoe_dtor_null),
    	cmocka_unit_test(test_tictactoe_ctor_valid),
    	cmocka_unit_test(test_tictactoe_dtor_valid),
    	cmocka_unit_test(test_tictactoe_play_move_invalid_cell),
    	cmocka_unit_test(test_tictactoe_play_move_gameover),
    	cmocka_unit_test(test_tictactoe_play_move_invalid_player),
    };
 
    return cmocka_run_group_tests(tests, setup, teardown);
}

