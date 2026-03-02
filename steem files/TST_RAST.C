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

	return 0;
}
