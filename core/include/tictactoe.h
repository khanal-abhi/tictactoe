#ifndef __H_TICTACTOE__
#define __H_TICTACTOE__

#include <stdint.h>
#include <stdbool.h>

#define NUM_ROWS 3
#define NUM_COLS 3

typedef enum {
	TTT_OKAY,
	ETTT_MALLOC,
	ETTT_FREE,
	ETTT_NULLCTOR,
	ETTT_NULLDTOR,
	ETTT_INVALIDCELL,
	ETTT_INVALIDPLAYER,
	ETTT_GAMEOVER,
} tictactoe_error_t;

typedef enum {
	TTT_PLAYER_NONE = 0,
	TTT_PLAYER_O = 1,
	TTT_PLAYER_X = 2,
} tictactoe_player_t;

typedef enum {
	TTT_RUNNING,
	TTT_ENDED_WINO,
	TTT_ENDED_WINX,
	TTT_ENDED_DRAW,
} tictactoe_game_state_t;

typedef struct {
	tictactoe_player_t last_player;
	tictactoe_player_t cells[NUM_ROWS][NUM_COLS];
	tictactoe_game_state_t game_state;
} tictactoe_t;

/* tictactoe ownership functions */
tictactoe_t* tictactoe_new(void);
int tictactoe_ctor(tictactoe_t*);
int tictactoe_dtor(tictactoe_t*);
void tictactoe_del(tictactoe_t*);

/* tictactoe game logic */
int tictactoe_play_move(tictactoe_t*, tictactoe_player_t, uint8_t, uint8_t);
bool tictactoe_running(tictactoe_t*, tictactoe_game_state_t*);

#endif
