#include "model.h"

void initialize_game(Model *game) {
    *game = (Model){0};
    
    initialize_deck(&game->deck);
    shuffle(&game->deck);

    game->player1.bank = 1000;
    game->player2.bank = 1000;

    give_start_cards(game);

    initialize_timer(&game->timer, 60);
    
    game->player1_turn = TRUE;
    game->player2_turn = FALSE;
    game->dealer_turn = FALSE;
    game->is_round_over = FALSE;
}

void new_round(Model *game) {
    remove_cards(&game->player1.hand);
    remove_cards(&game->player2.hand);
    remove_cards(&game->dealer.hand);
    
    give_start_cards(game);

    if (game->deck.top > 208) { //if 4/6 ths of the shoe has been used
        shuffle(&game->deck);
    }

    game->player1_turn = TRUE;
    game->player2_turn = FALSE;
    game->dealer_turn = FALSE;
    game->is_round_over = FALSE;

}

void two_players(Model *game, int is_there_plr_2) {
    game->is_there_player2 = is_there_plr_2;
}

void give_start_cards(Model *game) {
    Card dealt_card;
    if (game->is_there_player2 == TRUE) {
        dealt_card = deal(&game->deck);    //player 1 first card
        add_card(&game->player1.hand, &dealt_card);

        dealt_card = deal(&game->deck); //player 2 first card
        add_card(&game->player2.hand, &dealt_card);

        dealt_card = deal(&game->deck);
        add_card(&game->dealer.hand, &dealt_card); //dealer first card

        dealt_card = deal(&game->deck); //player 1 second card
        add_card(&game->player1.hand, &dealt_card);

        dealt_card = deal(&game->deck); //player 2 second card
        add_card(&game->player2.hand, &dealt_card);

        dealt_card = deal(&game->deck); //dealer hidden card
        add_hidden_card(&game->dealer, &dealt_card);
    } else {
        dealt_card = deal(&game->deck);    //player 1 first card
        add_card(&game->player1.hand, &dealt_card);

        dealt_card = deal(&game->deck);
        add_card(&game->dealer.hand, &dealt_card); //dealer first card

        dealt_card = deal(&game->deck); //player 1 second card
        add_card(&game->player1.hand, &dealt_card);

        dealt_card = deal(&game->deck); //dealer hidden card
        add_hidden_card(&game->dealer, &dealt_card);
    }
}