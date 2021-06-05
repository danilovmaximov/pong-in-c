#include "pads.h"

int p1_pos = DISPLAY_HEIGHT / 2 - PADS_HEIGHT / 2;
int p2_pos = DISPLAY_HEIGHT / 2 - PADS_HEIGHT / 2;

u_int8_t p1_old_knob;
u_int8_t p1_new_knob;
u_int8_t p2_old_knob;
u_int8_t p2_new_knob;

void render_pads()
{
    fill_rect
    (
        PADS_X_OFFSET, p1_pos, PADS_WIDTH, PADS_HEIGHT, RED
    );

    fill_rect
    (
        DISPLAY_WIDTH - PADS_X_OFFSET, p2_pos, PADS_WIDTH, PADS_HEIGHT, BLUE
    );
}

void update_pads()
{
    p1_new_knob = red_knob;
    if (p1_pos < 4) p1_pos += 10;
    else if (p1_pos > DISPLAY_HEIGHT - PADS_HEIGHT - 4) p1_pos -= 10;
    else
    {
        int update = p1_old_knob - p1_new_knob;

        if (update < -1 && update > -50) p1_pos += PADS_MOVE_SPEED;
        if (update > 1 && update < 50) p1_pos -= PADS_MOVE_SPEED;
    }

    p1_old_knob = p1_new_knob;

    p2_new_knob = blue_knob;
    if (p2_pos < 4) p2_pos += 10;
    else if (p2_pos > DISPLAY_HEIGHT - PADS_HEIGHT - 4) p2_pos -= 10;
    else
    {
        int update = p2_old_knob - p2_new_knob;

        if (update < -1 && update > -50) p2_pos += PADS_MOVE_SPEED;
        if (update > 1 && update < 50) p2_pos -= PADS_MOVE_SPEED;
    }

    p2_old_knob = p2_new_knob;
}

void init_pads()
{
    p1_old_knob = red_knob;
    p1_new_knob = red_knob;
    p2_old_knob = blue_knob;
    p2_new_knob = blue_knob;
}