#include "render.h"
#include "string.h"
#include "stdio.h"

static RenderSnapshot front_snapshot;
static RenderSnapshot back_snapshot;

void render_card(const Card *card, UINT8 *base) {
    char rank[10];
    char suit[10];
    
    if (card->is_hidden) {
        clear_region(base, card->position[0], card->position[1], 80, 55);
        plot_rectangle(base, card->position[0], card->position[1], 80, 55);
        plot_string(base, card->position[0] + 40, card->position[1], "HIDDEN");
        return;
    }

    strcpy(rank, card->rank);
    strcpy(suit, card->suit);
    clear_region(base, card->position[0], card->position[1], 80, 55);
    plot_rectangle(base, card->position[0], card->position[1], 80, 55);
    plot_string(base, (card->position[0] + 2), (card->position[1] + 9), rank);
    if (!(strcmp(suit, "D")))
       	plot_16bit_bitmap((UINT16 *)base, (card->position[0] + 10), (card->position[1] + 4), diamond, 16);
    if (!(strcmp(suit, "H")))
        plot_16bit_bitmap((UINT16 *)base, (card->position[0] + 10), (card->position[1] + 4), heart, 16);
    if (!(strcmp(suit, "S")))
        plot_16bit_bitmap((UINT16 *)base, (card->position[0] + 10), (card->position[1] + 4), spade, 16);
    if (!(strcmp(suit, "C")))
        plot_16bit_bitmap((UINT16 *)base, (card->position[0] + 10), (card->position[1] + 4), club, 16);
}

void render_hand(const Hand *hand, UINT8 *base) {
    int i;

    if (hand->num_of_cards == 0)
        return;

    render_card(&hand->cards[0], base);
    for (i = 1; i < hand->num_of_cards; i++) {
        render_card(&hand->cards[i], base);
    }
}

void render_player(const Player *player, UINT8 *base) {
    char bank[20] = "Bank: ";
    char value[20] = "Value: ";
    char bet[20] = "Bet: ";

    char bank_int[10];
    char value_int[10];
    char bet_int[10];

    /* convert integers to strings */
    sprintf(bank_int, "%d", player->bank);
    sprintf(value_int, "%d", player->hand.value);
    sprintf(bet_int, "%d", player->total_bet);

    /*append the numbers to the text */
    strcat(bank, bank_int);
    strcat(value, value_int);
    strcat(bet, bet_int);

    plot_string(base, player->hand_position[0] + 105, player->hand_position[1], bank);
    plot_string(base, player->hand_position[0] - 20, player->hand_position[1], value);
    plot_string(base, player->hand_position[0] - 40, player->hand_position[1], bet);

    render_hand(&player->hand, base);
}

void render_player_text(const Player *player, UINT8 *base) {
    plot_string(base, player->hand_position[0] + 105, player->hand_position[1], bank);
    plot_string(base, player->hand_position[0] - 20, player->hand_position[1], value);
    plot_string(base, player->hand_position[0] - 40, player->hand_position[1], bet);
}

void render_player_cards(const Player *player, UINT8 *base) {
    char bank_int[10];
    char value_int[10];
    char bet_int[10];

    /* convert integers to strings */
    sprintf(bank_int, "%d", player->bank);
    sprintf(value_int, "%d", player->hand.value);
    sprintf(bet_int, "%d", player->total_bet);

    plot_string(base, player->hand_position[0] + 105, player->hand_position[1], bank);
    plot_string(base, player->hand_position[0] - 20, player->hand_position[1], value);
    plot_string(base, player->hand_position[0] - 40, player->hand_position[1], bet);


}

void render_dealer(const Dealer *dealer, UINT8 *base) {
    char value[20] = "Value: ";
    char value_int[10];

    sprintf(value_int, "%d", dealer->hand.value);
    strcat(value, value_int);

    render_card(&dealer->hidden_card, base);
    render_hand(&dealer->hand, base);
    
    plot_string(base, dealer->position[0] - 20, dealer->position[1], value);
}

void render_timer_text(const Timer *timer, UINT8 *base) {
    plot_string(base, 200, 280, "Seconds Left: ");
}

void render_timer_tick(const Timer *timer, UINT8 *base) {
    char seconds_int[10];

    /* convert integer seconds to string */
    sprintf(seconds_int, "%d", timer->seconds);

    clear_region(base, 200, 330, 16, 8);
    plot_string(base, 200, 330, seconds_int);
}

void render(const Model *model, UINT8 *base) {
    render_dealer(&model->dealer, base);
    render_player(&model->player1, base);
    render_timer(&model->timer, base);
    if (model->is_there_player2)
        render_player(&model->player2, base);
}

void create_snapshot(const Model *game, RenderSnapshot *snap) {
    snap->player1 = game->player1;
    snap->player2 = game->player2;
    snap->dealer = game->dealer;
    snap->timer = game->timer;

    snap->is_there_player2 = game->is_there_player2;

    snap->player1_bet = game->player1_bet;
    snap->player2_bet = game->player2_bet;

    snap->player1_turn = game->player1_turn;
    snap->player2_turn = game->player2_turn;
    snap->dealer_turn = game->dealer_turn;

    snap->dealing_start_cards = game->dealing_start_cards;
    snap->outcome_applied = game->outcome_applied;
    snap->is_round_over = game->is_round_over;
    snap->is_game_over = game->is_game_over;
}

void render_min(const Model *model, UINT8 *base) {
    
}