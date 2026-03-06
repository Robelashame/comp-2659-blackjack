#include <osbind.h>
#include <stdio.h>
#include "raster.h"

/* 8x8 "X" shape */
const UINT8 bitmap8[] = {
    0x81, 0x42, 0x24, 0x18, 0x18, 0x24, 0x42, 0x81
};

/* 16x10 Diamond shape */
const UINT16 diamond[] = {
    0x0180, 0x03C0, 0x07E0, 0x0FF0, 0x1FF8, 
    0x1FF8, 0x0FF0, 0x07E0, 0x03C0, 0x0180
};

/* 16x16 Spade shape */
const UINT16 spade[] = {
    0x0000, 0x0180, 0x03c0, 0x07e0, 0x0ff0, 0x1ff8, 0x1ff8, 0x1ff8, 
	0x1ff8, 0x0ff0, 0x0180, 0x03c0, 0x03c0, 0x07e0, 0x0000, 0x0000
};

/* 16x16 Heart shape */
const UINT16 heart[] = {
    0x0000, 0x3c3c, 0x7e7e, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
	0xffff, 0xffff, 0x7ffe, 0x3ffc, 0x1ff8, 0x0ff0, 0x07e0, 0x03c0
};


/* 32x10 Downward Arrow */
const UINT32 bitmap32[] = {
    0x00000F00, 0x0000FF00, 0x000FFFFF, 0x00FFFFFF, 0x0FFFFFFF,
    0x0FFFFFFF, 0x00FFFFFF, 0x000FFFFF, 0x0000FF00, 0x00000F00
};

int main()
{
	void *base = Physbase();

	printf("\033f");
	fflush(stdout);
	/*
	clear_region(base, 50, 50, 16, 250);
	plot_string(base, 50, 50, "Press any key to clear screen.");
	Cnecin();
	clear_screen(base);

	plot_string(base, 50, 50, "Testing plot_pixel");
	Cnecin();
	clear_region(base, 50, 50, 16, 250);
	plot_pixel(base, 0, 0);
	plot_pixel(base, 399, 0);
	plot_pixel(base, 0, 639);
	plot_pixel(base, 399, 639);
	plot_pixel(base, 200, 320);
	Cnecin();
	
	clear_region(base, 50, 50, 16, 250);
	plot_string(base, 50, 50, "Press any key to clear screen.");
	Cnecin();
	clear_screen(base);

	plot_string(base, 50, 50, "Error bounds");
	Cnecin();
	clear_region(base, 50, 50, 16, 250);
	plot_pixel(base, -1, 0);
	plot_pixel(base, 0, -1);
	plot_pixel(base, 400, 0);
	plot_pixel(base, 0, 640);

	Cnecin();
	plot_string(base, 50, 50, "Testing clear_region");
	plot_string(base, 66, 50, "abcdefghijklmnopqrstuvwxyz");

	Cnecin();
	clear_region(base, 50, 50, 16, 250);
	Cnecin();
	clear_region(base, 50, 50, 32, 100);
	Cnecin();
	clear_region(base, 50, 100, 32, 100);
	Cnecin();
	clear_region(base, 50, 150, 32, 120);
	Cnecin();
	
	plot_string(base, 50, 50, "Testing plot_horizontal_line");
	Cnecin();
	clear_region(base, 50, 50, 16, 250);

	plot_string(base, 50, 50, "Normal lines");
	Cnecin();
	clear_region(base, 50, 50, 16, 250);

	plot_horizontal_line(base, 0, 0, 100);
	plot_horizontal_line(base, 100, 0, 100);
	plot_horizontal_line(base, 150, 0, 640);
	plot_horizontal_line(base, 200, 320, 100);
	plot_horizontal_line(base, 399, 220, 100);
	Cnecin();

	plot_string(base, 50, 50, "Clipping lines");
	Cnecin();
	clear_region(base, 50, 50, 16, 250);

	plot_horizontal_line(base, 250, 320, 400);
	plot_horizontal_line(base, 300, 320, 350);
	*/
	Cnecin();
	clear_screen(base);

	plot_string(base, 50, 50, "Testing plot_vertical_line");
	Cnecin();
	clear_region(base, 50, 50, 16, 250);

	plot_vertical_line(base, 0, 0, 200);
	plot_vertical_line(base, 100, 320, 200);
	plot_vertical_line(base, 0, 639, 200);
	plot_vertical_line(base, 300, 0, 200);
	plot_vertical_line(base, 300, 639, 300);

	Cnecin();
	clear_screen(base);
	
	plot_string(base, 50, 50, "Testing plot_line");
	Cnecin();
	clear_region(base, 50, 50, 16, 250);

	/*
	plot_character(base, 0, 0, 'a');
	plot_string(base, 50, 50, "Monkey!");

	plot_8bit_bitmap(base, 20, 20, bitmap8, 8);
	plot_16bit_bitmap((UINT16 *)base, 20, 50, spade, 16);
	plot_16bit_bitmap((UINT16 *)base, 110, 54, heart, 16);
	plot_character(base, 102, 59, 'A');
	plot_character(base, 1020, 610, 'A');
	plot_rectangle(base, 100, 50, 200, 100);
	plot_16bit_bitmap((UINT16 *)base, 20, 80, diamond, 10);
	plot_32bit_bitmap((UINT32 *)base, 50, 100, bitmap32, 10);
	*/
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
