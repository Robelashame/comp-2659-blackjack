#include "hand.h"

int calculate_hand_value(Hand *hand) {
    int value = 0;
    for (int i = 0; i < hand->num_of_cards; i++) {
        value += hand->cards[i].value;
    }
    return value;
}

void add_card(Hand *hand, Card *card) {
    int index = 0;
    while (index < hand->num_of_cards) {
        index++;
    }
    hand->cards[index] = (*card);
    hand->num_of_cards++;
    if (card->value == 11 && hand->value > 11) {
        hand->value++;
    } else {
        hand->value = calculate_hand_value(hand);
    }
}

bool is_blackjack(Hand *hand) {
    if (hand->value == 21)
        return true;
    else 
        return false;
}

bool is_bust(Hand *hand) {
    if (hand->value > 21)
        return true;
    else 
        return false;
}

void remove_cards(Hand *hand) {
    for (int i = 0; i < hand->num_of_cards; i++) {
        hand->cards[i] = (Card){0};
    }
    hand->num_of_cards = 0;
    hand->bet_amount = 0;
    hand->value = 0;
}