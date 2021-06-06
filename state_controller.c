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

#include "state_controller.h"

// Which player won the game
int winner = 0;

// Countains current countdown second for rendering
int countdown;

/*
 *  Main game's update method
 */
void update(int* state)
{
    switch (*state)
    {
        case MENU:
            update_menu();
            break;

        case READY:
            countdown = run_countdown();
            break;

        case GAME:
            update_gamefield();
            break;

        case END:
            update_end_screen();
            break;
    }
}

/*
 *  Main game's render method
 */
void render(int* state)
{
    // Clean display for rerendering
    clean_display();
    
    switch(*state)
    {
        case MENU:
            render_menu();
            break;

        case READY:
            render_gamefield();
            render_countdown(countdown);
            break;

        case GAME:
            render_gamefield();
            break;

        case END:
            render_end_screen(winner);
    }

    // Write new display data to the memory
    render_screen_data(parlcd_mem_base);
}

/*
 *  Method for quitting the game, turns off periphery
 */
void quit()
{
    // Clean the display
    clean_display();
    render_screen_data(parlcd_mem_base);

    // Turn off LED line and LED RGB
    *led_line = 0;
    *rgb_led1 = 0;
    *rgb_led2 = 0;

    // Free the frame buffer
    free(fb);

    exit(0);
}