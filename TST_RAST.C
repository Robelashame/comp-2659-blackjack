#include <osbind.h>
#include <stdio.h>
#include "raster.h"

int main()
{
	void *base = Physbase();

	printf("\033f");
	fflush(stdout);
	printf("Clear Screen");
	Cnecin();
	clear_screen(base);
	plot_character(base, 0, 0, 'a');
	
	/*
	printf("\033f");
	fflush(stdout);
	printf("Clear Region 10x10");
	Cnecin();
	clear_region(base, 0, 0, 10, 10);
	

	printf("\033f");
	fflush(stdout);
	printf("Plot Pixel 50x50");
	plot_pixel(base, 50, 50);
	Cnecin();

	plot_pixel(base, 100, 100);
	Cnecin();

	plot_horizontal_line(base, 10, 10, 100);
	Cnecin();

	plot_vertical_line(base, 10, 10, 100);
	Cnecin();
	
	*/

	return 0;
}
