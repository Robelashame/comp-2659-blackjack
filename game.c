#include "objects/model.h"
#include "objects/async.h"
#include "objects/cond.h"
#include "objects/sync.h"
#include "render/render.h"
#include "raster/raster.h"
#include "input.h"
#include "TYPES.H"
#include "handle.h"

Model model;

int main() {
char key;
int action;
Model *game = &model;

initialize_game(game, 0);
render(game);
game->is_game_over = FALSE;

while (!game->is_game_over)
{
    if (has_input) {
        key = get_input;
        action = handle_input(game, key);
    }
        

    if (clock ticked)
        process sync events
        process condition events
        render next frame
}
}