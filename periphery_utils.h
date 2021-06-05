#ifndef PERIPHERY_UTILS_H
#define PERIPHERY_UTILS_H

#include <stdlib.h>
#include <stdbool.h>

#include "params.h"
#include "mzapo_parlcd.h"

u_int16_t *fb;
u_int8_t *parlcd_mem_base;

volatile u_int32_t *led_line;
volatile u_int32_t *rgb_led1;
volatile u_int32_t *rgb_led2;
volatile u_int32_t *knobs;

u_int8_t knob_pressed;
u_int8_t red_knob;
u_int8_t green_knob;
u_int8_t blue_knob;

enum knobs_press_codes 
{
    RED_KNOB_PRESSED = 4,
    GREEN_KNOB_PRESSED = 2,
    BLUE_KNOB_PRESSED = 1,
    FORSE_QUIT = 7
};

/*
 *  Method for cleaning screen when quitting the game
 */
void clean_display();

/*
 *  Method for rendering data from the frame buffer
 */
void render_screen_data(u_int8_t *parlcd_mem_base);

/*
 *  Function for handling knobs input
 */
void handle_input();

/*
 *  Method for drawing a rectangle
 */
void fill_rect(int x, int y, int width, int height, u_int16_t color);

#endif