#include "time.h"
#include "types.h"
#include <stdlib.h>
#include <osbind.h>
#include "effects.h"

static int woosh_active = 0;
static int woosh_noise = 25;
static UINT32 woosh_timing = 0;

static int hit_active = 0;
static int hit_noise = 20;
static UINT32 hit_timing = 0;

void play_effect_woosh()
{
    enable_channel(0, 0, 1);
    write_psg(8, 15);

    woosh_active = 1;
    woosh_noise = 20;
    woosh_timing = get_time();

    set_envelope(8, 1600);
}


void play_effect_hit()
{
    set_noise(20);

    set_envelope(0, 200);

    enable_channel(0, 0, 1);

    write_psg(8, 15);
}

void update_effects(UINT32 time_elapsed)
{
    if(woosh_active)
    {
        if(time_elapsed - woosh_timing > 40)
        {
            woosh_timing = time_elapsed;

            set_noise(woosh_noise);
            woosh_noise--;

            if(woosh_noise <= 2)
            {
                woosh_active = 0;
            }
        }
    }
}