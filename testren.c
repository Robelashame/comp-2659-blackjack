#include <osbind.h>
#include "render.h"
#include <stdio.h>

Model game;

int main() {

    void *base = Physbase();

	printf("\033f");
	fflush(stdout);
	printf("Clear Screen");
	Cnecin();
	clear_screen(base);
    initialize_game(&game);
    render_dealer(&game.dealer, base);
    render_player(&game.player1, base);
    if (game.is_there_player2 == TRUE)
        render_player(&game.player2, base);
    return 0;
}