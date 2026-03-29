#ifndef PSG_H
#define PSG_H

#include "types.h"

/* Writes the given byte value (0-255) to the given PSG register (0-15). */
void write_psg(int reg, UINT8 val);

/* For testing purposes */
UINT8 read_psg(int reg);

/* Loads the tone registers (coarse and fine) for the given channel (0=A, 1=B, 2=C) with the
given 12-bit tuning. */
void set_tone(int channel, int tuning);

/* Loads the volume register for the given channel. */
void set_volume(int channel, int volume);

/* Turns the given channel’s tone/noise signals on/off (0=off, 1=on). */
void enable_channel(int channel, int tone_on, int noise_on);

/* Stops all PSG sound production. */
void stop_sound();

#endif
