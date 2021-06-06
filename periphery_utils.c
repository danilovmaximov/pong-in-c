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

#include "periphery_utils.h"

// Variables for working with LEDs
uint32_t led_count;
uint8_t right;
uint8_t led_color;
uint8_t current_led;
uint8_t led_counter;

/*
 *  Method for cleaning screen when quitting the game and for rerendering
 */
void clean_display()
{
    for (int i = 0; i < DISPLAY_WIDTH * DISPLAY_HEIGHT; i++)
        fb[i] = BLACK;
}

/*
 *  Method for drawing a rectangle
 */
void fill_rect(int x, int y, int width, int height, uint16_t color)
{
    for (int i = 0; i < width; i++)
        for (int j = 0; j < height; j++)
            draw_pixel(x + i, y + j, color);
}

/*
 *  Method for rendering data from the frame buffer
 */
void render_screen_data(uint8_t *parlcd_mem_base)
{
    parlcd_write_cmd(parlcd_mem_base, 0x2c);

    for (int i = 0; i < DISPLAY_WIDTH * DISPLAY_HEIGHT; i++)
        parlcd_write_data(parlcd_mem_base, fb[i]);
}

/*
 *  Function for handling knobs input
 */
void get_input()
{
    knob_pressed = *knobs >> 24;
    red_knob = (*knobs >> 16) & 0xFF;
    green_knob = (*knobs >> 8) & 0xFF;
    blue_knob = *knobs & 0xFF;
}

/*
 *  Method for pulsing RGB LEDs (when a player scores)
 */
void pulse_led(uint8_t color, uint8_t led)
{
    current_led = led;
    led_counter = 255;
    led_color = color;
}

/*
 *  Method for updating RGB LEDs states
 */
void update_led() 
{
    uint8_t R = ((led_color >> 2) * led_counter);
    uint8_t G = ((led_color >> 1) % 2) * led_counter;
    uint8_t B = (led_color % 2) * led_counter;

    if (led_counter != 0) led_counter -= 15;

    if (current_led == 1) *rgb_led1 = ((uint32_t)R << 16) + ((uint32_t)G << 8) + (uint32_t)B;
    if (current_led == 2) *rgb_led2 = ((uint32_t)R << 16) + ((uint32_t)G << 8) + (uint32_t)B;
}

/*
 *  Method for running one light across the LED line
 */
void led_run_light() 
{
    if (led_count % 10000)
    {
        if (right) 
        {
            if (*led_line == 1) right = 0;
            else *led_line >>= 1;
        } 
        else
        {
            if (*led_line == 0x80000000) right = 1;
            else *led_line <<= 1;
        }
    }
    
    led_count++;
}

/*
 *  Method for initializing necessary variables before running one light across the LED line
 */
void init_led_run_light()
{
    *led_line = 0x80000000;
    right = 1;
    led_count = 0;
}

/*
 *  Method for running two lines (to left and right) on the LED line at the end of the game
 */
void end_led()
{
    if (led_count % 1000)
    {
        uint32_t temp_l;
        uint32_t temp_r;

        if (*led_line == 0xFFFFFFFF) *led_line = 0x00018000;
        else 
        {
            temp_l = *led_line;
            temp_r = *led_line;
            temp_l <<= 1;
            temp_r >>= 1;
            *led_line = *led_line | temp_l | temp_r;
        }
    }

    led_count++;
}

/*
 *  Method for initializing necessary variables before running two lines on the LED line
 */
void init_end_led()
{
    *led_line = 0x00018000;
    led_count = 0;
}