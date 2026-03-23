#ifndef HANDLE_H
#define HANDLE_H
#include "model.h"
#include "asynch.h"
#include "synch.h"
#include "input.h"
#include "TYPES.H"

void handle_input(Model *game, char cin, int in_prog);

void update_model(Model *game, int *in_prog);

void prompts(Model *game, UINT8 *base);


#endif