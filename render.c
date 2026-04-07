#include "render.h"
#include <string.h>
#include "stdio.h"

#define SCREEN_WIDTH 640

/* full and minimal rendering */

void render(const Model *model, UINT8 *base) {
    render_timer(&model->timer, base);
    render_dealer(&model->dealer, base);
    render_player(&model->player1, base);
    if (model->is_there_player2)
        render_player(&model->player2, base);
}

void render_min(const Model *game, RenderSnapshot *snap, UINT8 *base) {
    if(prompts_changed(game, snap)) {
        clear_prompts(base);
        render_prompts(game, base);
    }
    
    if(player_bank_changed(game, snap)) {
        clear_player_bank(&game->player1, base);
        render_player_bank(&game->player1, base);
    }

    if(player_value_changed(game, snap)) {
        clear_player_value(&game->player1, base);
        render_player_value(&game->player1, base);
    }

    if(player_bet_changed(game, snap)) {
        clear_player_bet(&game->player1, base);
        render_player_bet(&game->player1, base);
    }

    if(player_cards_changed(game, snap)) {
        render_update_hand(&game->player1.hand, &snap->player1.hand, base);
    }

    if(dealer_value_changed(game, snap)) {
        clear_dealer_value(&game->dealer, base);
        render_dealer_value(&game->dealer, base);
    }

    if(dealer_cards_changed(game, snap)) {
        if(snap->dealer.hidden_card.is_moving) {
            clear_region(base, snap->dealer.hidden_card.position[0], snap->dealer.hidden_card.position[1], 80, 55);
        }
        if(game->dealer.hidden_card.is_moving) {
            render_card(&game->dealer.hidden_card, base);
        }

        render_update_hand(&game->dealer.hand, &snap->dealer.hand, base);

        if (!game->dealer.hidden_card.is_moving && !game->dealer.hidden_card.is_hidden) {
        clear_region(base, snap->dealer.hidden_card.position[0], snap->dealer.hidden_card.position[1], 80, 55);
        render_dealer_cards(&game->dealer, base);
    }
    }

    if(timer_changed(game, snap)) {
        clear_timer_tick(&game->timer, base);
        render_timer_tick(&game->timer, base);
    }

    /* updates snapshot */
    create_snapshot(game, snap);
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

static void render_update_hand(const Hand *curr, const Hand *prev, UINT8 *base) {
    clear_old_moving_cards(prev, base);

    if (is_cards_moving(curr)) {
        render_moving_cards(curr, base);
    } else {
        clear_hand_cards(prev, base);
        render_hand(curr, base);
    }
}

/* card rendering */ 

static void render_card(const Card *card, UINT8 *base) {
    char rank[10];
    char suit[10];
    
    if (card->is_hidden) {
        plot_rectangle(base, card->position[0], card->position[1], 80, 55);
        plot_string(base, card->position[0] + 40, card->position[1], "HIDDEN");
        return;
    }

    strcpy(rank, card->rank);
    strcpy(suit, card->suit);

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

static void render_hand(const Hand *hand, UINT8 *base) {
    int i;

    if (hand->num_of_cards == 0)
        return;

    render_card(&hand->cards[0], base);
    for (i = 1; i < hand->num_of_cards; i++) {
        render_card(&hand->cards[i], base);
    }
}

static void render_moving_cards(const Hand *hand, UINT8 *base) {
    int i;
    for(i = 0; i < hand->num_of_cards; i++) {
        if(hand->cards[i].is_moving) {
            render_card(&hand->cards[i], base);
        }
    }
}

/* player rendering */

void render_player(const Player *player, UINT8 *base) {
    render_player_bank(player, base);
    render_player_value(player, base);
    render_player_bet(player, base);
    render_player_cards(player, base);
}

void render_player_bank(const Player *player, UINT8 *base) {
    char bank[20] = "Bank: ";
    char bank_int[10];
    int x;
    /* convert integers to strings */
    sprintf(bank_int, "%d", player->bank);
    /*append the numbers to the text */
    strcat(bank, bank_int); 
    plot_string(base, player->hand_position[0] + 105, player->hand_position[1], bank);
}

void render_player_value(const Player *player, UINT8 *base) {
    char value[20] = "Value: ";
    char value_int[10];
    sprintf(value_int, "%d", player->hand.value);
    strcat(value, value_int);
    plot_string(base, player->hand_position[0] - 20, player->hand_position[1], value);
}

void render_player_bet(const Player *player, UINT8 *base) {
    char bet[20] = "Bet: ";
    char bet_int[10];
    sprintf(bet_int, "%d", player->total_bet);
    strcat(bet, bet_int);
    plot_string(base, player->hand_position[0] - 40, player->hand_position[1], bet);
}

void render_player_cards(const Player *player, UINT8 *base) {
    render_hand(&player->hand, base);
}

/* dealer rendering */

void render_dealer(const Dealer *dealer, UINT8 *base) {
    render_dealer_value(dealer, base);
    render_dealer_cards(dealer, base);
}

void render_dealer_value(const Dealer *dealer, UINT8 *base) {
    char value[20] = "Value: ";
    char value_int[10];
    sprintf(value_int, "%d", dealer->hand.value);
    strcat(value, value_int);
    plot_string(base, dealer->position[0] - 20, dealer->position[1], value);
}

void render_dealer_cards(const Dealer *dealer, UINT8 *base) {
    if (dealer->hidden_card.is_hidden || dealer->hidden_card.is_moving) {
        render_card(&dealer->hidden_card, base);
    }
    render_hand(&dealer->hand, base);
}

/* timer and prompt rendering */

void render_timer(const Timer *timer, UINT8 *base) {
    render_timer_text(timer, base);
    render_timer_tick(timer, base);
}

void render_timer_text(const Timer *timer, UINT8 *base) {
    plot_string(base, 200, 280, "Seconds Left: ");
}

void render_timer_tick(const Timer *timer, UINT8 *base) {
    char seconds_int[10];

    /* convert integer seconds to string */
    sprintf(seconds_int, "%d", timer->seconds);
    plot_string(base, 200, 390, seconds_int);
}

void render_prompts(Model *game, UINT8 *base) {
    char prompt[100];
    int x;

    strcpy(prompt, "");  /* default to empty */

    if (game->player1_turn) {
        strcpy(prompt, "Press h to hit, s to stand.");
    }
    else if (game->dealer_turn) {
        strcpy(prompt, "Dealer is playing.");
    }
    else if (game->is_round_over) {
        /* Determine outcome for Player 1 */
        if (game->player1.hand.value > 21) {
            strcpy(prompt, "Player 1 busts. Dealer wins. Press c for new round.");
        }
        else if (game->dealer.hand.value > 21) {
            strcpy(prompt, "Dealer busts. Player 1 wins. Press c for new round.");
        }
        else if (game->player1.hand.value > game->dealer.hand.value) {
            strcpy(prompt, "Player 1 wins. Press c for new round.");
        }
        else if (game->player1.hand.value < game->dealer.hand.value) {
            strcpy(prompt, "Dealer wins. Press c for new round.");
        }
        else {
            strcpy(prompt, "Push. Press c for new round.");
        }
    }
    else if (game->player1_bet) {
        strcpy(prompt, "Press w to increase bet, s to decrease, c to confirm.");
    }

    /* center the text */
    x = (SCREEN_WIDTH / 2) - (strlen(prompt) * 8) / 2;

    plot_string(base, 150, x, prompt);
}

/* change detection */

int player_bank_changed(const Model *game, RenderSnapshot *snap) {
    return snap->player1.bank != game->player1.bank;
}

int player_value_changed(const Model *game, RenderSnapshot *snap) {
    return snap->player1.hand.value != game->player1.hand.value;
}

int player_bet_changed(const Model *game, RenderSnapshot *snap) {
    return snap->player1.total_bet != game->player1.total_bet;
}

int player_cards_changed(const Model *game, RenderSnapshot *snap) {
    return memcmp(&snap->player1.hand, &game->player1.hand, sizeof(Hand)) != 0;
}

int dealer_value_changed(const Model *game, RenderSnapshot *snap) {
    return snap->dealer.hand.value != game->dealer.hand.value;
}

int dealer_cards_changed(const Model *game, RenderSnapshot *snap) {
    return snap->dealer.hand.num_of_cards != game->dealer.hand.num_of_cards ||
           snap->dealer.hidden_card.is_hidden != game->dealer.hidden_card.is_hidden ||
           snap->dealer.hidden_card.is_moving != game->dealer.hidden_card.is_moving ||
           snap->dealer.hidden_card.position[0] != game->dealer.hidden_card.position[0] ||
           snap->dealer.hidden_card.position[1] != game->dealer.hidden_card.position[1];
}

int timer_changed(const Model *game, RenderSnapshot *snap) {
    return snap->timer.seconds != game->timer.seconds;
}

int prompts_changed(const Model *game, RenderSnapshot *snap) {
    return snap->player1_turn != game->player1_turn ||
           snap->dealer_turn != game->dealer_turn ||
           snap->is_round_over != game->is_round_over ||
           snap->player1_bet != game->player1_bet ||
           snap->player1.hand.value != game->player1.hand.value ||
           snap->dealer.hand.value != game->dealer.hand.value;
}

/* clearing functions */

void clear_player_bank(const Player *player, UINT8 *base) {
    clear_region(base, player->hand_position[0] + 105, player->hand_position[1], 8, 88);
}

void clear_player_value(const Player *player, UINT8 *base) {
    clear_region(base, player->hand_position[0] - 20, player->hand_position[1], 8, 72);
}

void clear_player_bet(const Player *player, UINT8 *base) {
    clear_region(base, player->hand_position[0] - 40, player->hand_position[1], 8, 80);
}

void clear_hand_cards(const Hand *hand, UINT8 *base) {
    int i;
    for (i = 0; i < hand->num_of_cards; i++) {
        clear_region(base, hand->cards[i].position[0], hand->cards[i].position[1], 80, 55);
    }
}

void clear_dealer_value(const Dealer *dealer, UINT8 *base) {
    clear_region(base, dealer->position[0] - 20, dealer->position[1], 8, 104);
}

void clear_timer_tick(const Timer *timer, UINT8 *base) {
    clear_region(base, 200, 390, 6, 16);
}

void clear_prompts(UINT8 *base) {
    clear_region(base, 100, 100, 8, 400);
}

static void clear_old_moving_cards(const Hand *old_hand, UINT8 *base) {
    int i;
    for (i = 0; i < old_hand->num_of_cards; i++) {
        if (old_hand->cards[i].is_moving) {
            clear_region(base, old_hand->cards[i].position[0], old_hand->cards[i].position[1], 80, 55);
        }
    }
}

static int is_cards_moving(const Hand *hand) {
    int i;
    for (i = 0; i < hand->num_of_cards; i++) {
        if (hand->cards[i].is_moving) {
            return 1;
        }
    }
    return 0;
}

int snapshot_has_moving_cards(const RenderSnapshot *snap) {
    int i, num;
    if(snap->player1.hand.num_of_cards > snap->dealer.hand.num_of_cards) {
        num = snap->player1.hand.num_of_cards;
    } else {
        num = snap->dealer.hand.num_of_cards;
    }

    for (i = 0; i < num; i++) {
        if(snap->player1.hand.cards[i].is_moving != 0 || snap->dealer.hand.cards[i].is_moving != 0 || snap->dealer.hidden_card.is_moving != 0) {
            return 1;
        }
    }
    return 0;
}