#ifndef HAND_H
#define HAND_H
#define TRUE 1
#define FALSE 0

#include "card.h"

typedef struct {
    Card cards[20];
    int value;
    int bet_amount;
    int position[2];
    int num_of_cards;
} Hand;

void add_card(Hand *hand, Card *card);

void remove_cards(Hand *hand);

int calculate_hand_value(Hand *hand);

int is_blackjack(Hand *hand);
int is_bust(Hand *hand);

#endif