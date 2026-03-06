#include "render.h"
#include "string.h"
#include "stdio.h"

void render_card(const Card *card, UINT8 *base) {
    if (card->is_flipped) {
        clear_region(base, card->position[0], card->position[1], 80, 55);
        plot_rectangle(base, card->position[0], card->position[1], 80, 55);
        plot_string(base, card->position[0] + 40, card->position[1] + 20, "FLIPED");
        return;
    }

    char rank[10];
    char suit[10];
    strcpy(rank, card->rank);
    strcpy(suit, card->suit);
    clear_region(base, card->position[0], card->position[1], 80, 55);
    plot_rectangle(base, card->position[0], card->position[1], 80, 55);
    plot_character(base, (card->position[0] + 2), (card->position[1] + 9), rank[0]);
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

    // convert integers to strings
    sprintf(bank_int, "%d", player->bank);
    sprintf(value_int, "%d", player->value);
    sprintf(bet_int, "%d", player->bet);

    // append the numbers to the text
    strcat(bank, bank_int);
    strcat(value, value_int);
    strcat(bet, bet_int);

    plot_string(base, player->hand_position[0] + 105, player->hand_position[1], bank);
    plot_string(base, player->hand_position[0] - 20, player->hand_position[1], value);
    plot_string(base, player->hand_position[0] - 40, player->hand_position[1], bet);

    render_hand(&player->hand, base);
}

void render_dealer(const Dealer *dealer, UINT8 *base) {
    char value[20] = "Value: ";
    char value_int[10];

    sprintf(value_int, "%d", dealer->hand.value);
    strcat(value, value_int);

    render_card(dealer->hidden_card, base);
    render_hand(dealer->hand, base);
    
    plot_string(base, dealer->position[0] + 20, dealer->position[1], value);
}

void render_timer(const Timer *timer, UINT8 *base) {
    char timer_str[20] = "Seconds Left: ";
    char seconds_int[10];

    // convert integer seconds to string
    sprintf(seconds_int, "%d", timer->seconds);

    // append the number to the string
    strcat(timer_str, seconds_int);

    plot_string(base, 200, 300, timer_str);
}

void render(const Model *model, *base) {
    render_dealer(&model->dealer, base);
    render_player(&model->player1, base);
    if (model->is_there_player2)
        render_player(&model->player2, base);
    render_timer(&model->timer, base);
}