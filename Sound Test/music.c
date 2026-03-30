#include "types.h"
#include <stdlib.h>
#include <osbind.h>
#include "music.h"

typedef struct
{
    UINT16 tone;
    UINT16 duration;
} Note;

const Note song[] =
{
    {0x200, 30},
    {0x180, 30},
    {0x150, 30},
    {0x100, 60},
    {0, 30}
};

static UINT32 last_time = 0;
static int current_note = 0;

void start_music()
{
    int current_note = 0;
    UINT32 last_time = 0;

    set_volume(8, 10);
    enable_channel(0, 1, 0);
}

void update_music(UINT32 time_elapsed)
{
    if(time_elapsed - last_time >= song[current_note].duration)
    {
        UINT16 tone = song[current_note].tone;

        if(tone == 0)
        {
            set_volume(8, 0);
        }
        else
        {
            set_tone(0, tone & 0xFF);
            set_tone(1, tone >> 8);
            set_volume(8, 10);
        }

        last_time = time_elapsed;

        current_note++;

        if(current_note >= 5)
        {
            current_note = 0;
        }
    }
}


