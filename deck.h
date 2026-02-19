#ifndef DECK_H
#define DECK_H

#include "card.h"

typedef struct {
    Card cards[312];
} Deck;

void shuffle(Deck *cards);

#endif