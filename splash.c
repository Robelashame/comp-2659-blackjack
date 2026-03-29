#include "splash.h"
#include "input.h"
#include "raster.h"
#include "bmaps.h"
#include <osbind.h>

#define KEY_ONE '1'
#define KEY_TWO '2'
#define KEY_Q 'q'

int splash_screen() 
{
    int choice;
    int running;

    choice = 0;
    running = 1;

    while (running) 
    {
        draw splash screen
        draw title
        draw buttons

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
                return choice; /* quit */
            }
        }
    }
    return choice;
}

static void draw_splash_screen(UINT8 *base)
{
    clear_screen(base);

	/* title */
    plot_16bit_bitmap(base, 87, 184-8, heart, 16);
    plot_16bit_bitmap(base, 87, 237-8, diamond, 10);
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