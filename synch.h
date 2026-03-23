#ifndef SYNCH_H
#define SYNCH_H

#include "model.h"

void update_timer(Model *game);

int move_card(Model *game);

/* moves 'current' toward 'target' by at most 'step'
   returns the new value */

int move_toward(int current, int target, int step);

#endif