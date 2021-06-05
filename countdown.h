#ifndef COUNTDOWN_H
#define COUNTDOWN_H

#include <stdbool.h>

#include "mzapo_parlcd.h"
#include "mzapo_phys.h"
#include "mzapo_regs.h"
#include "text_utils.h"
#include "params.h"
#include "periphery_utils.h"
#include "game_states.h"
#include "state_controller.h"
#include "pads.h"

#define REAL_COUNTDOWN_LENGTH 60
#define COUNTDOWN_BASE 9
#define USER_COUNTDOWN_LENGTH 3

int run_countdown();

void render_countdown(int cur_countdown);

#endif