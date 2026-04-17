#include "splash.h"
#include "input.h"
#include "raster.h"
#include "bmaps.h"
#include "types.h"
#include "music.h"
#include "time.h"
#include <osbind.h>
#include <stdio.h>

#define KEY_ONE '1'
#define KEY_TWO '2'
#define KEY_Q 'q'

#define CURSOR_W 3
#define CURSOR_H 10

static UINT8 cursor_save[CURSOR_W * CURSOR_H];

#define LEFT_BUTTON  1
#define RIGHT_BUTTON 2

static int prev_buttons = 0;

void restore_cursor(UINT8 *base);

void save_cursor(UINT8 *base, int x, int y);

static void draw_mouse_debug(UINT8 *base, const MouseState *ms);
static int prev_x = -1;
static int prev_y = -1;

int splash_screen() 
{
    UINT8 *base;
    UINT32 timenow, timethen, timeElapsed;
    MouseState ms;
    int choice;
    int running;

    choice = 0;
    running = 1;

    base = (UINT8 *)Physbase();

    ikbd_init();
    clear_screen(base);
    draw_splash_screen(base);

    timethen = get_time();
    timenow = get_time();
    start_music();

    while (running) 
    {
        char buffer[40];
        int pressed, released;

        update_mouse(&ms);

        pressed  = ms.buttons & ~prev_buttons;
        released = prev_buttons & ~ms.buttons;

        if(pressed & LEFT_BUTTON)
        {
            plot_filled_rect(base, ms.y, ms.x, 10, 10);
        }

        if(released & LEFT_BUTTON)
        {
            if(point_in_rect(ms.x, ms.y, 200, 220, 110, 20))
            {
                ikbd_uninstall();
                return 0;
            }

            if(point_in_rect(ms.x, ms.y, 340, 220, 110, 20))
            {
                ikbd_uninstall();
                return 1; 
            }

            if(point_in_rect(ms.x, ms.y, 269, 270, 110, 20))
            {
                ikbd_uninstall();
                return 2; 
            }
        }

        /*
        if(prev_x > ms.y || prev_y > ms.x || prev_x < ms.y || prev_y < ms.x)
        {
            clear_region(base, prev_x, prev_y, 10, 10);
        }
        */

        update_music(timenow);
        timenow = get_time();
        timeElapsed = timenow - timethen;
        
        
        if(prev_x != ms.y || prev_y != ms.x)
        {
            restore_cursor(base);

            save_cursor(base, ms.y, ms.x);

            plot_square(base, ms.y, ms.x, 10);
        }
        prev_x = ms.y;
        prev_y = ms.x;
        prev_buttons = ms.buttons;
        

        if (has_input()) 
        {
            char input;
            input = get_input();

            if (input == KEY_ONE) 
            {
                return 0; /* single player mode */
            }
            else if (input == KEY_TWO)
            {
                return 1; /* two player mode */
            }
            else if (input == KEY_Q)
            {
                return 2; /* quit */
            }
        }

        if(timeElapsed > 0) {
            timethen = timenow;
        }
    }
}


static void draw_splash_screen(UINT8 *base)
{
	/* title */
    plot_16bit_bitmap(base, 87, 184-8, heart, 16);
    plot_16bit_bitmap(base, 87, 237-8, diamond, 16);
    plot_16bit_bitmap(base, 87, 387-8, heart, 16);
    plot_16bit_bitmap(base, 87, 440-8, spade, 16);
    plot_string(base, 90, 290-8, "BlackJack");

    /* buttons */
    plot_rectangle(base, 220, 200-8, 20, 110);
    plot_string(base, 226, 205-8, "Single Player");

    plot_rectangle(base, 220, 340-8, 20, 110);
    plot_string(base, 226, 354-8, "Two Players");

    plot_rectangle(base, 270, 269-8, 20, 110);
    plot_string(base, 276, 309-8, "Quit");
}

void ending_screen(UINT8 *base)
{
    clear_screen(base);
}

void save_cursor(UINT8 *base, int x, int y)
{
    int row;
    UINT8 *src;

    src = base + (x * 80) + (y >> 3);

    for(row = 0; row < CURSOR_H; row++)
    {
        cursor_save[row * CURSOR_W] = src[0];
        cursor_save[row * CURSOR_W + 1] = src[1];
        cursor_save[row * CURSOR_W + 2] = src[2];

        src += 80;
    }
}

void restore_cursor(UINT8 *base)
{
    int row;
    UINT8 *dst;

    if(prev_x < 0) return;

    dst = base + (prev_x * 80) + (prev_y >> 3);

    for(row = 0; row < CURSOR_H; row++)
    {
        dst[0] = cursor_save[row * CURSOR_W];
        dst[1] = cursor_save[row * CURSOR_W + 1];
        dst[2] = cursor_save[row * CURSOR_W + 2];

        dst += 80;
    }
}

int point_in_rect(int x, int y, int rect_x, int rect_y, int w, int h)
{
    return (x >= rect_x && x < rect_x + w && y >= rect_y && y < rect_y + h);
}