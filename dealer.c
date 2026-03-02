#include "dealer.h"

void show_hidden(Dealer *dealer) {
    dealer->is_showing_hidden = true;
    add_card(&dealer->hand, &dealer->hidden_card);
}

void dealer_play(Dealer *dealer, Deck *shoe) {
    
    add_card(&dealer->hand, &dealer->hidden_card);

    while (dealer->hand.value < 17){
        Card dealt_card = deal(shoe);
        add_card(&dealer->hand, &dealt_card);
    }
    
}

void add_hidden_card(Dealer *dealer, Card *card) {
    dealer->hidden_card = (*card);
}
