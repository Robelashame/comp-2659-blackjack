#ifndef TESTMODEL_H
#define TESTMODEL_H

#include <stdbool.h>

#include "model.h"
#include "asynch.h"
#include "synch.h"
#include "cond.h"

void test_two_player (Model *game);

void test_game_start(Model *game);

void test_hit(Model *game);

void test_win_or_lose(Model *game);

#endif