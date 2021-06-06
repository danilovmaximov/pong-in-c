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

#include "game.h"

// Players scores
int p1_score = INIT_SCORE;
int p2_score = INIT_SCORE;

// Game field separation line's X coordinate
int separation_line_x = DISPLAY_WIDTH / 2 + 2 * SEPARATION_LINE_WIDTH;

/*
 *  Method for checking if any of the players scored enough to end the game
 */
void check_score()
{   
    // Check if Player 1 scored enough
    if (p1_score == SCORE_AIM)
    {
        winner = PLAYER_1;
        p1_score = INIT_SCORE;
        state = END;
        init_end_led();
    }

    // Check if Player 2 scored enough
    else if (p2_score == SCORE_AIM)
    {
        winner = PLAYER_2;
        p2_score = INIT_SCORE;
        state = END;
        init_end_led();
    }
}

/*
 *  Method for rendering players' scores
 */
void render_score()
{
    // Player 1 score
    draw_char
    (
        separation_line_x - SCORE_X_OFFSET - SCORE_WIDTH, SCORE_Y_OFFSET, 
        (char) p1_score + '0', RED, SCORE_SCALE
    );

    // Player 2 score
    draw_char
    (
        separation_line_x + SCORE_X_OFFSET - SCORE_WIDTH, SCORE_Y_OFFSET,
        (char) p2_score + '0', BLUE, SCORE_SCALE
    );
}

/*
 *  Method for pausing the game (all the progress is saved)
 */
void pause_game()
{
    state = MENU;
}

/*
 *  Method for running game's logic.
 */
void update_gamefield()
{
    check_score();
    update_led();
    update_pads();
    update_ball();

    if (knob_pressed == GREEN_KNOB_PRESSED) 
    {
        *rgb_led1 = 0;
        *rgb_led2 = 0;
        pause_game();
    }
}

/*
 *  Method for rendering game field's separation line
 */
void render_separation_line()
{
    for (int i = 0; i < 32; i += 1)
    {
        fill_rect
        (
            DISPLAY_WIDTH / 2 + 2 * SEPARATION_LINE_WIDTH,
            SEPARATION_LINE_OFFSET * i,
            SEPARATION_LINE_WIDTH,
            SEPARATION_LINE_HEIGHT,
            WHITE
        );
    }
}

/*
 *  Method for rendering all game fields's elements
 */
void render_gamefield()
{
    render_separation_line();
    render_pads();
    render_score();
    render_ball();
}

/*
 *  Method for incrementing player's score  
 */
void update_score(int side)
{
    if (side == PLAYER_1) p1_score++;
    else if (side == PLAYER_2) p2_score++;
    else printf("Something's really wrong here!\n");
}