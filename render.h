#ifndef RENDER_H
#define RENDER_H

#include "TYPES.H"
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

/* full and minimal rendering */
void render(const Model *model, UINT8 *base);

void render_min(const Model *game, RenderSnapshot *snap, UINT8 *base);

void create_snapshot(const Model *game, RenderSnapshot *snapshot);

/* player rendering */
void render_player(const Player *player, UINT8 *base);

void render_player_bank(const Player *player, UINT8 *base);

void render_player_value(const Player *player, UINT8 *base);

void render_player_bet(const Player *player, UINT8 *base);

void render_player_cards(const Player *player, UINT8 *base);

/* dealer rendering */

void render_dealer(const Dealer *dealer, UINT8 *base);

void render_dealer_value(const Dealer *dealer, UINT8 *base);

void render_dealer_cards(const Dealer *dealer, UINT8 *base);


/* timer and prompt rendering */

void render_timer(const Timer *timer, UINT8 *base);

void render_timer_text(const Timer *timer, UINT8 *base);

void render_timer_tick(const Timer *timer, UINT8 *base);

void render_prompts(Model *game, UINT8 *base);

/* change detection */

int player_bank_changed(const Model *game, RenderSnapshot *snap);

int player_value_changed(const Model *game, RenderSnapshot *snap);

int player_bet_changed(const Model *game, RenderSnapshot *snap);

int player_cards_changed(const Model *game, RenderSnapshot *snap);

int dealer_value_changed(const Model *game, RenderSnapshot *snap);

int dealer_cards_changed(const Model *game, RenderSnapshot *snap);

int timer_changed(const Model *game, RenderSnapshot *snap);

int prompts_changed(const Model *game, RenderSnapshot *snap);

/* clearing functions */

void clear_player_bank(const Player *player, UINT8 *base);

void clear_player_value(const Player *player, UINT8 *base);

void clear_player_bet(const Player *player, UINT8 *base);

void clear_hand_cards(const Hand *hand, UINT8 *base);

void clear_dealer_value(const Dealer *dealer, UINT8 *base);

void clear_timer_tick(const Timer *timer, UINT8 *base);

void clear_prompts(UINT8 *base);

/* utility */

int snapshot_has_moving_cards(const RenderSnapshot *snap);

#endif