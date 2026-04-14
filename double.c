#include "double.h"
#include "render.h"
#include "raster.h"
#include <osbind.h>
#include <stdlib.h>

static UINT8 *original_screen = 0;
static UINT8 *front_buffer = 0;
static UINT8 *back_buffer = 0;
static UINT8 *raw_buffer1 = 0;
static UINT8 *raw_buffer2 = 0;

void init_buffer() {
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

void swap_buffer() {
    UINT8 *temp;

    temp = front_buffer;
    front_buffer = back_buffer;
    back_buffer = temp;
}

void clear_buffer() {
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

void test_swap() {
    init_buffer();

    clear_screen((UINT32 *)front_buffer);
    plot_string(front_buffer, 100, 100, "FRONT BUFFER");

    clear_screen((UINT32 *)back_buffer);
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

void restore_screen() {
    Setscreen(-1, original_screen, -1);
}

UINT8 *get_front_buffer() {
    return front_buffer;
}

UINT8 *get_back_buffer() {
    return back_buffer;
}