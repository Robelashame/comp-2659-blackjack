#ifndef PLAYER_H
#define PLAYER_H

#include "hand.h"

typedef struct {
    int bank;
    int total_bet;
    Hand hand;
    bool active_turn;
} Player;


#endif