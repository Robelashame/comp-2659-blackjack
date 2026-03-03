#include "raster.h"
#include "types.h"

#define SCREEN_BYTES 32000
#define SCREEN_WIDTH 320
#define SCREEN_WIDTH_BYTES 160
#define SCREEN_HEIGHT 200
#define SCREEN_HEIGHT_BYTES 100

 /* byteOffset = row * 80 + (col / 8) */ 
 /* times by 80 is offset for bytes per row */ 
 /* int div by 8 is to check which byte */ 

 /* mask = 1 << (7 - (c & 7)); */ 
 /* bits are left to right, 7 -> 0 */ 
 /* 1 << bit */ 
 /* ex: bit is 5 */ 
 /*1 << 5 = 00010000 */ 
 /* taking the inverse of this gives you, to clear it */ 
 /* 11101111 */ 

void clear_screen(UINT32 *base)
{
    int i;
    for(i = 0; i < SCREEN_BYTES; i++)
    {
        base[i] = 0xFFFFFFFF;
    }
}

void clear_region(UINT32 *base, int row, int col, UINT16 length, UINT16 width)
{
    UINT8 *base8;
    UINT8 mask;
    UINT16 yEnd, xEnd;
    UINT32 byteOffset;
    int r, c;

    base8 = (UINT8 *)base;

    yEnd = row + length;
    xEnd = col + width;

    if (row < 0 || col < 0 || row >= SCREEN_HEIGHT || col >= SCREEN_WIDTH) return;
    if (yEnd > SCREEN_HEIGHT) yEnd = SCREEN_HEIGHT;
    if (xEnd > SCREEN_WIDTH) xEnd = SCREEN_WIDTH;

    for(r = row; r < yEnd; r++) {                
        for(c = col; c < xEnd; c++) {            
            byteOffset = r * 80 + (c >> 3);      /* find byte */
            mask = 0x01 << (7 - (c & 7));          /* find bit */
            base8[byteOffset] &= 0x00;   /* clear bit */
        }   
    }
}

void plot_pixel(UINT8 *base, int row, int col)
{
    if (row < 0 || col < 0 || row >= SCREEN_HEIGHT || col >= SCREEN_WIDTH) return;
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
    
}

void plot_16bit_bitmap(UINT16 *base, int row, int col, const UINT16 *bitmap, UINT16 height)
{
    
}

void plot_32bit_bitmap(UINT32 *base, int row, int col, const UINT32 *bitmap, UINT16 height)
{
    
}

void plot_character(UINT8 *base, int row, int col, char ch)
{
    
}

void plot_string(UINT8 *base, int row, int col, char *ch)
{

}