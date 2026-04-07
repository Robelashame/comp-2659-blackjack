#ifndef MUSIC_H
#define MUSIC_H

#include "types.h"
#include "psg.h"

/* Starts the music playing. */
void start_music();

/* Updates the music playing based on time elapsed. */
void update_music(UINT32 time_elapsed);

#endif
