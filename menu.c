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

#include "menu.h"

// Menu's button choice
int choice = 1;

// Variables contain knobs' states before and after spinning
u_int8_t old_knob;
u_int8_t new_knob; 

/*
 *  Method for rendering game's title
 */
void render_title()
{
    const char letters[4] = {'P', 'O', 'N', 'G'};

    // Render a rectangle around the title
    fill_rect
    (
        0, 10, DISPLAY_WIDTH, 130, WHITE
    );

    // Render the letters
    for (int i = 0; i < 4; i++)
    {
        draw_char
        (
            i * TITLE_LETTERS_X_OFFSET,
            TITLE_Y_OFFSET,
            letters[i],
            BLACK,
            TITLE_LETTERS_SCALE
        );
    }
}

/*
 *  Method for rendering menu's buttons
 */
void render_buttons()
{
    // Render PLAY button
    draw_string
    (
        DISPLAY_WIDTH / 2 - string_width("PLAY"),
        MENU_Y_OFFSET,
        "PLAY",
        MENU_TEXT_SCALE,
        0,
        WHITE
    );

    // Render EXIT button
    draw_string
    (
        DISPLAY_WIDTH / 2 - string_width("EXIT"),
        MENU_Y_OFFSET * 1.33,
        "EXIT",
        MENU_TEXT_SCALE,
        0,
        WHITE
    );
}

/*
 *  Method for rendering game's credits
 */
void render_credits()
{
    char CREDIT[] = "made by Danil Maksimov";

    draw_string
    (
        DISPLAY_WIDTH / 2 - string_width(CREDIT) / 2,
        MENU_Y_OFFSET * 1.66,
        CREDIT,
        MENU_TEXT_SCALE / 2,
        0,
        WHITE
    );
}

/*
 *  Method for rendering the line which underlines player's button choice in the menu
 */
void render_choice()
{
    switch (choice)
    {
        case -1:
            fill_rect(DISPLAY_WIDTH / 2 - string_width("PLAY"), MENU_Y_OFFSET + 30, string_width("PLAY") * 2, 4, GREEN);
            break;
        case 1:
            fill_rect(DISPLAY_WIDTH / 2 - string_width("EXIT"), MENU_Y_OFFSET * 1.33 + 30, string_width("EXIT") * 2, 4, GREEN);
            break;
    }
}

/*
 *  Method for rendering all the menu's elements
 */
void render_menu()
{
    render_title();
    render_buttons();
    render_choice();
    render_credits();
}

/*
 *  Method contating main menu's logic
 */
void update_menu()
{
    // Run the LED snake
    led_run_light();

    // Green knob's new state
    new_knob = green_knob;
    
    // Check if the green knob's state is different than a cycle before
    int update = old_knob - green_knob;
    if (update != 0) 
    {
        choice *= -1;
        old_knob = new_knob;
    }

    // If player pressed the green knob, check which button was it and proceed
    if (knob_pressed == GREEN_KNOB_PRESSED)
    {
        switch (choice)
        {
        case -1:  // if the player pressed "PLAY"
            *led_line = 0;
            state = READY;
            break;
        case 1:  // if the player pressed "EXIT"
            quit();
            break;
        }
    }
}

/*
 *  Method for initializing menu's variables
 */
void init_menu()
{
    old_knob = green_knob;
    new_knob = green_knob;
}
