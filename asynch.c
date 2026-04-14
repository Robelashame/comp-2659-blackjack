#include "asynch.h"

void hit(Model *game) {

    Card dealt_card;
    dealt_card = deal(&game->deck);
    play_effect_hit();
    if (game->player1_turn == TRUE) {
        add_card(&game->player1.hand, &dealt_card);
    }
    else if (game->player2_turn == TRUE) {
        add_card(&game->player2.hand, &dealt_card);
    }
}

void stand(Model *game) {
    player_turn_ends(game);
}

void increase_bet(Model *model) {
    if (model->player1_bet)
    {
        if (model->player1.total_bet + 50 <= model->player1.bank)
            model->player1.total_bet += 50;
        else if (model->player1.total_bet + 50 > model->player1.bank)
            model->player1.total_bet = model->player1.bank;
    }
    else if (model->player2_bet)
    {
        if (model->player2.total_bet + 50 <= model->player2.bank)
            model->player2.total_bet += 50;
        else if (model->player2.total_bet + 50 > model->player2.bank)
            model->player2.total_bet = model->player2.bank;
    }
}

void decrease_bet(Model *model) {
    if (model->player1_bet)
    {
        if (model->player1.total_bet - 50 >= 0)
            model->player1.total_bet -= 50;
        else if (model->player1.total_bet - 50 < 0)
            model->player1.total_bet = 0;
    }
    else if (model->player2_bet)
    {
        if (model->player2.total_bet - 50 >= 0)
            model->player2.total_bet -= 50;
        else if (model->player2.total_bet - 50 < 0)
            model->player2.total_bet = 0;
    }
}

void bet_confirmed(Model *model) {
    if (model->player1_bet) {
        model->player1.bank -= model->player1.total_bet;
        if (model->is_there_player2) {
            model->player1_bet = 0;
            model->player2_bet = 1;
        } else
            new_round(model);
    } else if (model->player2_bet) {
        model->player2.bank -= model->player2.total_bet;
        new_round(model);
    }
}

void quit(Model *game) {
    game->is_game_over = TRUE;
}
