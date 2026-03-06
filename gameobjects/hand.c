#include "hand.h"

int calculate_hand_value(Hand *hand) {
    int value;
    int i;
    int ace_count;

    value = 0;
    ace_count = 0;

    for (i = 0; i < hand->num_of_cards; i++) {
        value += hand->cards[i].value;

        if (hand->cards[i].value == 11)
            ace_count++;
        
        while (value > 21 && ace_count > 0) {
            value -= 10;
            ace_count--;
        }
    }
    return value;
}

void add_card(Hand *hand, Card *card) {
    int index;
    index = hand->num_of_cards;

    hand->cards[index] = (*card);
    hand->num_of_cards++;

    hand->value = calculate_hand_value(hand);
}

int is_blackjack(Hand *hand) {
    if (hand->value == 21)
        return TRUE;
    else 
        return FALSE;
}

int is_bust(Hand *hand) {
    if (hand->value > 21)
        return TRUE;
    else 
        return FALSE;
}

void remove_cards(Hand *hand) {
    int i;
    for (i = 0; i < hand->num_of_cards; i++) {
        hand->cards[i].rank[0] = '\0';
        hand->cards[i].suit[0] = '\0';
        hand->cards[i].value = 0;
    }
    hand->num_of_cards = 0;
    hand->bet_amount = 0;
    hand->value = 0;
}