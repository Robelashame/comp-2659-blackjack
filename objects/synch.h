#ifndef SYNCH_H
#define SYNCH_H

#include "model.h"

void timer(Model *game);    /*cant implement right now, cant reliably track seconds */

void move_card(Model *game);    /*cant implement right now, not on animations yet */

/* moves 'current' toward 'target' by at most 'step'
   returns the new value */

int move_toward(int current, int target, int step);

#endif