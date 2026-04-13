#include "input.h"
#include "ikbdlow.h"

/* Save old handler */
static void (*old_ikbd_isr)(void) = 0;

/* Interrupt routine */
void ikbd_isr(void)
{
    UINT8 b;

    b = ikbd_read_data_register();

    input_mouse_on_ikbd_byte(b);

    ikbd_ack_interrupt();
}

void input_mouse_init(void)
{
    long old_ssp = Super(0);

    old_ikbd_isr = install_ikbd_vector(ikbd_isr);

    ikbd_enable_rx_interrupt();

    Super(old_ssp);
}

void input_mouse_shutdown(void)
{
    long old_ssp = Super(0);

    ikbd_disable_rx_interrupt();
    restore_ikbd_vector(old_ikbd_isr);

    Super(old_ssp);
}