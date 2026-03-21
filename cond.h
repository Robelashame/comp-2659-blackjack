#ifndef COND_H
#define COND_H

#include "model.h"

void start_game(Model *game);

void new_round_start(Model *game);

void dealer_draws(Model *game);

void outcome(Model *game, int player_number);

void player_bj_or_bust(Model *game); /* for blackjack or bust */

void player_turn_ends(Model *game);

void timeout(Model *game);  /* time runs out */

#endif