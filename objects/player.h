#ifndef PLAYER_H
#define PLAYER_H

#include "hand.h"
#include "deck.h"

typedef struct {
    int bank;
    int total_bet;
    Hand hand;
    int active_turn;
    int hand_position[2];
} Player;

void hit_plr(Player *player, Deck *shoe);

void stand_plr(Player *player);

void bet_on_hand(Player *player, int bet_amount);

#endif