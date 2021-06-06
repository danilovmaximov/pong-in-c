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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mzapo_parlcd.h"
#include "mzapo_phys.h"
#include "mzapo_regs.h"
#include "font_types.h"

/*********************************************/
/* This part of code is taken from lecture 8 */
/*********************************************/

unsigned short *fb;
font_descriptor_t *fdes;
int scale = 4;

/*
 *  Method for calculating char's width
 */
int char_width(int ch) 
{
    int width;
    if (!fdes -> width) 
    {
        width = fdes -> maxwidth;
    } 
    else 
    {
        width = fdes -> width[ch - fdes -> firstchar];
    }
    return width;
}

/*
 *  Method for calculating string's width
 */
int string_width(char *str) 
{
    int i = 0;
    int result = 0;

    while (str[i] != '\0') 
    {
        result += char_width(str[i]);
        i++;
    }
    return result;
}

/*
 *  Method for drawing a pixel on the display
 */
void draw_pixel(int x, int y, unsigned short color) 
{
    if (x >= 0 && x < 480 && y >= 0 && y < 320) 
    {
        fb[x + 480 * y] = color;
    }
}

/*
 *  Method for regulating character's scale
 */
void draw_pixel_big(int x, int y, u_int16_t color, int scale) 
{
    int i, j;
    for (i = 0; i < scale; i++) 
    {
        for (j = 0; j < scale; j++) 
        {
            draw_pixel(x + i, y + j, color);
        }
    }
}

/*
 *  Method for drawing a character on the display
 *
 *  int x, y  -  coordinates fo the upper left corner of the character
 *  char ch  -  the character or it's code from the font table
 */
void draw_char(int x, int y, char ch, u_int16_t color, int scale) 
{
    int w = char_width(ch);
    const font_bits_t *ptr;
    if ((ch >= fdes -> firstchar) && (ch - fdes -> firstchar < fdes -> size)) 
    {
        if (fdes -> offset) 
        {
            ptr = &fdes -> bits[fdes -> offset[ch - fdes -> firstchar]];
        } 
        else 
        {
            int bw = (fdes -> maxwidth + 15) / 16;
            ptr = &fdes -> bits[(ch - fdes -> firstchar) * bw * fdes -> height];
        }
        int i, j;
        for (i = 0; i < fdes -> height; i++) 
        {
            font_bits_t val = *ptr;
            for (j = 0; j < w; j++) 
            {
                if ((val &0x8000) != 0) 
                {
                    draw_pixel_big(x + scale * j, y + scale * i, color, scale);
                }
                val <<= 1;
            }
            ptr++;
        }
    }
}

/*
 *  Method for drawing a string on the display
 *
 *  int x, y  -  coordinates of the upper left corner of the string
 *  char *str  -  the string to draw
 */
void draw_string(int x, int y, 
                 char *str, 
                 int scale, int kerning,
                 u_int16_t color) 
{
    int concatinated = 0;

    while (*str != '\0') 
    {
        draw_char(x + concatinated, y, *str, color, scale);
        concatinated += (char_width(*str) + kerning) * scale;
        str++;
    }
}
