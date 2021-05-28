/*******************************************************************
  text_utils.c  - upporting methods for work with text.

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
int scale=4;

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
 *  Calculate string's width
 *  
 *  char *str  -  string, it's width is being calculated
 */
int string_width(char *str) 
{
    int i = 0;
    int result = 0;

    while (str[i] != '\0') 
    {
        result += charWidth(str[i]);
        i++;
    }
    return result;
}


void draw_pixel(int x, int y, unsigned short color) 
{
    if (x >= 0 && x < 480 && y >= 0 && y < 320) 
    {
        fb[x + 480 * y] = color;
    }
}

/*
 *  Regulate character's scale
 */
void draw_pixel_big(int x, int y, unsigned short color) 
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
 *  Draw a character on the display
 *
 *  int x, y  -  coordinates fo the upper left corner of the character
 *  char ch  -  the character or it's code from the font table
 */
void draw_char(int x, int y, char ch, unsigned short color) 
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
                    draw_pixel_big(x + scale * j, y + scale * i, color);
                }
                val <<= 1;
            }
            ptr++;
        }
    }
}

/*
 *  Draw a string on the display
 *
 *  int x, y  -  coordinates of the upper left corner of the string
 *  char *str  -  the string to draw
 */
void draw_string(int x, int y, 
                 char *str, 
                 int scale, int kerning,
                 uint16_t color) 
{
    int concatinated = 0;

    while (*str != '\0') 
    {
        draw_сhar(x + (concatinated), y, *(str), color, scale);
        concatinated += (char_width(*(str)) + kerning) * scale;
        str++;
    }
}
