#include "handle.h"
#include "render.h"
#include <string.h>


void handle_input(Model *game, char cin, int in_prog)
{

    if (game->is_round_over)
    {
        if (cin == 'c')
        {
            remove_everyones_cards(game);
            game->is_round_over = FALSE;
            game->outcome_applied = FALSE;
            game->player1_bet = TRUE;
            game->player2_bet = FALSE;
            game->dealer.hidden_card.position[0] = -90;
        }
        else if (cin == 'q')
        {
            quit(game);
        }
        return;
    }


    if (in_prog) /*ends if card is moving*/
        return;

    if ((game->player1_turn || game->player2_turn))
    {
        if (cin == 'h')
        {
            hit(game);
            reset_time(game);
            startup_timer(game);
        }
        else if (cin == 's')
        {
            stand(game);
            stop_time(game);
            reset_time(game);
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
            if (game->player1.total_bet == 0)
                return;
            bet_confirmed(game);
            startup_timer(game);
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
        update_timer(game);

        if (timer_expired(&game->timer)) {
            stand(game);
        }

        if (game->dealing_start_cards)
            give_start_cards(game);

        if (game->player1_turn || game->player2_turn)
            player_bj_or_bust(game);

        if (game->dealer_turn) {
            dealer_draws(game);
            reset_time(game);
        }
        if (game->is_round_over && !game->outcome_applied)
        {
            outcome(game, 1);
            if (game->is_there_player2)
                outcome(game, 2);
            game->outcome_applied = TRUE;
        }
    }
}

void prompts(Model *game, UINT8 *base) {
    char prompt[100];
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
        if (game->player1.bank == 0) {
            strcpy(prompt, "You have no more money. You lose.");
        }
        else
            strcpy(prompt, "Press w to increase bet, s to decrease, c to confirm.");
    }

    plot_string(base, 150, 200, prompt);
}
