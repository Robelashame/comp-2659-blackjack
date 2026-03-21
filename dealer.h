#ifndef DEALER_H
#define DEALER_H

#include "hand.h"
#include "card.h"
#include "deck.h"

typedef struct {
    Hand hand;
    Card hidden_card;
    int is_showing_hidden;
    int position[2];
} Dealer;

void include_hidden(Dealer *dealer);

void dealer_play(Dealer *dealer, Deck *shoe);

void hidden_to_hand(Hand *hand, Card *card);


void add_hidden_card(Dealer *dealer, Card *card);

void show_hidden(Dealer *dealer);

#endif