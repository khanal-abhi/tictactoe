#include <tictactoe.h>
#include <stdlib.h>

tictactoe_t* tictactoe_new()
{
	return calloc(1, sizeof(tictactoe_t));
}

int tictactoe_ctor(tictactoe_t* this)
{
	if (this == NULL) {
		return -ETTT_NULLCTOR;
	}
	this->last_player = TTT_PLAYER_NONE;
	this->game_state = TTT_RUNNING;
	for(int row = 0; row < NUM_ROWS; row++) {
		for(int col = 0; col < NUM_COLS; col++) {
			this->cells[row][col] = TTT_PLAYER_NONE;
		}
	}
	return 0;
}

int tictactoe_dtor(tictactoe_t* this)
{
	if (this == NULL)
	{
		return -ETTT_NULLDTOR;
	}
	return tictactoe_ctor(this);
}

void tictactoe_del(tictactoe_t* this)
{
	free(this);
}

int tictactoe_play_move(tictactoe_t* this, tictactoe_player_t player, uint8_t row, uint8_t col)
{
	tictactoe_game_state_t game_state;
	if (!tictactoe_running(this, &game_state)) {
		return -ETTT_GAMEOVER;
	}
	if (0 > row || row >= NUM_ROWS || 0 > col || col >= NUM_COLS) {
		return -ETTT_INVALIDCELL;
	}
	if (this->cells[row][col] != TTT_PLAYER_NONE)
	{
		return -ETTT_INVALIDCELL;
	}
	if (player == TTT_PLAYER_NONE || player > TTT_PLAYER_X) {
		return -ETTT_INVALIDPLAYER;
	}
	switch (this->last_player) {
		case TTT_PLAYER_NONE:
		case TTT_PLAYER_X:
			if (player != TTT_PLAYER_O) {
				return -ETTT_INVALIDPLAYER;
			}
			break;
		case TTT_PLAYER_O:
			if (player != TTT_PLAYER_X) {
				return -ETTT_INVALIDPLAYER;
			}
			break;
		default:
			return -ETTT_INVALIDPLAYER;
			break;
	}
	
	return TTT_OKAY;
}

bool tictactoe_running(tictactoe_t* this, tictactoe_game_state_t* game_state)
{
	*game_state = this->game_state;
	return this->game_state == TTT_RUNNING;
}
