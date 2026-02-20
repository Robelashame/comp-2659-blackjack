#ifndef PLAYER_H
#define PLAYER_H

#include "hand.h"
#include "deck.h"

typedef struct {
    int bank;
    int total_bet;
    Hand hand;
    bool active_turn;
} Player;

void hit(Player *player, Deck *shoe);

void stand(Player *player);

#endif