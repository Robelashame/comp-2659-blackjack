#include "testmodel.h"
#include <stdio.h>

void test_two_player(Model *game) {
    int player_count;
    printf("Press 1 for player 2: ");
    scanf("%d", &player_count);
    if (player_count == 1) {
        game->is_there_player2 = true;
        printf("Game will have 2 players");
    } else {
        game->is_there_player2 = false;
        printf("Game will have 1 player");
    }
}

void test_game_start(Model *game) {
    initialize_game(game);

    Hand plr_1_hand = game->player1.hand;
    Dealer game_dealer = game->dealer;
    Deck shoe = game->deck;

    printf("Game start:\n");
    printf("Player 1 starting card 1: %s of %s, ", plr_1_hand.cards[0].rank, plr_1_hand.cards[0].suit);
    printf("%s of %s\n", plr_1_hand.cards[1].rank, plr_1_hand.cards[1].suit);
    printf("Dealer showing card: %s of %s, ", game_dealer.hand.cards[0].rank, game_dealer.hand.cards[0].suit);
    printf("Hidden card: %s of %s\n", game_dealer.hidden_card.rank, game_dealer.hidden_card.value);
    printf("Deck top card: %s of %s\n", shoe.cards[shoe.top].rank, shoe.cards[shoe.top].suit);
    printf("Player 1 turn\n");
}

void test_hit(Model *game) {
    hit(game);
    
    Hand plr_1_hand = game->player1.hand;

    printf("Player 1 new card: %s of %s\n", plr_1_hand.cards[2].rank, plr_1_hand.cards[2].suit);
    printf("Player 1 hand value: %d", plr_1_hand.value);
    player_turn_ends(game);
    if (game->player1_turn == true) {
        printf("It is still player 1's turn, standing for dealer turn");
        stand(game);
        if (game->is_there_player2 == true)
            stand(game);
    } else {
        if (game->is_there_player2 == true)
            stand(game);
    }
}

void test_win_or_lose(Model *game) {
    dealer_draws(game);

    int bank_before = game->player1.bank;
    int bet = game->player1.total_bet;

    outcome(game, 1);

    if (bank_before == game->player1.bank)
        printf("Player 1 lost");
    else if (bank_before + bet == game->player1.bank)
        printf("Player 1 draw");
    else
        printf("Player 1 win");
}
