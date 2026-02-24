#include <raster.h>

#define SCREEN_BYTES 32000
#define SCREEN_WIDTH 320
#define SCREEN_WIDTH_BYTES 160
#define SCREEN_HEIGHT 200
#define SCREEN_HEIGHT_BYTES 100

void clear_screen(UINT32 *base)
{
    for(int i = 0; i < SCREEN_BYTES; i++)
    {
        base[i] = 0;
    }
}

void clear_region(UINT32 *base, UINT16 row, UINT16 col, UINT16 length, UINT16 width)
{
    
}
void plot_pixel(UINT8 *base, UINT16 row, UINT16 col)
{
    if(row < 0 || row >= SCREEN_HEIGHT || col < 0 || col >= SCREEN_WIDTH) return;

    base[row * SCREEN_HEIGHT + col] = 1;
}
void plot_horizontal_line(UINT32 *base, UINT16 row, UINT16 col, UINT16 length)
{
    for(int i = 0; i < length)
    {
        plot_pixel(base, row, col);
        row++;
    }
}
void plot_vertical_line(UINT32 *base, UINT16 row, UINT16 col, UINT16 length)
{
    for(int i = 0; i < length)
    {
        plot_pixel(base, row, col);
        col++;
    }
}
void plot_line(UINT32 *base, UINT16 start_row, UINT16 start_col, UINT16 end_row, UINT16 end_col)
{
    
}
void plot_rectangle(UINT32 *base, UINT16 row, UINT16 col, UINT16 length, UINT16 width)
{
    
}
void plot_square(UINT32 *base, UINT16 row, UINT16 col, UINT16 side)
{
    
}
void plot_triangle(UINT32 *base, UINT16 row, UINT16 col, UINT16 base, UINT16 height, UINT8 direction)
{
    
}
void plot_bitmap_8(UINT8 *base, UINT16 row, UINT16 col, UINT16 height)
{
    
}

void plot_bitmap_16(UINT16 *base, UINT16 row, UINT16 col, UINT16 height)
{
    
}

void plot_bitmap_32(UINT32 *base, UINT16 row, UINT16 col, UINT16 height)
{
    
}



void plot_character(UINT8 *base, UINT16 row, UINT16 col, char ch)
{
    
}



void plot_string(UINT8 *base, UINT16 row, UINT16 col, char *ch)
{

}