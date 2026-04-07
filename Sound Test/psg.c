#include "types.h"
#include <stdlib.h>
#include <osbind.h>
#include "psg.h"

#define PSG_REG_SELECT  ((volatile unsigned char *)0xFF8800)
#define PSG_REG_WRITE   ((volatile unsigned char *)0xFF8802)

#define MIXER_REG 7

void write_psg(int reg, UINT8 val)
{
    long old_ssp;
    if(reg < 0 || reg > 15) return;

    long old_ssp = Super(0);

    *PSG_REG_SELECT = reg;
    *PSG_REG_WRITE = val;

    Super(old_ssp);
}


UINT8 read_psg(int reg)
{
    UINT8 psg_val;

    long old_ssp = Super(0);

    *PSG_REG_SELECT = reg;
    psg_val = *PSG_REG_WRITE;

    Super(old_ssp);

    return psg_val;
}


void set_tone(int channel, int tuning)
{
    if(channel < 0 || channel > 5) return;

    if(tuning < 0 || tuning > 255) return;

    write_psg(channel, tuning);
}


void set_volume(int channel, int volume)
{
    if(channel < 8 || channel > 10) return;

    if(volume < 0 || volume > 15) return;
        
    write_psg(channel, volume);
}


void enable_channel(int channel, int tone_on, int noise_on)
{
    UINT8 original_mixer;

    if(channel < 0 || channel > 2) return;
       

    original_mixer = read_psg(MIXER_REG);

    /* Tone modifying */
    if(tone_on)
        original_mixer &= ~(1 << channel);
    else
        original_mixer |= (1 << channel);

    /* Noise modifying */
    if(noise_on)
        original_mixer &= ~(1 << (channel + 3));
    else
        original_mixer |= (1 << (channel + 3));

    write_psg(MIXER_REG, original_mixer);
}


void stop_sound()
{
    write_psg(MIXER_REG, 0x3F);  /* Disable all tone and noise */

    write_psg(8, 0);     /* Volume A */
    write_psg(9, 0);     /* Volume B */
    write_psg(10, 0);    /* Volume C */
}


void set_noise(int tuning)
{
    if(tuning < 0 || tuning > 31) return;

    write_psg(6, tuning & 0x1F);
}


void set_envelope(int shape, unsigned int sustain)
{
    if(shape < 0 || shape > 15) return;

    write_psg(11, sustain & 0xFF);        
    write_psg(12, (sustain >> 8) & 0xFF);

    write_psg(13, shape);
}

