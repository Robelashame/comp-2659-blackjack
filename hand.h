#ifndef HAND_H
#define HAND_H
#include <stdbool.h>

#include "card.h"

typedef struct {
    Card cards[20];
    int value;
    int bet_amount;
    int position[2];
    int num_of_cards;
} Hand;

void add_card(Hand *hand, Card *card);

int calculate_hand_value(Hand *hand);

bool is_blackjack(Hand *hand);

bool is_bust(Hand *hand);

#endif