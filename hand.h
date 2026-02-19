#ifndef HAND_H
#define HAND_H

#include "card.h"

typedef struct {
    Card cards[20];
    int value;
    int bet_amount;
    int position[2];
} Hand;


#endif