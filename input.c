#include "input.h"

/* Shared states written by ISR. */
volatile int g_mouse_x = 320;
volatile int g_mouse_y = 200;
volatile UINT8 g_mouse_buttons = 0;

/* Parser state for incoming 3-byte packets. */
static volatile UINT8 s_phase = 0;   
static volatile signed char s_dx = 0;
static volatile UINT8 s_hdr = 0;

/* Last copy of states. */
static UINT8 s_prev_buttons = 0;
static int s_prev_x = 320, s_prev_y = 200;

/* Call for ISR. */
void input_mouse_on_ikbd_byte(UINT8 b);

/* Helper function for clamping, idk if needed.*/
static int clamp(int value, int low, int high)
{
    if (value < low) return low;
    if (value > high) return high;
    return value;
}

int has_input() {
    return Cconis() != 0;
}

char get_input() {
    char in;
    in = Cconin();
    return (char)in;
}

void input_mouse_on_ikbd_byte(UINT8 b)
{
    if (s_phase == 0)
    {
        if ((b & 0xF8) == 0xF8)
        {
            /* 111110LR mouse header */
            s_hdr = b;
            s_phase = 1;
            return;
        }
        return;
    }

    if (s_phase == 1) {
        s_dx = (signed char)b;
        s_phase = 2;
        return;
    }

    /* s_phase == 2 : got dy */
    {
        int dx = (int)s_dx;
        int dy = (int)((signed char)b);

        g_mouse_buttons = (UINT8)(s_hdr & 0x03);
        g_mouse_x = clamp(g_mouse_x + dx, 0, 639);
        g_mouse_y = clamp(g_mouse_y + dy, 0, 399);

        s_phase = 0;
    }
}

void update_mouse(MouseState *mouse)
{
    long old_ssp;
    int x, y;
    UINT8 b;

    if (!mouse) return;

    old_ssp = Super(0);
    x = g_mouse_x;
    y = g_mouse_y;
    b = g_mouse_buttons;
    Super(old_ssp);

    mouse->x = x;
    mouse->y = y;
    mouse->buttons = b;
    mouse->pressed = (UINT8)((~s_prev_buttons) & b);
    mouse->released = (UINT8)(s_prev_buttons & (~b));
    mouse->moved = (UINT8)((x != s_prev_x) || (y != s_prev_y));

    s_prev_buttons = b;
    s_prev_x = x;
    s_prev_y = y;
}