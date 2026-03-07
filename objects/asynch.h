#ifndef ASYNCH_H
#define ASYNCH_H

#include "model.h"

void hit(Model *game);

void stand(Model *game);

void increase_bet(Model *game);

void decrease_bet(Model *game);

void bet_confirmed(Model *game);

void quit(Model *game);

#endif