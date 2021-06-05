#include "game.h"
#include "params.h"
#include "text_utils.h"

#define WINNER_Y_OFFSET 100
#define WINNER_TEXT_SCALE 2

#define CONTINUE_Y_OFFSET 270
#define CONTINUE_TEXT_SCALE 1

#define GREEN_RECT_X 211
#define GREEN_RECT_Y 273
#define GREEN_RECT_SIZE 10


void render_end_screen(int winner);

void update_end_screen();