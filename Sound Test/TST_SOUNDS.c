#include <osbind.h>
#include <stdio.h>
#include "psg.h"
#include "raster.h"
#include "music.h"
#include "effects.h"

int main()
{
	UINT32 timenow;
	void *base = Physbase();

	printf("\033f");
	fflush(stdout);
	clear_screen(base);
	stop_sound();

	while(Cconis())
	{

	}
	Cnecin();                   
	plot_string(base, 50, 50, "Press Key to test channel A");

    /* Channel A Test */

    write_psg(0, 0xAA);
	write_psg(1, 0x01);

	write_psg(8, 15);

	write_psg(7, 0x3E);

    while (!Cconis())
	{

	}

	Cnecin();
	stop_sound();
	clear_screen(base);
	plot_string(base, 50, 50, "Press Key to test channel B");

    /* Channel B Test */

    set_tone(2, 0xCC);
    set_tone(3, 0x01);

    set_volume(9, 15);

    enable_channel(1, 1, 0);

    while (!Cconis())
	{

	}
	Cnecin();

	stop_sound();
	clear_screen(base);
	plot_string(base, 50, 50, "Press Key to test channel C");

    /* Channel C Test */

    set_tone(4, 0x88);
    set_tone(5, 0x02);

    set_volume(10, 15);

    enable_channel(2, 1, 0);

    while (!Cconis())
	{

	}
	Cnecin();

	stop_sound();
	clear_screen(base);
	plot_string(base, 50, 50, "Testing woosh effect sound");

	timenow = get_time();
	play_effect_woosh();
	while (!Cconis())
	{
		timenow = get_time();
		update_effects(timenow);
	}
	Cnecin();

	stop_sound();
	clear_screen(base);
	plot_string(base, 50, 50, "Testing hit effect sound");

	timenow = get_time();
	play_effect_hit();
	while (!Cconis())
	{
		timenow = get_time();
		update_effects(timenow);
	}
	Cnecin();

	stop_sound();
	clear_screen(base);
	plot_string(base, 50, 50, "Testing music");
	timenow = get_time();
	start_music();

	while(!Cconis())
	{
		timenow = get_time();
		update_music(timenow);
	}
	Cnecin();


	return 0;
}