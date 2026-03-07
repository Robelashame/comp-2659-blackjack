#include "model.h"
#include <string.h>
#include <stdio.h>

void initialize_game(Model *game) {
    int player_count;
    
    memset(game, 0, sizeof(Model));
    initialize_deck(&game->deck);
    shuffle(&game->deck);

    printf("Press 1 for player 2: ");
    scanf("%d", &player_count);

    two_players(game,player_count);

    game->player1.bank = 1000;
    game->player2.bank = 1000;

    if (game->is_there_player2 == TRUE) {
        game->player1.hand_position[0] = 265;
        game->player1.hand_position[1] = 35;
        game->player2.hand_position[0] = 265;
        game->player2.hand_position[1] = 355;
    } else {
        game->player1.hand_position[0] = 265;
        game->player1.hand_position[1] = 280;
    }

    game->dealer.position[0] = 20;
    game->dealer.position[1] = 280;

    memcpy(game->dealer.hand.position, game->dealer.position, sizeof(game->dealer.position));
    memcpy(game->player1.hand.position, game->player1.hand_position, sizeof(game->player1.hand_position));
    if (game->is_there_player2)
            memcpy(game->player2.hand.position, game->player2.hand_position, sizeof(game->player2.hand_position));


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

    if (game->deck.top > 208) { /*if 4/6 ths of the shoe has been used */
        shuffle(&game->deck);
    }

    game->player1_turn = TRUE;
    game->player2_turn = FALSE;
    game->dealer_turn = FALSE;
    game->is_round_over = FALSE;

}

void two_players(Model *game, int is_there_plr_2) {
    if  (is_there_plr_2 == 1)
        game->is_there_player2 = is_there_plr_2;
    else
        game->is_there_player2 = FALSE;
}

void give_start_cards(Model *game) {
    Card dealt_card;
    if (game->is_there_player2 == TRUE) {
        dealt_card = deal(&game->deck);    /*player 1 first card */
        add_card(&game->player1.hand, &dealt_card);

        dealt_card = deal(&game->deck); /*player 2 first card */
        add_card(&game->player2.hand, &dealt_card);

        dealt_card = deal(&game->deck);
        add_card(&game->dealer.hand, &dealt_card); /*dealer first card */

        dealt_card = deal(&game->deck); /*player 1 second card */
        add_card(&game->player1.hand, &dealt_card);

        dealt_card = deal(&game->deck); /*player 2 second card */
        add_card(&game->player2.hand, &dealt_card);

        dealt_card = deal(&game->deck); /*dealer hidden card */
        add_hidden_card(&game->dealer, &dealt_card);
    } else {
        dealt_card = deal(&game->deck);    /* player 1 first card */
        add_card(&game->player1.hand, &dealt_card);

        dealt_card = deal(&game->deck);
        add_card(&game->dealer.hand, &dealt_card); /*dealer first card */

        dealt_card = deal(&game->deck); /*player 1 second card */
        add_card(&game->player1.hand, &dealt_card);

        dealt_card = deal(&game->deck); /* dealer hidden card */
        add_hidden_card(&game->dealer, &dealt_card);
    }
}