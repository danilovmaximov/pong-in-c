#ifndef MENU_H
#define MENU_H

#include "text_utils.h"
#include "params.h"
#include "periphery_utils.h"
#include "game_states.h"
#include "state_controller.h"

#define TITLE_LETTERS_SCALE 10
#define TITLE_LETTERS_X_OFFSET 120
#define TITLE_Y_OFFSET 0

#define MENU_Y_OFFSET 180
#define MENU_TEXT_SCALE 2

/*
 *  Method contating main menu's logic
 */
void update_menu();

/*
 *  Method for rendering the line which underlines player's button choice in the menu
 */
void render_menu();

/*
 *  Method for initializing menu's variables
 */
void init_menu();

#endif