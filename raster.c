#include "raster.h"
#include "font.h"

#define SCREEN_BYTES 32000
#define SCREEN_WIDTH 320
#define SCREEN_WIDTH_BYTES 80
#define SCREEN_HEIGHT 200
#define SCREEN_HEIGHT_BYTES 100

void clear_screen(UINT32 *base)
{
    int i;
    for(i = 0; i < SCREEN_BYTES; i++)
    {
        base[i] = 0;
    }
}

void clear_region(UINT32 *base, int row, int col, UINT16 length, UINT16 width)
{
    int r, c;
    UINT8 *byte_base = (UINT8 *)base; /* Cast to byte pointer for easier addressing */
    
    for(r = 0; r < length; r++)
    {
        for(c = 0; c < width; c++)
        {
            if (row + r < SCREEN_HEIGHT && col + c < SCREEN_WIDTH)
            {
                byte_base[(row + r) * SCREEN_WIDTH + (col + c)] = 0xFFFF;
            }
        }
    }
}
void plot_pixel(UINT8 *base, int row, int col)
{
    /* 1. Bounds checking to prevent memory corruption */
    if(row < 0 || row >= SCREEN_HEIGHT || col < 0 || col >= SCREEN_WIDTH) 
        return;

    /* 2. Use SCREEN_WIDTH (320) to find the start of the row, then add the column */
    /* 3. Setting the byte to 0xFF (or -1) turns the pixel 'on' */
    
    *(base + col * 80 + (row >> 3)) |= 1 << (7 - (row >> 3));
}
void plot_horizontal_line(UINT32 *base, int row, int col, UINT16 length)
{
    int i;
    UINT8 *byte_base = (UINT8 *)base;
    for(i = 0; i < length; i++)
    {
        plot_pixel(byte_base, row, col + i);
    }
}
void plot_vertical_line(UINT32 *base, int row, int col, UINT16 length)
{
    int i;
    UINT8 *byte_base = (UINT8 *)base;
    for(i = 0; i < length; i++)
    {
        plot_pixel(byte_base, row + i, col);
    }
}
void plot_line(UINT32 *base, int start_row, int start_col, int end_row, int end_col)
{
    
}
void plot_rectangle(UINT32 *base, int row, int col, UINT16 length, UINT16 width)
{
    
}
void plot_square(UINT32 *base, int row, int col, UINT16 side)
{
    
}
void plot_triangle(UINT32 *base, int row, int col, UINT16 triangle_base, UINT16 height, UINT8 direction)
{
    
}
void plot_8bit_bitmap(UINT8 *base, int row, int col, const UINT8 *bitmap, UINT16 height)
{
    int r, c;
    for(r = 0; r < height; r++)
    {
        for(c = 0; c < 8; c++)
        {
            /* Check if the specific bit is set (1) */
            if(bitmap[r] & (1 << (7 - c)))
            {
                plot_pixel(base, row + r, col + c);
            }
        }
    }
}

void plot_16bit_bitmap(UINT16 *base, int row, int col, const UINT16 *bitmap, UINT16 height)
{
    
}

void plot_32bit_bitmap(UINT32 *base, int row, int col, const UINT32 *bitmap, UINT16 height)
{
    
}



void plot_character(UINT8 *base, int row, int col, char ch)
{
    int x, y;
    for (y = 0; y < 16*10; y++)
    {
        UINT8 row_data = font[y];
        for (x = 0; x < 8*10; x++)
        {
            if (row_data & (0x80 >> x))
            {
                plot_pixel(base, x + col, y + row);
            }
        }
    }
}



void plot_string(UINT8 *base, int row, int col, char *ch)
{

}