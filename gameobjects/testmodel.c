#include "testmodel.h"
#include <stdio.h>

void test_two_player(Model *game) {
    int player_count;
    printf("Press 1 for player 2: ");
    scanf("%d", &player_count);
    if (player_count == 1) {
        game->is_there_player2 = TRUE;
        printf("Game will have 2 players(but im not showing it just trust me)\n");
    } else {
        game->is_there_player2 = FALSE;
        printf("Game will have 1 player\n");
    }
}

void test_game_start(Model *game) {
    Hand plr_1_hand;
    Dealer game_dealer;
    Deck shoe;
    
    initialize_game(game);

    plr_1_hand = game->player1.hand;
    game_dealer = game->dealer;
    shoe = game->deck;

    printf("Game start:\n");
    printf("Player 1 starting card 1: %s of %s, ", plr_1_hand.cards[0].rank, plr_1_hand.cards[0].suit);
    printf("%s of %s\n", plr_1_hand.cards[1].rank, plr_1_hand.cards[1].suit);
    printf("Dealer showing card: %s of %s, ", game_dealer.hand.cards[0].rank, game_dealer.hand.cards[0].suit);
    printf("Hidden card: %s of %s\n", game_dealer.hidden_card.rank, game_dealer.hidden_card.suit);
    printf("Deck top card: %s of %s\n", shoe.cards[shoe.top].rank, shoe.cards[shoe.top].suit);
    printf("Player 1 turn\n");
}

void test_hit(Model *game) {
    Hand plr_1_hand;
    
    hit(game);
    
    plr_1_hand = game->player1.hand;

    printf("Player 1 new card: %s of %s\n", plr_1_hand.cards[2].rank, plr_1_hand.cards[2].suit);
    printf("Player 1 hand value: %d\n", plr_1_hand.value);
    player_turn_ends(game);
    if (game->player1_turn == TRUE) {
        printf("It is still player 1's turn, standing for dealer turn\n");
        stand(game);
        if (game->is_there_player2 == TRUE)
            stand(game);
    } else {
        if (game->is_there_player2 == TRUE)
            stand(game);
    }
}

void test_win_or_lose(Model *game) {
    int player1value;
    int dealervalue;
    
    dealer_draws(game);

    outcome(game, 1);

    player1value = game->player1.hand.value;
    dealervalue = game->dealer.hand.value;

    printf("Dealers hand value: %d\n", dealervalue);
    if (player1value > 21) {
        printf("Player 1 lost\n");   // player busts → always lose
    } else if (dealervalue > 21) {
        printf("Player 1 win\n");    // dealer busts → player wins (only if player didn't bust)
    } else if (player1value > dealervalue) {
        printf("Player 1 win\n");    // player higher without bust
    } else if (player1value < dealervalue) {
        printf("Player 1 lost\n");   // dealer higher without bust
    } else {
        printf("Player 1 draw\n");   // equal values, no bust
    }
}
