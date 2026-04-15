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
#include "vbl.h"



#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 400
#define SCREEN_SIZE ((SCREEN_WIDTH * SCREEN_HEIGHT) / 8) /*This stuff should be in nother file*/
#define ALIGNMENT 256

Model model;

static UINT8 *original_screen = 0;  /*this stuff too*/
static UINT8 *front_buffer = 0;
static UINT8 *back_buffer = 0;
static UINT8 *raw_buffer = 0;

static void init_buffer();
static void swap_buffer();
static void clear_buffer();
static void test_swap();
static void restore_screen();
static void set_video_base_safe(UINT16 *base);
static UINT16 *get_video_base_safe(void);

int main() {
    int in_prog;
    char key;
    Model *game;

    in_prog = 0;

    game = &model;

    initialize_game(game, 0);
    init_buffer();

    /*Draws first frame*/
    clear_screen(back_buffer);
    render(game, back_buffer);
    set_video_base_safe((UINT16 *)back_buffer);
    swap_buffer();

    vbl_init();

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
            clear_screen(back_buffer);
            prompts(game, back_buffer);
            render(game, back_buffer);
            set_video_base_safe((UINT16 *)back_buffer);
            swap_buffer();
        }
    }

    vbl_shutdown();
    restore_screen();
    clear_buffer();
    return 0;
}

/*below this stuff aswell*/
static void init_buffer() {
    if (original_screen == 0) 
{
        original_screen = (UINT8 *)get_video_base_safe();
        front_buffer = original_screen;
        raw_buffer = (UINT8 *)malloc(SCREEN_SIZE + (ALIGNMENT - 1));
        /* malloc gives a random memory address and we need it 256 byte aligned */
        /* first we convert it to a pointer because we can't use arithmatic on it */
        /* then we add 255 because if we round the memory address down without it, it can skip the address by 255 bytes */
        /* so we guarantee that when rounding down we are within our allocated size, which is also why we give it 255 more bytes when allocating */
        /* and then you round off the last 2 bytes since that will make it always a multiple of 256 */
        back_buffer = (UINT8 *)(((long)raw_buffer + (ALIGNMENT - 1)) & 0xFFFFFF00);
    }
}

static void swap_buffer() {
    UINT8 *temp;

    temp = front_buffer;
    front_buffer = back_buffer;
    back_buffer = temp;
}

/* unsure if necessary but here for now */
static void clear_buffer() {
    if (raw_buffer != 0) 
    {
        free(raw_buffer);
        raw_buffer = 0;
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
    set_video_base_safe((UINT16 *)front_buffer);
    Cnecin();

    /* flip to back buffer */
    swap_buffer();
    set_video_base_safe((UINT16 *)front_buffer);
    Cnecin();

    /* flip back to the other buffer */
    swap_buffer();
    set_video_base_safe((UINT16 *)front_buffer);
    Cnecin();

    /* restore original TOS screen before exit */
    vbl_shutdown();
    restore_screen();
}

static void restore_screen() {
    set_video_base_safe((UINT16 *)original_screen);
}

static void set_video_base_safe(UINT16 *base) {
    long old_ssp;

    old_ssp = Super(0);
    set_video_base(base);
    Super(old_ssp);
}

static UINT16 *get_video_base_safe(void) {
    long old_ssp;
    UINT16 *base;

    old_ssp = Super(0);
    base = get_video_base();
    Super(old_ssp);
    return base;
}
