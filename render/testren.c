#include <osbind.h>
#include "render.h"
#include <stdio.h>

Model game;

int main() {
    UINT8 *base = (UINT8 *)Physbase();

    printf("\033E");
    fflush(stdout);

    test_swap();

    /*
    initialize_game(&game);

    render(&game, base);

    Cnecin();
    */
    /*
	printf("\033f");
	fflush(stdout);
	Cnecin();
	clear_screen(base);
    initialize_game(&game);
    clear_screen(base);
    render_dealer(&game.dealer, base);
    render_player(&game.player1, base);
    if (game.is_there_player2 == TRUE)
        render_player(&game.player2, base);
    */

    return 0;
}