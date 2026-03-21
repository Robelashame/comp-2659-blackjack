#include "synch.h"

int move_card(Model *game) {
    Card *card;
    int num_of_cards;

    if (game->player1_turn) {
        num_of_cards = game->player1.hand.num_of_cards;
        card = &game->player1.hand.cards[num_of_cards - 1];
    } else if (game->player2_turn) {
        num_of_cards = game->player2.hand.num_of_cards;
        card = &game->player2.hand.cards[num_of_cards - 1];
    } else if (game->dealer_turn) {
        if (game->dealer.hidden_card.is_moving) {
            card = &game->dealer.hidden_card;
        } else {
            num_of_cards = game->dealer.hand.num_of_cards;
            card = &game->dealer.hand.cards[num_of_cards - 1];
        }
    }

    if (card->is_moving) {
        card->position[1] = move_toward(card->position[1], card->target_position[1], 2);
        card->position[0] = move_toward(card->position[0], card->target_position[0], 2);

        if (card->position[1] == card->target_position[1] && card->position[0] == card->target_position[0]) {
            card->is_moving = 0;
            if (!(card == &game->dealer.hidden_card))
                card->is_hidden = FALSE;
            return 0;
        }
    }
    return 1;
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