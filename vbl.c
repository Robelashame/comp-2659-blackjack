#include <osbind.h>
#include "vbl.h"

#define VBL_VECTOR_ADDRESS ((volatile long *)0x70L)

static void (*old_vbl_vector)(void) = 0;
static volatile UINT32 vbl_ticks = 0;
static volatile UINT8 render_request = 0;

extern void vbl_isr();

void vbl_init() {
    long old_ssp;

    old_ssp = Super(0);
    old_vbl_vector = (void (*)(void))*VBL_VECTOR_ADDRESS;
    *VBL_VECTOR_ADDRESS = (long)vbl_isr;
    vbl_ticks = 0;
    render_request = 1;
    Super(old_ssp);
}

void vbl_shutdown() {
    long old_ssp;

    old_ssp = Super(0);
    if (old_vbl_vector)
    {
        *VBL_VECTOR_ADDRESS = (long)old_vbl_vector;
    }
    Super(old_ssp);
}

void vbl_tick() {
    vbl_ticks++;
    render_request = 1;
}

int vbl_consume_render_request() {
    int requested;

    requested = (int)render_request;
    render_request = 0;

    return requested;
}

UINT32 vbl_get_ticks() {
    return vbl_ticks;
}
