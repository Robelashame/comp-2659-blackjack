#include "dealer.h"

void show_hidden(Dealer *dealer) {
    dealer->is_showing_hidden = TRUE;
    dealer->hidden_card.is_hidden = FALSE;
    add_card(&dealer->hand, &dealer->hidden_card);
}

void dealer_play(Dealer *dealer, Deck *shoe) {
    Card dealt_card;

    add_card(&dealer->hand, &dealer->hidden_card);

    while (dealer->hand.value < 17){
        dealt_card = deal(shoe);
        add_card(&dealer->hand, &dealt_card);
    }
    
}

void add_hidden_card(Dealer *dealer, Card *card) {
    dealer->hidden_card = (*card);
    dealer->is_showing_hidden = FALSE;
    dealer->hidden_card.is_hidden = TRUE;
    dealer->hidden_card.position[0] = 30;
    dealer->hidden_card.position[1] = 220;
}
