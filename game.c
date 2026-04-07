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
#include "time.h"
#include "splash.h"
#include <stdio.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 400
#define SCREEN_SIZE ((SCREEN_WIDTH * SCREEN_HEIGHT) / 8) /*This stuff should be in nother file*/
#define ALIGNMENT 256

Model model;
RenderSnapshot front_snapshot;
RenderSnapshot back_snapshot;

static UINT8 *original_screen = 0;  /*this stuff too*/
static UINT8 *front_buffer = 0;
static UINT8 *back_buffer = 0;
static UINT8 *raw_buffer1 = 0;
static UINT8 *raw_buffer2 = 0;

static void init_buffer();
static void swap_buffer();
static void clear_buffer();
static void test_swap();
static void restore_screen();

int main() {
    UINT32 timenow, timethen, timeElapsed;
    int in_prog, choice;
    char key;
    int action;
    Model *game;

    Cconws("\033f");

    timethen = get_time();
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

    draw_full_frame(game, front_buffer, &front_snapshot);
    draw_full_frame(game, back_buffer, &back_snapshot);

    timenow = get_time();
    Setscreen(-1, back_buffer, -1);
    wait_vbl(timenow);
    swap_buffer();

    timethen = get_time();

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

            if (in_prog || snapshot_has_moving_cards(&back_snapshot)) {
                draw_full_frame(game, back_buffer, &back_snapshot);
            } else {
                render_min(game, &back_snapshot, back_buffer);
            }

            Setscreen(-1, back_buffer, -1);
            wait_vbl(timenow);
            swap_buffer();
            swap_snapshots();

            timethen = timenow;
        }
    }
    restore_screen();
    clear_buffer();
    return 0;
}

static void draw_full_frame(const Model *game, UINT8 *buffer, RenderSnapshot *snap) {
    clear_screen(buffer);
    render(game, buffer);
    prompts(game, buffer);
    create_snapshot(game, snap);
}

/*below this stuff as well*/
static void init_buffer() {
    if (original_screen == 0) 
{
        original_screen = (UINT8 *)Physbase();
        
        raw_buffer1 = (UINT8 *)malloc(SCREEN_SIZE + (ALIGNMENT - 1));
        raw_buffer2 = (UINT8 *)malloc(SCREEN_SIZE + (ALIGNMENT - 1));
        /* malloc gives a random memory address and we need it 256 byte aligned */
        /* first we convert it to a pointer because we can't use arithmatic on it */
        /* then we add 255 because if we round the memory address down without it, it can skip the address by 255 bytes */
        /* so we guarantee that when rounding down we are within our allocated size, which is also why we give it 255 more bytes when allocating */
        /* and then you round off the last 2 bytes since that will make it always a multiple of 256 */
        front_buffer = (UINT8 *)(((long)raw_buffer1 + (ALIGNMENT - 1)) & 0xFFFFFF00);
        back_buffer = (UINT8 *)(((long)raw_buffer2 + (ALIGNMENT - 1)) & 0xFFFFFF00);
    }
}

static void swap_buffer() {
    UINT8 *temp;

    temp = front_buffer;
    front_buffer = back_buffer;
    back_buffer = temp;
}

static void swap_snapshots() {
    RenderSnapshot temp = front_snapshot;
    front_snapshot = back_snapshot;
    back_snapshot = temp;
}

/* unsure if necessary but here for now */
static void clear_buffer() {
    if ((raw_buffer1 || raw_buffer2) != 0) 
    {
        free(raw_buffer1);
        raw_buffer1 = 0;
        free(raw_buffer2);
        raw_buffer2 = 0;
    }

    front_buffer = 0;
    back_buffer = 0;
    original_screen = 0;
}

static void test_swap() {
    init_buffer();

    clear_screen(front_buffer);
    plot_string(front_buffer, 100, 100, "FRONT BUFFER");

    clear_screen(back_buffer);
    plot_string(back_buffer, 100, 140, "BACK BUFFER");

    /* start on original visible screen */
    Setscreen(-1, front_buffer, -1);
    Cnecin();

    /* flip to back buffer */
    swap_buffer();
    Setscreen(-1, front_buffer, -1);
    Cnecin();

    /* flip back to the other buffer */
    swap_buffer();
    Setscreen(-1, front_buffer, -1);
    Cnecin();

    /* restore original TOS screen before exit */
    restore_screen();
}

static void restore_screen() {
    Setscreen(-1, original_screen, -1);
}