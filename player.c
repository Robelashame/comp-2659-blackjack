#include "player.h"

void hit_plr(Player *player, Deck *shoe) {
    Card delt_card = deal(shoe);
    add_card(&player->hand, &delt_card);
    player->active_turn = !(is_blackjack(&player->hand) || is_bust(&player->hand));
}

void stand_plr(Player *player) {
    player->active_turn = false;
}

void bet_on_hand(Player *player, int bet_amount) {
    player->bank -= bet_amount;
    player->total_bet += bet_amount;
}