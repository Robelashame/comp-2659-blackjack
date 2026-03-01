#ifndef TESTMODEL_H
#define TESTMODEL_H

#include <stdbool.h>

#include "model.h"

void test_two_player (Model *game);

void test_game_start(Model *game);

void test_hit(Model *game);

void test_stand(Model *game);

void test_win(Model *game);

void test_lose(Model *game);

void test_new_round(Model *game);

void test_quit(Model *game);

#endif