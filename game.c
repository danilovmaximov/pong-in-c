#include "game.h"

int p1_score = INIT_SCORE;
int p2_score = INIT_SCORE;

int separation_line_x = DISPLAY_WIDTH / 2 + 2 * SEPARATION_LINE_WIDTH;

void check_score()
{
    if (p1_score == 10)
    {
        winner = PLAYER_1;
        p1_score = INIT_SCORE;
        state = END;
        init_end_led();
    }
    else if (p2_score == 10)
    {
        winner = PLAYER_2;
        p2_score = INIT_SCORE;
        state = END;
        init_end_led();
    }
}

void pause_game()
{
    state = MENU;
}

void update_gamefield()
{
    check_score();
    update_led();
    update_pads();
    update_ball();

    if (knob_pressed == GREEN_KNOB_PRESSED) 
    {
        *rgb_led1 = 0;
        *rgb_led2 = 0;
        pause_game();
    }
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
    render_ball();
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

void update_score(int side)
{
    if (side == PLAYER_1) p1_score++;
    else if (side == PLAYER_2) p2_score++;
    else printf("Something's really wrong here!\n");
}