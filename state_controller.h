
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

int state, scale;
bool in_state_transition;

struct timespec delay;

void update(int* state);

void render(int* state);

void quit();