#ifndef MODEL_H
#define MODEL_H

#include "player.h"
#include "dealer.h"
#include "deck.h"
#include "timer.h"

typedef struct {
    Player player1;
    Player player2;
    Dealer dealer;
    Deck deck;
    Timer timer;
    bool is_there_player2;
    bool player1_turn;
    bool player2_turn;
    bool dealer_turn;
    bool is_round_over;
    bool is_game_over;
} Model;

void new_round(Model *game);

void initialize_game(Model *game);

void give_start_cards(Model *game);

void two_players(Model *game, bool is_there_plr_2);

#endif