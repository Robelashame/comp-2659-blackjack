#include "synch.h"

static int bezier_quad(int start, int control, int target, int t);
static void control_point_for_card(const Card *card, int *control_row, int *control_col);

int move_card(Model *game) {
    Card *card;
    Card *last;
    int t, control_row, control_col, i, is_dealer_card;

    card = 0;
    is_dealer_card = 0;

    /* check player 1 moving */
    if (game->player1.hand.num_of_cards > 0) {
        last = &game->player1.hand.cards[game->player1.hand.num_of_cards - 1];
        if (last->is_moving)
            card = last;
    }

    /* check player 2 moving */
    if (!card && game->player2.hand.num_of_cards > 0) {
        last = &game->player2.hand.cards[game->player2.hand.num_of_cards - 1];
        if (last->is_moving)
            card = last;
    }

    /* check dealer moving */
    if (!card) {
        if (game->dealer.hidden_card.is_moving) {
            card = &game->dealer.hidden_card;
        } else if (game->dealer.hand.num_of_cards > 0) {
            last = &game->dealer.hand.cards[game->dealer.hand.num_of_cards - 1];
            if (last->is_moving)
                card = last;
        }
    }

    if (!card) return 0;

    if (!card->is_moving) return 0;

    is_dealer_card = 0;

    for (i = 0; i < game->dealer.hand.num_of_cards; i++) {
        if (card == &game->dealer.hand.cards[i]) {
            is_dealer_card = 1;
            break;
        }
    }

    if (card == &game->dealer.hidden_card) {
        card->path_progress += 6;
    }
    else if (is_dealer_card) {
        card->path_progress += 6;
    }
    else {
        card->path_progress += 4; 
    }

    if (card->path_progress > 100)
        card->path_progress = 100;

    t = card->path_progress;

    control_point_for_card(card, &control_row, &control_col);

    card->position[0] = bezier_quad(card->start_position[0], control_row, card->target_position[0], t);
    card->position[1] = bezier_quad(card->start_position[1], control_col, card->target_position[1], t); 

    if (card->path_progress >= 100) {
        card->position[0] = card->target_position[0];
        card->position[1] = card->target_position[1];
        card->is_moving = FALSE;

        if (card != &game->dealer.hidden_card)
            card->is_hidden = FALSE;
        return 1;
    }

    return 1;
}

static void control_point_for_card(const Card *card, int *control_row, int *control_col) {
    int mid_row;
    int mid_col;

    mid_row = (card->start_position[0] + card->target_position[0]) / 2;
    mid_col = (card->start_position[1] + card->target_position[1]) / 2;

    if (card->is_hidden) {
        *control_row = mid_row + 20;
        *control_col = mid_col - 60;   
    }
    else if (card->target_position[0] < 120) {
        /* dealer: flatter, same general direction */
        *control_row = mid_row + 10;
        *control_col = mid_col - 120;
    } else {
        /* player: wider curve to avoid prompt/timer/ui */
        *control_row = mid_row + 180;
        *control_col = mid_col - 180;
    }
}

static int bezier_quad(int start, int control, int target, int t) {
    int inv_t;
    long value;

    inv_t = 100 - t;
    value = ((long)inv_t * inv_t * start +
             2L * inv_t * t * control +
             (long)t * t * target) / 10000L;
    return (int)value;
}

int move_toward(int current, int target, int step) {
    if (current < target) {
        current += step;
        if (current > target)
            current = target;
    }
    else if (current > target) {
        current -= step;
        if (current < target)
            current = target;
    }
    return current;
}

void update_timer(Model *game) {
    updateing_timer(&game->timer);
}
