#ifndef DECK_H
#define DECK_H

#define CARDS_PER_DECK 52
#define NUMBER_OF_DECKS 6

#include "card.h"

typedef struct {
    Card cards[CARDS_PER_DECK * NUMBER_OF_DECKS]; //6 standard decks
    int top; //index for top
} Deck;

void initialize_deck(Deck *deck);

void shuffle(Deck *cards);

Card deal(Deck *cards);

#endif