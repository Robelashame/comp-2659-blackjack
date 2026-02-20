#include "dealer.h"

void show_hidden(Dealer *dealer) {
    dealer->is_showing_hidden = true;
    add_card(&dealer->hand, &dealer->hidden_card);
}

void dealer_play(Dealer *dealer, Deck *shoe) {
    if (dealer->hand.value < 17){
        Card dealt_card = deal(&shoe);
        add_card(&dealer->hand, &dealt_card);
    }
}