#include "types.h"
#include <stdlib.h>
#include <osbind.h>
#include "effects.h"

static int woosh_active = 0;
static int woosh_noise = 10;
static UINT32 woosh_timing = 0;

static int hit_active = 0;
static int hit_noise = 20;
static UINT32 hit_timing = 0;

void play_effect_woosh()
{
    set_noise(6);
    set_envelope(10, 3000);
    enable_channel(0, 0, 1);
    

    woosh_active = 1;
    woosh_noise = 6;
    woosh_timing = get_time();
    
    write_psg(8, 15);
}


void play_effect_hit()
{
    set_noise(15);

    set_envelope(0, 2000);

    enable_channel(0, 0, 1);

    hit_active = 1;
    hit_noise = 6;
    hit_timing = get_time();

    write_psg(8, 15);
}

void update_effects(UINT32 time_elapsed)
{
    if(woosh_active)
    {
        if(time_elapsed - woosh_timing > 4)
        {
            woosh_timing = time_elapsed;
            woosh_noise--;
            set_noise(woosh_noise);
            

            if(woosh_noise <= 2)
            {
                woosh_active = 0;
                set_noise(0);
                enable_channel(0, 0, 0);
            }
        }
    }

    if(hit_active)
    {
        if(time_elapsed - hit_timing > 1)
        {
            hit_timing = time_elapsed;
            hit_noise--;
            set_noise(woosh_noise);
            

            if(hit_noise <= 2)
            {
                hit_active = 0;
                set_noise(0);
                enable_channel(0, 0, 0);
            }
        }
    }
}