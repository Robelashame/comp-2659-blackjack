#include <osbind.h>
#include <stdio.h>
#include "raster.h"

int main()
{
	void *base = Physbase();

	printf("\033f");
	fflush(stdout);

	clear_screen(base);
	Cnecin();
	clear_region(base, 0, 0, 10, 10);
	plot_pixel(base, 0, 0);
	Cnecin();
	plot_pixel(base, 2, 2);
	Cnecin();
	plot_pixel(base, 100, 100);
	Cnecin();
	printf("Im doin it!");
	plot_horizontal_line(base, 10, 10, 100);
	Cnecin();
	plot_vertical_line(base, 10, 10, 100);
	Cnecin();
	
	

	return 0;
}
