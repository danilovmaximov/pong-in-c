#ifndef PADS_H
#define PADS_H

#include "text_utils.h"
#include "params.h"
#include "periphery_utils.h"

#define PADS_X_OFFSET 10
#define PADS_HEIGHT 60
#define PADS_WIDTH 7
#define PADS_MOVE_SPEED 30

int pad1_pos, pad2_pos;

/*
 *  Method for rendering the pads
 */
void render_pads();

/*
 *  Method for initializing pads' variables
 */
void init_pads();

/*
 *  Methods contating pads logic (their movement, players' input)
 */
void update_pads();

#endif