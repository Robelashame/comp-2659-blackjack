#include "cond.h"
#include "asynch.h"

void start_game(Model *game) {
    initialize_game(game);
}

void new_round_start(Model *game) {
    new_round(game);
}

void dealer_draws(Model *game) {
    dealer_play(&game->dealer, &game->deck);
    game->dealer_turn = false;
}

void player_turn_ends(Model *game) {
    if (game->player1_turn == true) {
        if (is_blackjack(&game->player1.hand) || is_bust(&game->player1.hand)) {
            if (game->is_there_player2) {
                game->player1_turn = false;
                game->player2_turn = true;
            } else {
                game->player1_turn = false;
                game->dealer_turn = true;
            }
        }
    } else if (game->player2_turn == true){
        if (is_blackjack(&game->player2.hand) || is_bust(&game->player2.hand)) {
            game->player2_turn = false;
            game->dealer_turn = true;
        }
    }
}

void timeout(Model *game) {
    if (game->timer.seconds == 0) {
        stand(game);
    }
}

void outcome(Model *game, int player_number) {
    Player *player;

    if (player_number == 2) {
        player = &game->player2; 
    } else {
        player = &game->player1; 
    }

    if ((game->dealer.hand.value < player->hand.value) && (player->hand.value != 21)) {
        player->bank += (player->total_bet * 2);
    } else if ((game->dealer.hand.value < player->hand.value) && (player->hand.value == 21)) {
        player->bank += (player->total_bet * 5) / 2;    //3 to 2 payout for getting blackjack
    } else if (game->dealer.hand.value > 21 && player->hand.value <= 21) {
        player->bank += (player->total_bet * 2);
    } else if (game->dealer.hand.value == player->hand.value){
        player->bank += player->total_bet;
    }
    
    player->total_bet = 0;
}

