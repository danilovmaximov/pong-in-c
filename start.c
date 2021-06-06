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

#define _POSIX_C_SOURCE 200112L

#include "start.h"

/*
 *  Display initialization method
 */
void display_init()
{
    // Set game state to MENU
    state = MENU;

    // Init font descriptor
    fdes = &font_winFreeSystem14x16;

    // Init display data
    fb = malloc(DISPLAY_WIDTH * DISPLAY_HEIGHT * 16);
    if (fb == NULL) 
    {
        fprintf(stderr, "Failed to initialize display!\n");
        exit(-1);
    }

    parlcd_mem_base = map_phys_address(PARLCD_REG_BASE_PHYS, PARLCD_REG_SIZE, 0);
    if (parlcd_mem_base == NULL) 
    {
        fprintf(stderr, "Failed to initialize display!\n");
        exit(-1);
    }

    parlcd_write_cmd(parlcd_mem_base, 0x2c);
    
    int ind = 0;
    u_int32_t temp;

    for (int i = 0; i < DISPLAY_HEIGHT; i++) 
    {
        for (int j = 0; j < DISPLAY_WIDTH; j++) 
        {
            temp = 0;
            fb[ind] = temp;
            parlcd_write_data(parlcd_mem_base, fb[ind++]);
        }
    }
}

void delay_init() 
{
    delay.tv_sec = 0;
    delay.tv_nsec = 17 * 1000 * 1000;
}

/*
 *  Method for initializing knobs, LED line and LED RGB
 */
void periphery_init() 
{
    u_int8_t *spiled_mem_base = map_phys_address(SPILED_REG_BASE_PHYS, SPILED_REG_SIZE, 0);
    if (spiled_mem_base == NULL)
    {
        fprintf(stderr, "Failed to initialize periphery!\n");
        exit(-1);
    }

    led_line = (volatile u_int32_t *) (spiled_mem_base + SPILED_REG_LED_LINE_o);
    rgb_led1 = (volatile u_int32_t *) (spiled_mem_base + SPILED_REG_LED_RGB1_o);
    rgb_led2 = (volatile u_int32_t *) (spiled_mem_base + SPILED_REG_LED_RGB2_o);
    knobs = (volatile u_int32_t *) (spiled_mem_base + SPILED_REG_KNOBS_8BIT_o);
}

/*
 *  Method for initializing all game components
 */
void init()
{
    delay_init();
    display_init();
    periphery_init();
    init_led_run_light();
    init_menu();
}

/*
 *  Game's main cycle
 */
int main(int argc, char *argv[])
{
    init();

    while (true)
    {
        get_input();
        update(&state);
        render(&state);

        if (knob_pressed == FORSE_QUIT) quit();
        clock_nanosleep(CLOCK_MONOTONIC, 0, &delay, NULL);
    }    
}