#include "periphery_utils.h"

u_int16_t *fb;
u_int8_t *parlcd_mem_base;

volatile u_int32_t *led_line;
volatile u_int32_t *rgb_led1;
volatile u_int32_t *rgb_led2;
volatile u_int32_t *knobs;

u_int8_t red_knob;
u_int8_t green_knob;
u_int8_t blue_knob;
u_int8_t knob_pressed;
bool red_knob_released;
bool green_knob_released;
bool blue_knob_released;

/*
 *  Method for cleaning screen when quitting the game
 */
void clean_display()
{
    for (int i = 0; i < DISPLAY_WIDTH * DISPLAY_HEIGHT; i++)
        fb[i] = BLACK;
    render_screen_data(parlcd_mem_base);
}


/*
 *  Method for drawing a rectangle
 */
void fill_rect(int x, int y, int width, int height, u_int16_t color)
{
    for (int i = 0; i < width; i++)
        for (int j = 0; j < height; j++)
            draw_pixel(x + i, y + j, color);
}

/*
 *  Method for rendering data from the frame buffer
 */
void render_screen_data(u_int8_t *parlcd_mem_base)
{
    parlcd_write_cmd(parlcd_mem_base, 0x2c);

    for (int i = 0; i < DISPLAY_WIDTH * DISPLAY_HEIGHT; i++)
        parlcd_write_data(parlcd_mem_base, fb[i]);
}

/*
 *  Function for handling knobs input
 */
void handle_input()
{
    char red_knob_pressed = knob_pressed & 0xb100;
    char green_knob_pressed = knob_pressed & 0xb010;
    char blue_knob_pressed = knob_pressed & 0xb001;

    red_knob_released = false;
    green_knob_released = false;
    blue_knob_released = false;

    knob_pressed = *knobs >> 24;
    red_knob = (*knobs >> 16) & 0xFF;
    green_knob = (*knobs >> 8) & 0xFF;
    blue_knob = *knobs & 0xFF;

    if (red_knob_pressed - (knob_pressed & 0b100) == 0b100)
        red_knob_released = true;
    if (green_knob_pressed - (knob_pressed & 0b010) == 0b010)
        green_knob_released = true;
    if (blue_knob_pressed - (knob_pressed & 0b001) == 0b001)
        blue_knob_released = true;
}
