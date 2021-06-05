#ifndef MENU_H
#define MENU_H

#include <stdbool.h>

#include "mzapo_parlcd.h"
#include "mzapo_phys.h"
#include "mzapo_regs.h"
#include "text_utils.h"
#include "params.h"
#include "periphery_utils.h"
#include "game_states.h"
#include "state_controller.h"


#define TITLE_LETTERS_SCALE 10
#define TITLE_LETTERS_X_OFFSET 120
#define TITLE_Y_OFFSET 0

#define MENU_Y_OFFSET 150
#define MENU_TEXT_SCALE 2

void update_menu();

void render_menu();

void init_menu();

#endif