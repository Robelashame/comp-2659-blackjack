#ifndef HANDLE_H
#define HANDLE_H
#include "objects/model.h"
#include "objects/asynch.h"
#include "objects/synch.h"

void handle_input(Model *game, char cin);

void update_model(Model *game);

#endif