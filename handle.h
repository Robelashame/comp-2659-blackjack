#ifndef HANDLE_H
#define HANDLE_H
#include "model.h"
#include "asynch.h"
#include "synch.h"
#include "input.h"

void handle_input(Model *game, char cin, int in_prog);

void update_model(Model *game, int *in_prog);

void dismiss_outcome(Model *game);


#endif