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

	plot_line(base, 100, 100, 200, 200);
	plot_line(base, 200, 200, 100, 300);
	plot_line(base, 50, 300, 200, 350);
	Cnecin();

	plot_line(base, -50, 50, 100, 100);
	plot_line(base, 350, 500, 450, 650);

	Cnecin();
	clear_screen(base);

	plot_string(base, 50, 50, "Testing plot_rectangle");
	Cnecin();
	clear_region(base, 50, 50, 16, 250);

	plot_rectangle(base, 100, 100, 50, 120);
	plot_rectangle(base, 200, 250, 80, 160);
	plot_rectangle(base, 50, 500, 40, 80);
	Cnecin();

	plot_rectangle(base, 50, -20, 50, 100);
	plot_rectangle(base, 350, 200, 80, 120);

	Cnecin();
	clear_screen(base);

	plot_string(base, 50, 50, "Testing plot_square");
	Cnecin();
	clear_region(base, 50, 50, 16, 250);

	plot_square(base, 120, 120, 40);
	plot_square(base, 200, 300, 60);
	plot_square(base, 80, 450, 50);
	Cnecin();

	plot_square(base, 50, -20, 60);
	plot_square(base, 350, 200, 80);

	Cnecin();
	clear_screen(base);

	plot_string(base, 50, 50, "Testing plot_triangle");
	Cnecin();
	clear_region(base, 50, 50, 16, 250);

	plot_triangle(base, 150, 150, 60, 60, 0);
	plot_triangle(base, 150, 300, 60, 60, 1);
	plot_triangle(base, 300, 150, 60, 60, 2);
	plot_triangle(base, 300, 300, 60, 60, 3);
	Cnecin();

	plot_triangle(base, 50, 50, 80, 80, 3);

	Cnecin();
	clear_screen(base);

	plot_string(base, 50, 50, "Testing plot_8bit_bitmap");
	Cnecin();
	clear_region(base, 50, 50, 16, 250);

	plot_8bit_bitmap(base, 100, 100, bitmap8, 8);
	plot_8bit_bitmap(base, 100, 200, bitmap8, 8);
	plot_8bit_bitmap(base, 200, 300, bitmap8, 8);
	Cnecin();

	plot_8bit_bitmap(base, 50, -4, bitmap8, 8);

	Cnecin();
	clear_screen(base);

	plot_string(base, 50, 50, "Testing plot_16bit_bitmap");
	Cnecin();
	clear_region(base, 50, 50, 16, 250);

	plot_16bit_bitmap(base, 100, 100, diamond, 10);
	plot_16bit_bitmap(base, 150, 250, spade, 16);
	plot_16bit_bitmap(base, 200, 400, heart, 16);
	Cnecin();

	plot_16bit_bitmap(base, 50, -8, diamond, 10);

	Cnecin();
	clear_screen(base);

	plot_string(base, 50, 50, "Testing plot_32bit_bitmap");
	Cnecin();
	clear_region(base, 50, 50, 16, 250);

	plot_32bit_bitmap(base, 100, 100, bitmap32, 10);
	plot_32bit_bitmap(base, 150, 250, bitmap32, 10);
	plot_32bit_bitmap(base, 200, 400, bitmap32, 10);
	Cnecin();

	plot_32bit_bitmap(base, 50, -16, bitmap32, 10);

	Cnecin();
	clear_screen(base);

	plot_string(base, 50, 50, "Testing plot_character");
	Cnecin();
	clear_region(base, 50, 50, 16, 250);

	plot_character(base, 100, 100, 'A');
	plot_character(base, 100, 120, 'B');
	plot_character(base, 100, 140, '7');
	Cnecin();

	plot_character(base, 0, 0, 'X');

	Cnecin();
	clear_screen(base);

	plot_string(base, 50, 50, "Testing plot_string");
	Cnecin();
	clear_region(base, 50, 50, 16, 250);

	plot_string(base, 120, 100, "Hello");
	plot_string(base, 160, 100, "Raster test");
	plot_string(base, 200, 100, "Blackjack");
	Cnecin();

	plot_string(base, 250, 580, "Edge Case");

	Cnecin();
	clear_screen(base);

	plot_string(base, 50, 50, "Final raster demo");
	Cnecin();
	clear_region(base, 50, 50, 16, 250);

	plot_rectangle(base, 40, 40, 80, 140);
	plot_square(base, 60, 250, 60);
	plot_triangle(base, 250, 120, 80, 80, 0);
	plot_line(base, 50, 550, 200, 620);
	plot_16bit_bitmap(base, 180, 350, diamond, 10);
	plot_string(base, 340, 300, "Done");

	Cnecin();
	clear_region(base, 150, 330, 80, 120);
	Cnecin();
	clear_screen(base);

	return 0;
}