#include "render.h"

Model model;

int main() {

    void *base = Physbase();

    Model *game = &model;
    initialize_game(game);
    render_card(game->dealer.hidden_card, base);
    render_hand(game->dealer.hand, base);
    

}