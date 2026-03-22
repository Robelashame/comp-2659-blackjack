#include "synch.h"

int move_card(Model *game) {
    Card *card;
    Card *last;

    card = 0;

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


    if (!card)
        return 0;

    if (card->is_moving) {
        card->position[1] = move_toward(card->position[1], card->target_position[1], 40);
        card->position[0] = move_toward(card->position[0], card->target_position[0], 40);

        if (card->position[1] == card->target_position[1] &&
            card->position[0] == card->target_position[0]) {

            card->is_moving = 0;

            if (card != &game->dealer.hidden_card)
                card->is_hidden = FALSE;

            return 0; /*Not in prog*/
        }
    }

    return 1; /*In prog*/
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