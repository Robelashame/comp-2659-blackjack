#include <osbind.h>
#include "model.h"
#include "async.h"
#include "cond.h"
#include "sync.h"
#include "render.h"
#include "raster.h"
#include "input.h"
#include "TYPES.H"
#include "handle.h"
#include "gettime.h"

Model model;

int main() {

    void *base = Physbase();

    UINT32 timenow, timethen, timeElapsed;
    int in_prog;
    in_prog = 0;
    timethen = 0;
    char key;
    int action;
    Model *game = &model;

    initialize_game(game, 0);
    render(game);
    game->is_game_over = FALSE;

    while (!game->is_game_over)
    {
        if (has_input())
        {
            key = get_input();
            handle_input(game, key, in_prog);
        }

        timenow = get_time();
        timeElapsed = timenow - timethen;

        if (timeElapsed > 0)
        {
            update_model(game, &in_prog);
            dismiss_outcome(game);
            render(game, base);
            timethen = timenow;
        }
    }
}