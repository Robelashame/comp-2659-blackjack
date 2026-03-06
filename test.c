#include "testmo.h"

Model game; /* to fix stack issue, made global*/

int main() {
    test_game_start(&game);
    test_hit(&game);
    test_win_or_lose(&game);
    return 0;
}