#ifndef MODEL_H
#define MODEL_H

#include "player.h"
#include "dealer.h"
#include "deck.h"
#include "timer.h"

typedef struct {
    Player player1;
    Player player2;
    Dealer dealer;
    Deck deck;
    Timer timer;
    bool is_there_player2;
} game;

#endif