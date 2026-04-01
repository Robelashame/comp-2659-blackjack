#ifndef EFFECTS_H
#define EFFECTS_H

#include "types.h"
#include "psg.h"

/* Plays woosh sound effect. */
void play_effect_woosh();

/* Plays hitting sound effect. */
void play_effect_hit();

/* Updates all sound effects according to time elapsed. */
void update_effects(UINT32 time_elapsed);

#endif
