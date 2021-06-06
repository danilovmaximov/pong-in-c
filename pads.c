/*******************************************************************
  Game of pong in C for MZ_APO.

  start.c  - main script
  state_controller  - handling states' update and render, handling transitions between the states
  text_utils.c  - supporting methods for the work with text.
  periphery_utils.c  - supporting methods for the work with periphery.
  menu.c  - rendering and handling the menu.
  countdown.c  - countdown before the logic and render.
  game.c  - game proccess.
  pads.c  - the game's pads logic and render.
  ball.c  - the game's ball logic and render.
  game_end.c  - rendering game's end screen, it's logic.

  (C) Copyright 2021 by Danil Maksimov
  e-mail: maksidan@fel.cvut.cz
  license: any combination of GPL, LGPL, MPL or BSD licenses

 *******************************************************************/

#include "pads.h"

// Pads' positions
int pad1_pos = DISPLAY_HEIGHT / 2 - PADS_HEIGHT / 2;
int pad2_pos = DISPLAY_HEIGHT / 2 - PADS_HEIGHT / 2;

// Red and blue knobs states for checking if some of them were spinned
u_int8_t p1_old_knob;
u_int8_t p1_new_knob;
u_int8_t p2_old_knob;
u_int8_t p2_new_knob;

/*
 *  Method for rendering the pads
 */
void render_pads()
{
    fill_rect
    (
        PADS_X_OFFSET, pad1_pos, PADS_WIDTH, PADS_HEIGHT, RED
    );

    fill_rect
    (
        DISPLAY_WIDTH - PADS_X_OFFSET, pad2_pos, PADS_WIDTH, PADS_HEIGHT, BLUE
    );
}

/*
 *  Methods contating pads logic (their movement, players' input)
 */
void update_pads()
{
    // Get red knob's current state
    p1_new_knob = red_knob;

    // Check if the red pad is going out of borders
    if (pad1_pos < 4) pad1_pos += 10;
    else if (pad1_pos > DISPLAY_HEIGHT - PADS_HEIGHT - 4) pad1_pos -= 10;

    // If the red knob's state changed, update red pad's position
    else
    {
        int update = p1_old_knob - p1_new_knob;

        if (update < -1 && update > -50) pad1_pos += PADS_MOVE_SPEED;
        if (update > 1 && update < 50) pad1_pos -= PADS_MOVE_SPEED;
    }

    // Save red knob's state to check if it changes later
    p1_old_knob = p1_new_knob;

    // Get blue knob's current state
    p2_new_knob = blue_knob;

    // Check if the blue pad is going out of borders
    if (pad2_pos < 4) pad2_pos += 10;
    else if (pad2_pos > DISPLAY_HEIGHT - PADS_HEIGHT - 4) pad2_pos -= 10;

    // If the blue knob's state changed, update blue pad's position
    else
    {
        int update = p2_old_knob - p2_new_knob;

        if (update < -1 && update > -50) pad2_pos += PADS_MOVE_SPEED;
        if (update > 1 && update < 50) pad2_pos -= PADS_MOVE_SPEED;
    }

     // Save blue knob's state to check if it changes later
    p2_old_knob = p2_new_knob;
}

/*
 *  Method for initializing pads' variables
 */
void init_pads()
{
    p1_old_knob = red_knob;
    p1_new_knob = red_knob;
    p2_old_knob = blue_knob;
    p2_new_knob = blue_knob;
}