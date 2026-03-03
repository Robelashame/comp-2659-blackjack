#include "dealer.h"

void show_hidden(Dealer *dealer) {
    dealer->is_showing_hidden = TRUE;
    add_card(&dealer->hand, &dealer->hidden_card);
}

void dealer_play(Dealer *dealer, Deck *shoe) {
    
    add_card(&dealer->hand, &dealer->hidden_card);

    Card dealt_card;

    while (dealer->hand.value < 17){
        dealt_card = deal(shoe);
        add_card(&dealer->hand, &dealt_card);
    }
    
}

void add_hidden_card(Dealer *dealer, Card *card) {
    dealer->hidden_card = (*card);
}
