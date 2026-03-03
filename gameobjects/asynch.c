#include "asynch.h"

void hit(Model *game) {
    if (game->player1_turn == true) {
        Card dealt_card = deal(&game->deck);
        add_card(&game->player1.hand, &dealt_card);
    }
    else if (game->player2_turn == true) {
        Card dealt_card = deal(&game->deck);
        add_card(&game->player2.hand, &dealt_card);
    }
}

void stand(Model *game) {
    if (game->player1_turn == true && game->is_there_player2 == true) {
        game->player1_turn = false;
        game->player2_turn = true;
    }

    else if (game->player2_turn == true) {
        game->player2_turn = false;
        game->dealer_turn = true;
    }

    else if (game->player1_turn == true && game->is_there_player2 == false) {
        game->player1_turn = false;
        game->dealer_turn = true;
    }
}

void increase_bet(Model *model) {
    if (model->player1_turn)
    {
        if (model->player1.total_bet + 50 <= model->player1.bank)
            model->player1.total_bet += 50;
    }
    else if (model->player2_turn)
    {
        if (model->player2.total_bet + 50 <= model->player2.bank)
            model->player2.total_bet += 50;
    }
}

void decrease_bet(Model *model) {
    if (model->player1_turn)
    {
        if (model->player1.total_bet - 50 >= 0)
            model->player1.total_bet -= 50;
    }
    else if (model->player2_turn)
    {
        if (model->player2.total_bet - 50 >= 0)
            model->player2.total_bet -= 50;
    }
}

void bet_confirmed(Model *model) {
    if (model->player1_turn)
        model->player1.bank -= model->player1.total_bet;

    else if (model->player2_turn)
        model->player2.bank -= model->player2.total_bet;
}

void quit(Model *game) {
    game->is_game_over = true;
}

