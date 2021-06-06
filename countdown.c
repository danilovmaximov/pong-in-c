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

#include "countdown.h"

int countdown_len = REAL_COUNTDOWN_LENGTH;
int countdown_base = COUNTDOWN_BASE;
int current_countdown = USER_COUNTDOWN_LENGTH;

/*
 *  Method for counting down from 3 before game starts.
 */
int run_countdown()
{
    // Run the countdown, rerender if a second passed
    if (countdown_len % 20 == 0 && countdown_len != REAL_COUNTDOWN_LENGTH) 
    {
        countdown_len = REAL_COUNTDOWN_LENGTH;
        current_countdown -= 1;
        countdown_len -= 1;
    } 
    else 
    {
        countdown_len -= 1;
    }

    // If countdown finished, reinitialize variables and start the game
    if (current_countdown == 0) 
    {
        countdown_len = REAL_COUNTDOWN_LENGTH;
        countdown_base = COUNTDOWN_BASE;
        current_countdown = 3;
        state = GAME;
        init_pads();
    }

    return current_countdown;
}

/*
 *  Method for rendering the countdown before the game starts.
 */
void render_countdown(int cur_countdown)
{
    draw_char
    (
        DISPLAY_WIDTH / 2 - char_width((char) cur_countdown + '0'),
        DISPLAY_HEIGHT / 2 - 2 * CHAR_HEIGHT,
        (char) cur_countdown + '0', WHITE, 5
    );
}