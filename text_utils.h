#ifndef TEXT_UTILS_H
#define TEXT_UTILS_H

#include <stdlib.h>
#include "font_types.h"

font_descriptor_t *fdes;

int char_width(int ch);

int string_width(char *str);

void draw_pixel(int x, int y, unsigned short color);

void draw_pixel_big(int x, int y, uint16_t color, int scale);

void draw_char(int x, int y, char ch, uint16_t color, int scale);

void draw_string(int x, int y, 
                 char *str, 
                 int scale, int kerning,
                 uint16_t color);

#endif