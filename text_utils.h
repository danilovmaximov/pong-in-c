/*******************************************************************
  text_utils.h  - upporting methods for work with text.

  (C) Copyright 2021 by Danil Maksimov
  e-mail: maksidan@fel.cvut.cz
  license: any combination of GPL, LGPL, MPL or BSD licenses

 *******************************************************************/

#include <stdlib.h>

int char_width(int ch);

int string_width(char *str);

void draw_pixel(int x, int y, unsigned short color);

void draw_pixel_big(int x, int y, unsigned short color);

void draw_char(int x, int y, char ch, unsigned short color);

void draw_string(int x, int y, 
                 char *str, 
                 int scale, int kerning,
                 uint16_t color);
