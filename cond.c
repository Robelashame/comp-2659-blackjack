#include "cond.h"
#include "asynch.h"

void start_game(Model *game) {
    initialize_game(game, 0);
}

void new_round_start(Model *game) {
    new_round(game);
}

void dealer_draws(Model *game) {
    dealer_play(&game->dealer, &game->deck);
    if (game->dealer.hand.value > 17) {
        game->dealer_turn = FALSE;
        game->is_round_over = TRUE;
    }
}

void player_turn_ends(Model *game) {
    if (game ->player1_turn) {
        game->player1_turn = 0;
        if (game->is_there_player2) {
            game->player2_turn = 1;
        } else {
            game->dealer_turn = 1;
        }
    } else if (game->player2_turn) {
        game->player2_turn = 0;
        game->dealer_turn = 1;
    }
}

void player_bj_or_bust(Model *game) {
    if (game->player1_turn == TRUE) {
        if (is_blackjack(&game->player1.hand) || is_bust(&game->player1.hand)) {
            if (game->is_there_player2) {
                game->player1_turn = FALSE;
                game->player2_turn = TRUE;
            } else {
                game->player1_turn = FALSE;
                game->dealer_turn = TRUE;
            }
        }
    } else if (game->player2_turn == TRUE){
        if (is_blackjack(&game->player2.hand) || is_bust(&game->player2.hand)) {
            game->player2_turn = FALSE;
            game->dealer_turn = TRUE;
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
        player->bank += (player->total_bet * 5) / 2;    /* 3 to 2 payout for getting blackjack */
    } else if (game->dealer.hand.value > 21 && player->hand.value <= 21) {
        player->bank += (player->total_bet * 2);
    } else if (game->dealer.hand.value == player->hand.value){
        player->bank += player->total_bet;
    }
    
    player->total_bet = 0;
}

