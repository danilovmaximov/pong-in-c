#ifndef BALL_H
#define BALL_H

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

#define BALL_SIZE 15

#define BALL_INIT_X 240
#define BALL_INIT_Y 50

#define BALL_MOVE_SPEED 8

#define NO_COLLISTION 0
#define VERTICAL_COLLISION 1
#define HORIZONTAL_COLLISION 2
#define CORNER_COLLISION 3
#define LEFT_OUT_OF_BOUNDS 4
#define RIGHT_OUT_OF_BOUNDS 5

void update_ball();

void render_ball();

void reset_ball();

#endif