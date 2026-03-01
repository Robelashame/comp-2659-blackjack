#include "testmodel.h"
#include <stdio.h>

test_two_player(Model *game) {
    int player_count;
    printf("Press 1 for player 2: ");
    scanf("%d", &player_count);
    if (player_count == 1) {
        game->is_there_player2 = true;
        printf("Game will have 2 players");
    } else {
        game->is_there_player2 = false;
        printf("Game will have 1 player");
    }
}