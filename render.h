#ifndef RENDER_H
#define RENDER_H

#include "types.h"
#include "raster.h"
#include "model.h"
#include "bmaps.h"

typedef struct {
    Player player1;
    Player player2;
    Dealer dealer;
    Timer timer;

    int is_there_player2;

    int player1_bet;
    int player2_bet;

    int player1_turn;   
    int player2_turn;
    int dealer_turn;

    int dealing_start_cards;
    int outcome_applied;
    int is_round_over;
    int is_game_over;
} RenderSnapshot;

void render(const Model *model, UINT8 *base);

void render_player(const Player *player, UINT8 *base);

void render_player_text(const Player *player, UINT8 *base);

void render_player_cards(const Player *player, UINT8 *base);

void render_hand(const Hand *hand, UINT8 *base);

void render_card(const Card *card, UINT8 *base);

void render_dealer(const Dealer *dealer, UINT8 *base);

void render_dealer_text(const Dealer *dealer, UINT8 *base);

void render_dealer_cards(const Dealer *dealer, UINT8 *base);

void render_timer_text(const Timer *timer, UINT8 *base);

void render_timer_tick(const Timer *timer, UINT8 *base);

void create_snapshot(const Model *game, RenderSnapshot *snapshot);

#endif