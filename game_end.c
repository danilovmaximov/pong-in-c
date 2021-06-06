#include "game_end.h"

void render_end_screen(int winner)
{
    if (winner == PLAYER_1)
    {
        draw_string
        (
            DISPLAY_WIDTH / 2 - string_width("RED PLAYER WON!"), WINNER_Y_OFFSET, 
            "RED PLAYER WON!", WINNER_TEXT_SCALE, 0, RED
        );
    }

    else
    {
        draw_string
        (
            DISPLAY_WIDTH / 2 -  string_width("BLUE PLAYER WON!"), WINNER_Y_OFFSET, 
            "BLUE PLAYER WON!", WINNER_TEXT_SCALE, 0, BLUE
        );
    }

    draw_string
    (
        DISPLAY_WIDTH / 2 - string_width("press       to continue") / 2, CONTINUE_Y_OFFSET,
        "press    to continue", CONTINUE_TEXT_SCALE, 0, WHITE
    );

    fill_rect
    (
        GREEN_RECT_X, GREEN_RECT_Y, 
        GREEN_RECT_SIZE, GREEN_RECT_SIZE, GREEN
    );
}

void update_end_screen()
{
    end_led();

    if (knob_pressed == GREEN_KNOB_PRESSED) 
    {
        *led_line = 0;
        *rgb_led1 = 0;
        *rgb_led2 = 0;
        state = MENU;
    }
}