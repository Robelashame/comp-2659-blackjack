#include "dealer.h"

#define CARD_START_ROW 0
#define CARD_START_COL 0

void show_hidden(Dealer *dealer) {
    dealer->hidden_card.is_hidden = FALSE;
    hidden_to_hand(&dealer->hand, &dealer->hidden_card);
}

void hidden_to_hand(Hand *hand, Card *card) {
    int index;
    index = hand->num_of_cards;

    hand->cards[index] = (*card);
    hand->num_of_cards++;

    hand->value = calculate_hand_value(hand);
}

void dealer_play(Dealer *dealer, Deck *shoe) {
    Card dealt_card;

    if (dealer->hidden_card.is_hidden == TRUE) {
        show_hidden(dealer);
    } else if (dealer->hand.value < 17 && !(dealer->hand.cards[dealer->hand.num_of_cards - 1].is_moving) && !(dealer->hidden_card.is_moving)){
        dealt_card = deal(shoe);
        add_card(&dealer->hand, &dealt_card);
    }
    
}

void add_hidden_card(Dealer *dealer, Card *card) {
    dealer->hidden_card = (*card);
    dealer->hidden_card.is_hidden = TRUE;

    dealer->hidden_card.position[0] = CARD_START_ROW;
    dealer->hidden_card.position[1] = CARD_START_COL;

    dealer->hidden_card.start_position[0] = dealer->hidden_card.position[0];
    dealer->hidden_card.start_position[1] = dealer->hidden_card.position[1];

    dealer->hidden_card.target_position[0] = 30;
    dealer->hidden_card.target_position[1] = 220;
    
    dealer->hidden_card.path_progress = 0;
    dealer->hidden_card.is_moving = TRUE;
}
