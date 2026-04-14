#include "hand.h"
#include <string.h>

#define CARD_START_ROW 0
#define CARD_START_COL 0

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
    int index, spacing, i;
    index = hand->num_of_cards;

    hand->cards[index] = (*card);
    hand->num_of_cards++;

    if (hand->position[0] > 200) {
        spacing = 60;
    } else {
        if (hand->num_of_cards <= 3) spacing = 30;
        else spacing = 40; 
    }

    for (i = 0; i < hand->num_of_cards; i++) {
        hand->cards[i].target_position[0] = hand->position[0];
        hand->cards[i].target_position[1] = hand->position[1] + (i * spacing);
    }

    hand->value = calculate_hand_value(hand);
    hand->cards[index].position[0] = CARD_START_ROW;
    hand->cards[index].position[1] = CARD_START_COL;

    hand->cards[index].start_position[0] = hand->cards[index].position[0];
    hand->cards[index].start_position[1] = hand->cards[index].position[1];

    hand->cards[index].target_position[0] = hand->position[0];
    hand->cards[index].target_position[1] = hand->position[1] + (index * spacing);

    hand->cards[index].path_progress = 0;
    hand->cards[index].is_moving = TRUE;
    hand->cards[index].is_hidden = FALSE;
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