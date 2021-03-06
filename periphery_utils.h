#ifndef PERIPHERY_UTILS_H
#define PERIPHERY_UTILS_H

#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <stdbool.h>

#include "params.h"
#include "text_utils.h"
#include "mzapo_parlcd.h"

// Frame buffer
uint16_t *fb;
// Variable for accessing the memory
uint8_t *parlcd_mem_base;

volatile uint32_t *led_line;
volatile uint32_t *rgb_led1;
volatile uint32_t *rgb_led2;

volatile uint32_t *knobs;
uint8_t red_knob;
uint8_t green_knob;
uint8_t blue_knob;
uint8_t knob_pressed;

/*
 *  Enum containing codes for pressing knobs
 */
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
void render_screen_data(uint8_t *parlcd_mem_base);

/*
 *  Function for handling knobs input
 */
void get_input();

/*
 *  Method for drawing a rectangle
 */
void fill_rect(int x, int y, int width, int height, uint16_t color);

/*
 *  Method for pulsing RGB LEDs (when a player scores)
 */
void pulse_led(uint8_t color, uint8_t led);

/*
 *  Method for updating RGB LEDs states
 */
void update_led();

/*
 *  Method for running one light across the LED line
 */
void led_run_light();

/*
 *  Method for initializing necessary variables before running one light across the LED line
 */
void init_led_run_light();

/*
 *  Method for running two lines (to left and right) on the LED line at the end of the game
 */
void end_led();

/*
 *  Method for initializing necessary variables before running two lines on the LED line
 */
void init_end_led();


#endif