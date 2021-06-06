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

#include "game_end.h"

/*
 *  Method for rendering results of the game (and celebrate a bit)
 */
void render_end_screen(int winner)
{
    // Render the winner
    if (winner == PLAYER_1)
    {
        draw_string
        (
            DISPLAY_WIDTH / 2 - string_width("RED PLAYER WON!"), WINNER_Y_OFFSET, 
            "RED PLAYER WON!", WINNER_TEXT_SCALE, 0, RED
        );
    }
    else
    {
        draw_string
        (
            DISPLAY_WIDTH / 2 -  string_width("BLUE PLAYER WON!"), WINNER_Y_OFFSET, 
            "BLUE PLAYER WON!", WINNER_TEXT_SCALE, 0, BLUE
        );
    }

    draw_string
    (
        DISPLAY_WIDTH / 2 - string_width("press       to continue") / 2, CONTINUE_Y_OFFSET,
        "press    to continue", CONTINUE_TEXT_SCALE, 0, WHITE
    );

    fill_rect
    (
        GREEN_RECT_X, GREEN_RECT_Y, 
        GREEN_RECT_SIZE, GREEN_RECT_SIZE, GREEN
    );
}

/*
 *  Method containg game's end screen logic (input, LED handling)
 */
void update_end_screen()
{
    // Start game end led running
    end_led();

    if (knob_pressed == GREEN_KNOB_PRESSED) 
    {
        *led_line = 0;
        *rgb_led1 = 0;
        *rgb_led2 = 0;
        state = MENU;
    }
}