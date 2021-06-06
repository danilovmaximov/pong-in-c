
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "game_states.h"
#include "menu.h"
#include "periphery_utils.h"
#include "countdown.h"
#include "game.h"
#include "game_end.h"

// Game's current state
int state;

int winner;

/*
 *  Main game's update method
 */
void update(int* state);

/*
 *  Main game's render method
 */
void render(int* state);

/*
 *  Method for quitting the game, turns off periphery
 */
void quit();