#include "types.h"
#include <stdlib.h>
#include <osbind.h>
#include "effects.h"


void play_effect_woosh()
{
    int i;

    enable_channel(0, 0, 1);
    write_psg(8, 15);

    for(i = 20; i > 2; i--)
    {
        set_noise(i);
    }

    set_envelope(8, 1500);
}


void play_effect_hit()
{
    set_noise(20);

    set_envelope(0, 200);

    enable_channel(0, 0, 1);

    write_psg(8, 15);
}