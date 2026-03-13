#include "render.h"
#include "string.h"
#include "stdio.h"

void *front_buffer = Physbase();
UINT32 *back_buffer = (UINT32 *) malloc((SCREEN_WIDTH * (SCREEN_HEIGHT + 20)) / 8);

void swap_buffer() {
    UINT32 *temp = (UINT32 *)front_buffer
    *front_buffer = *back_buffer;
    *back_buffer = *temp
    Setscreen(-1, *front_buffer, -1);
}

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

    /* swap frame buffers*/
    swap_buffer();

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

void render_dealer(const Dealer *dealer, UINT8 *base) {
    char value[20] = "Value: ";
    char value_int[10];

    swap_buffer();

    sprintf(value_int, "%d", dealer->hand.value);
    strcat(value, value_int);

    render_card(&dealer->hidden_card, base);
    render_hand(&dealer->hand, base);
    
    plot_string(base, dealer->position[0] - 20, dealer->position[1], value);
}

void render_timer(const Timer *timer, UINT8 *base) {
    char timer_str[20] = "Seconds Left: ";
    char seconds_int[10];

    swap_buffer();

    /* convert integer seconds to string */
    sprintf(seconds_int, "%d", timer->seconds);

    /* append the number to the string */
    strcat(timer_str, seconds_int);

    plot_string(base, 200, 300, timer_str);
}

void render(const Model *model, UINT8 *base) {
    render_dealer(&model->dealer, base);
    render_player(&model->player1, base);
    if (model->is_there_player2)
        render_player(&model->player2, base);
    render_timer(&model->timer, base);
}