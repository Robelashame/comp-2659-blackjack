#include <osbind.h>
#include <stdlib.h> /* remove when moving db stuff */
#include "model.h"
#include "asynch.h"
#include "cond.h"
#include "synch.h"
#include "render.h"
#include "raster.h"
#include "input.h"
#include "TYPES.H"
#include "handle.h"
#include "splash.h"
#include "music.h"
#include "effects.h"
#include "double.h"
#include <stdio.h>
#include "vbl.h"

Model model;
RenderSnapshot front_snapshot;
RenderSnapshot back_snapshot;

static void draw_full_frame(const Model *game, UINT8 *buffer, RenderSnapshot *snap);
static void swap_snapshots();

int main() {
    int in_prog, choice;
    char key;
    Model *game;

    Cconws("\033f");

    in_prog = 0;
    game = &model;
    
    choice = splash_screen();

    if (choice == 2)
    {
        return 0; /* quit game */
    }

    initialize_game(game, choice);
    init_buffer();

    /*Draws first frame*/

    draw_full_frame(game, get_front_buffer(), &front_snapshot);
    draw_full_frame(game, get_back_buffer(), &back_snapshot);

    set_video_base((UINT16 *)get_back_buffer());
    swap_buffer();

    vbl_init();
    start_music();
    game->is_game_over = FALSE;

    while (!game->is_game_over)
    {
        if (has_input())
        {
            key = get_input();
            handle_input(game, key, in_prog);
        }

        if (vbl_consume_render_request())
        {
            update_model(game, &in_prog);
            render_min(game, &back_snapshot, get_back_buffer());

            set_video_base((UINT16 *)get_back_buffer());
            swap_buffer();
            swap_snapshots();
            update_music(vbl_get_ticks());
        }
    }
    vbl_shutdown();
    restore_screen();
    ending_screen();
    Cnecin();
    clear_buffer();
    return 0;
}

static void draw_full_frame(const Model *game, UINT8 *buffer, RenderSnapshot *snap) {
    clear_screen((UINT32 *)buffer);
    render(game, buffer);
    render_prompts(game, buffer);
    create_snapshot(game, snap);
}

static void swap_snapshots() {
    RenderSnapshot temp = front_snapshot;
    front_snapshot = back_snapshot;
    back_snapshot = temp;
}
