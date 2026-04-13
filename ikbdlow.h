#ifndef IKBDLOW_H
#define IKBDLOW_H

#include "types.h"

UINT8 ikbd_read_data_register(void);
void ikbd_ack_interrupt(void);

void (*install_ikbd_vector(void (*new_isr)(void)))(void);
void restore_ikbd_vector(void (*old_isr)(void));

void ikbd_enable_rx_interrupt(void);
void ikbd_disable_rx_interrupt(void);

#endif