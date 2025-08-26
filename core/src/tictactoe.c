#include <tictactoe.h>
#include <stdlib.h>

tictactoe_t* tictactoe_new()
{
	return calloc(1, sizeof(tictactoe_t));
}

int tictactoe_ctor(tictactoe_t* this)
{
	this->last_player = PLAYER_NONE;
	for(int row = 0; row < NUM_ROWS; row++) {
		for(int col = 0; col < NUM_COLS; col++) {
			this->cells[row][col] = PLAYER_NONE;
		}
	}
	return 0;
}

int tictactoe_dtor(tictactoe_t* this)
{
	return tictactoe_ctor(this);
}

void tictactoe_del(tictactoe_t* this)
{
	free(this);
}
