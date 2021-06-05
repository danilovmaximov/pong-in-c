#include "state_controller.h"

int state, scale;
bool in_state_transition = true;

int winner = 0;

int countdown;

struct timespec delay =
{
    .tv_sec = 0,
    .tv_nsec = 17 * 1000 * 1000
};

void update(int* state)
{
    switch (*state)
    {
        case MENU:
            update_menu();
            break;

        case READY:
            countdown = run_countdown();
            break;

        case RUNNING:
            update_gamefield();
            break;

        case END:
            update_end_screen();
            break;
    }
}

void render(int* state)
{
    clean_display();

    switch(*state)
    {
        case MENU:
            render_menu();
            break;

        case READY:
            render_countdown(countdown);
            break;

        case RUNNING:
            render_gamefield();
            break;

        case END:
            render_end_screen(winner);
    }

    render_screen_data(parlcd_mem_base);
}

void quit()
{
    clean_display();
    free(fb);
    exit(0);
}