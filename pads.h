#ifndef PADS_H
#define PADS_H

#include <stdbool.h>

#include "mzapo_parlcd.h"
#include "mzapo_phys.h"
#include "mzapo_regs.h"
#include "text_utils.h"
#include "params.h"
#include "periphery_utils.h"
#include "game_states.h"
#include "state_controller.h"

#define PADS_X_OFFSET 10
#define PADS_HEIGHT 60
#define PADS_WIDTH 7
#define PADS_MOVE_SPEED 30

void render_pads();

void init_pads();

void update_pads();

#endif