#include "handle.h"
#include <string.h>

void handle_input(Model *game, char cin, int in_prog)
{

    if (in_prog) /*ends if card is moving*/
        return;

    if ((game->player1_turn || game->player2_turn))
    {
        if (cin == 'h')
        {
            hit(game);
        }
        else if (cin == 's')
        {
            stand(game);
        }
    }

    if (!(game->dealer_turn || game->player1_turn || game->player2_turn) && !(game->is_round_over))
    {
        if (game->player1.bank == 0) {
            quit(game);
        }
        else if (cin == 'w')
        {
            increase_bet(game);
        }
        else if (cin == 's')
        {
            decrease_bet(game);
        }
        else if (cin == 'c')
        {
            bet_confirmed(game);
        }
    }

    if (cin == 'q')
    {
        quit(game);
    }
}

void update_model(Model *game, int *in_prog)
{
    *in_prog = move_card(game);
    if (!(*in_prog))
    {
        if (game->dealing_start_cards)
            give_start_cards(game);

        if (game->player1_turn || game->player2_turn)
            player_bj_or_bust(game);

        if (game->dealer_turn)
            dealer_draws(game);

        if (game->is_round_over && !game->outcome_applied)
        {
            outcome(game, 1);
            if (game->is_there_player2)
                outcome(game, 2);
            game->outcome_applied = TRUE;
        }
    }
}

void dismiss_outcome(Model *game) {
    if (has_input()) {
        char key = get_input();
        if (key == 'c') {
            remove_everyones_cards(game);
            game->is_round_over = FALSE;
            game->outcome_applied = FALSE
        }
    }
}
