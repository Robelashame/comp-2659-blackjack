#ifndef DEALER_H
#define DEALER_H

#include "hand.h"
#include "card.h"
#include "deck.h"

typedef struct {
    Hand hand;
    Card hidden_card;
    bool is_showing_hidden;
} Dealer;

void dealer_play(Dealer *dealer, Deck *shoe);


void show_hidden(Dealer *dealer);

#endif