#include "input.h"
#include "raster.h"

#define IKBD_VECTOR 70

volatile int mouse_x = 320;
volatile int mouse_y = 200;

volatile int mouse_left = 0;
volatile int mouse_right = 0;

volatile int mouse_state = 0;

volatile signed char mouse_dx;
volatile signed char mouse_dy;

typedef void (*Vector)();

Vector install_vector(int num, Vector vector);

void ikbd_isr(void);

void ikbd_init()
{
    Vector orig_ikbd;

    orig_ikbd = install_vector(IKBD_VECTOR, ikbd_isr);
}

void ikbd_handler(unsigned char data)
{
    switch(mouse_state)
    {
        case 0:
            mouse_left  = (data & 0x02) != 0;
            mouse_right = (data & 0x01) != 0;
            mouse_state = 1;
            break;

        case 1:
            mouse_dx = (signed char)data;
            mouse_state = 2;
            break;

        case 2:
            mouse_dy = (signed char)data;

            mouse_x += mouse_dx;
            mouse_y -= mouse_dy;

            mouse_x = clamp(mouse_x, 0, 639);
            mouse_y = clamp(mouse_y, 0, 419);

            mouse_state = 0;
            break;
    }
}

/* Helper function for clamping, idk if needed.*/
static int clamp(int value, int low, int high)
{
    if (value < low) return low;
    if (value > high) return high;
    return value;
}


static Vector install_vector(int num, Vector vector)
{
    Vector orig;
    Vector *vectp = (Vector *)((long)num << 2);
    long old_ssp = Super(0);
    orig = *vectp;
    *vectp = vector;
    Super(old_ssp);
    return orig;
}


int has_input()
{
    return Cconis() != 0;
}

char get_input()
{
    char in;
    in = Cconin();
    return (char)in;
}

void update_mouse(MouseState *mouse)
{
    int x;
    int y;
    UINT8 b;

    if (!mouse) return;

    x = mouse_x;
    y = mouse_y;
    b = mouse_left;

    mouse->x = x;
    mouse->y = y;
    mouse->buttons = b;
    /*mouse->pressed = (UINT8)((~s_prev_buttons) & b);
    mouse->released = (UINT8)(s_prev_buttons & (~b));
    mouse->moved = (UINT8)((x != s_prev_x) || (y != s_prev_y));
    */

    /*s_prev_buttons = b;
    s_prev_x = x;
    s_prev_y = y;
    */
}