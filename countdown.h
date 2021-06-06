#ifndef COUNTDOWN_H
#define COUNTDOWN_H

#include <stdbool.h>

#include "text_utils.h"
#include "params.h"
#include "periphery_utils.h"
#include "game_states.h"
#include "state_controller.h"
#include "pads.h"

#define REAL_COUNTDOWN_LENGTH 60
#define COUNTDOWN_BASE 9
#define USER_COUNTDOWN_LENGTH 3

/*
 *  Method for counting down from 3 before game starts.
 */
int run_countdown();

/*
 *  Method for rendering the countdown before the game starts.
 */
void render_countdown(int cur_countdown);

#endif