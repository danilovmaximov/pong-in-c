#ifndef BALL_H
#define BALL_H

#include "periphery_utils.h"
#include "text_utils.h"
#include "pads.h"
#include "game.h"

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

/*
 *  Method for updating the ball's state and position.
 */
void update_ball();

/*
 *  Method for rendering the ball in the game.
 */
void render_ball();

#endif