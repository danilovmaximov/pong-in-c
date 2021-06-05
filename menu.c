#include "menu.h"

int choice = 1;

u_int8_t old_knob;
u_int8_t new_knob; 

void render_title()
{
    const char letters[4] = {'P', 'O', 'N', 'G'};
    for (int i = 0; i < 4; i++)
    {
        draw_char
        (
            i * TITLE_LETTERS_X_OFFSET,
            TITLE_Y_OFFSET,
            letters[i],
            RED,
            TITLE_LETTERS_SCALE
        );
    }
}

void render_buttons()
{
    draw_string
    (
        DISPLAY_WIDTH / 2 - string_width("PLAY"),
        MENU_Y_OFFSET,
        "PLAY",
        MENU_TEXT_SCALE,
        0,
        WHITE
    );

    draw_string
    (
        DISPLAY_WIDTH / 2 - string_width("EXIT"),
        MENU_Y_OFFSET * 1.33,
        "EXIT",
        MENU_TEXT_SCALE,
        0,
        WHITE
    );
}

void render_credits()
{
    char CREDIT[] = "made by Danil Maksimov";

    draw_string
    (
        DISPLAY_WIDTH / 2 - string_width(CREDIT) / 2,
        MENU_Y_OFFSET * 1.66,
        CREDIT,
        MENU_TEXT_SCALE / 2,
        0,
        WHITE
    );
}

void render_choice()
{
    switch (choice)
    {
        case -1:
            fill_rect(DISPLAY_WIDTH / 2 - string_width("PLAY"), MENU_Y_OFFSET + 30, string_width("PLAY") * 2, 4, WHITE);
            break;
        case 1:
            fill_rect(DISPLAY_WIDTH / 2 - string_width("EXIT"), MENU_Y_OFFSET * 1.33 + 30, string_width("EXIT") * 2, 4, WHITE);
            break;
    }
}

void render_menu()
{
    render_title();
    render_buttons();
    render_choice();
    render_credits();
}

void update_menu()
{
    new_knob = green_knob;
    
    int update = old_knob - green_knob;
    if (update != 0) 
    {
        choice *= -1;
        old_knob = new_knob;
    }

    if (knob_pressed == GREEN_KNOB_PRESSED)
    {
        switch (choice)
        {
        case -1:
            state = READY;
            break;
        case 1:
            quit();
            break;
        }
    }
}

void init_menu()
{
    old_knob = green_knob;
    new_knob = green_knob;
}
