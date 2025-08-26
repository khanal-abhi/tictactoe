#ifndef __H_TICTACTOE__
#define __H_TICTACTOE__

#include <stdint.h>

#define NUM_ROWS 3
#define NUM_COLS 3

typedef enum {
	PLAYER_NONE = 0,
	PLAYER_O = 1,
	PLAYER_X = 2,
} player_t;

typedef struct {
	player_t last_player;
	player_t cells[NUM_ROWS][NUM_COLS];
} tictactoe_t;

tictactoe_t* tictactoe_new(void);
int tictactoe_ctor(tictactoe_t*);
int tictactoe_dtor(tictactoe_t*);
void tictactoe_del(tictactoe_t*);

#endif
