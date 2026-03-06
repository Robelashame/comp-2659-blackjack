#include "render.h"

Model model;

int main() {

    void *base = Physbase();

    Model *game = &model;
    initialize_game(game);
    render_dealer(game->dealer, base);
    render_player(game->player1, base);
    if (game->is_there_player2 == TRUE)
        render_player(game->player2, base);
    return 0;
}