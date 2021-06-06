#ifndef GAME_H
#define GAME_H

#include <stdbool.h>

#include "mzapo_parlcd.h"
#include "mzapo_phys.h"
#include "mzapo_regs.h"
#include "text_utils.h"
#include "params.h"
#include "periphery_utils.h"
#include "game_states.h"
#include "state_controller.h"
#include "pads.h"
#include "ball.h"

#define SEPARATION_LINE_OFFSET 10
#define SEPARATION_LINE_WIDTH 2
#define SEPARATION_LINE_HEIGHT 5

#define SCORE_X_OFFSET 50
#define SCORE_Y_OFFSET 20
#define SCORE_SCALE 5
#define SCORE_WIDTH 18

#define SCORE_AIM 5
#define PLAYER_1 1
#define PLAYER_2 2
#define INIT_SCORE 0

int p1_score, p2_score;

void update_gamefield();

void render_gamefield();

void render_score();

void update_score(int side);

#endif