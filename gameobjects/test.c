#include "testmo.h"

int main() {
    Model game;
    test_game_start(&game);
    test_hit(&game);
    test_win_or_lose(&game);
    return 0;
}