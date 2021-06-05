#include "game.h"

int p1_score = 0;
int p2_score = 0;

int separation_line_x = DISPLAY_WIDTH / 2 + 2 * SEPARATION_LINE_WIDTH;

void update_gamefield()
{
    update_pads();
}

void render_separation_line()
{
    for (int i = 0; i < 32; i += 1)
    {
        fill_rect
        (
            DISPLAY_WIDTH / 2 + 2 * SEPARATION_LINE_WIDTH,
            SEPARATION_LINE_OFFSET * i,
            SEPARATION_LINE_WIDTH,
            SEPARATION_LINE_HEIGHT,
            WHITE
        );
    }
}

void render_gamefield()
{
    render_separation_line();
    render_pads();
    render_score();
}

void render_score()
{
    draw_char
    (
        separation_line_x - SCORE_X_OFFSET - SCORE_WIDTH, SCORE_Y_OFFSET, 
        (char) p1_score + '0', RED, SCORE_SCALE
    );

    draw_char
    (
        separation_line_x + SCORE_X_OFFSET - SCORE_WIDTH, SCORE_Y_OFFSET,
        (char) p2_score + '0', BLUE, SCORE_SCALE
    );
}