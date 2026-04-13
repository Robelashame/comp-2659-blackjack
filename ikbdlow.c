#include "ikbdlow.h"

/* TODO: replace with real Atari ST hardware access */
UINT8 ikbd_read_data_register(void) { return 0; }
void ikbd_ack_interrupt(void) { }

void (*install_ikbd_vector(void (*new_isr)(void)))(void)
{
    (void)new_isr;
    return (void (*)(void))0;
}

void restore_ikbd_vector(void (*old_isr)(void))
{
    (void)old_isr;
}

void ikbd_enable_rx_interrupt(void) { }
void ikbd_disable_rx_interrupt(void) { }