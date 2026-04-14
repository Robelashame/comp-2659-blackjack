#include "types.h"
#include <stdlib.h>
#include <osbind.h>
#include "effects.h"

static int woosh_active = 0;
static int woosh_noise = 10;
static UINT32 woosh_timing = 0;

static int hit_active = 0;
static int hit_noise = 16;
static UINT32 hit_timing = 0;

void play_effect_woosh()
{
    set_noise(31);

    write_psg(12, hit_noise);
    write_psg(13, 0);

    enable_channel(0, 0, 1);
    

    woosh_active = 1;
    woosh_noise = 6;
    woosh_timing = get_time();
    
    write_psg(8, 15);
}


void play_effect_hit()
{
    set_noise(15);

    enable_channel(0, 1, 0);

    write_psg(0, 0x30);

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
            woosh_noise += 5;
            

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
            hit_noise++;
            
            write_psg(0, hit_noise);

            if(hit_noise >= 192)
            {
                hit_active = 0;
                enable_channel(0, 0, 0);
            }
        }
    }
}