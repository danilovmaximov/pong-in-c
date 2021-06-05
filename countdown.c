#include "countdown.h"

int countdown_len = REAL_COUNTDOWN_LENGTH;
int countdown_base = COUNTDOWN_BASE;
int current_countdown = USER_COUNTDOWN_LENGTH;

int run_countdown()
{
    if (countdown_len % 10 == 0) countdown_base -= 1;

    if (countdown_len % 20 == 0 && countdown_len != REAL_COUNTDOWN_LENGTH) 
    {
        countdown_len = REAL_COUNTDOWN_LENGTH;
        current_countdown -= 1;
        countdown_len -= 1;
    } 
    else 
    {
        countdown_len -= 1;
    }

    if (current_countdown == 0) 
    {
        countdown_len = REAL_COUNTDOWN_LENGTH;
        countdown_base = COUNTDOWN_BASE;
        current_countdown = 3;
        state = RUNNING;
        init_pads();
    }

    return current_countdown;
}

void render_countdown(int cur_countdown)
{
    draw_char
    (
        DISPLAY_WIDTH / 2 - char_width((char) cur_countdown + '0') / 2,
        DISPLAY_HEIGHT / 2 - 2 * CHAR_HEIGHT,
        (char) cur_countdown + '0', WHITE, 5
    );
}