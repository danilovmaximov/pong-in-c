#ifndef START_H
#define START_H

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <stdbool.h>

#include "state_controller.h"
#include "font_types.h"
#include "mzapo_parlcd.h"
#include "mzapo_phys.h"
#include "mzapo_regs.h"

struct timespec delay = {.tv_sec = 0, .tv_nsec = 17 * 1000 * 1000};

#endif