#ifndef DEALER_H
#define DEALER_H

#include "hand.h"
#include "card.h"

typedef struct {
    Hand hand;
    Card hidden_card;
    bool is_showing_hidden;
} Dealer;

#endif