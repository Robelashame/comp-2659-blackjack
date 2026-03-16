#include "handle.h"
#include <string.h>

void handle_input(Model *game, char cin) {

    if (game->player1_turn || game->player2_turn) {
        if (cin == 'h') {
            hit(game);
            player_bj_or_bust(game);
        } else if (cin =='s') {
            stand(game);
        }
    }
    
    if (!(game->dealer_turn || game->player1_turn || game->player2_turn)) {
        if (cin == 'w') {
            increase_bet(game);
        } else if (cin == 's') {
            decrease_bet(game);
        } else if (cin == 'c') {
            bet_confirmed(game);
        }
    }

    if (cin == 'q') {
        quit(game);
    }
}

void update_model(Model *game) {
    int num_cards;
    if (game->player1_turn) {
        num_cards = game->player1.hand.num_of_cards;
        if (game->player1.hand.cards[num_cards - 1].is_moving) {
            move_card(game);
        }
    }
    if (game->player2_turn) {
        num_cards = game->player2.hand.num_of_cards;
        if (game->player2.hand.cards[num_cards - 1].is_moving) {
            move_card(game);
        }
    }
}
