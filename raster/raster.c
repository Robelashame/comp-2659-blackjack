#include "raster.h"
#include "types.h"
#include "font.h"
#include <stdlib.h>

#define SCREEN_BYTES 32000
#define SCREEN_WIDTH 640
#define SCREEN_WIDTH_BYTES 80
#define SCREEN_HEIGHT 400

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
    for(i = 0; i < (SCREEN_BYTES/4); i++)
    {
        base[i] = 0x00000000;
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
            byteOffset = r * SCREEN_WIDTH_BYTES + (c >> 3);      /* find byte */
            mask = 0x01 << (7 - (c & 7));          /* find bit */
            base8[byteOffset] &= (UINT8)~mask;   /* clear bit */
        }   
    }
}

void plot_pixel(UINT8 *base, int row, int col)
{
    /* returns early if out of bounds */
    if (row < 0 || col < 0 || row >= SCREEN_HEIGHT || col >= SCREEN_WIDTH) return;
    *(base + row * SCREEN_WIDTH_BYTES + (col >> 3)) |= 1 << (7 - (col & 7));
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

/* Bresenham’s Algorithm */
/* Bresenham calculates the ideal mathematical line and keeps math to only interger addition and subtraction, no floats so math is faster */
/* Instead of calculating the slope each time, we calculate the error, this tells us how much we are above or below the true line */
/* if dy = 1, and dx = 2, slope = 1/2 = 0.5, which means for every 2 steps in x, we take 1 step in y, but instead we use 0-2 so no float numbers*/
/*  */
void plot_line(UINT32 *base, int start_row, int start_col, int end_row, int end_col)
{
    UINT8 *base8 = (UINT8 *)base;
    int x0, x1, y0, y1, dx, dy, sx, sy, err, e2;

    x0 = start_col;
    x1 = end_col;
    y0 = start_row;
    y1 = end_row;

    /* difference between points, or the displacement between them */
    dy = y1 - y0;
    dx = x1 - x0;

    if (dy < 0) dy = -dy;
    if (dx < 0) dx = -dx;

    /* step variable, determines whether the line steps left or right, up or down */
    sy = (y0 < y1) ? 1 : -1;
    sx = (x0 < x1) ? 1 : -1;

    /* determines how off you are from the ideal line between points, + = horizontally off, - = vertically off */
    err = dx - dy;

    while(1) {
        plot_pixel(base8, y0, x0);
        /* break after you reach you're desitination point */
        if (x0 == x1 && y0 == y1) break;

        /* 2*err, bresenham doesn't want to use fractions, so instead of checking the midpoint at 1/2 we check 1 which is between 0 and 2 */
        e2 = err << 1;

        /* checks if you haven't drifted too far vertically, then takes a step in x direction */
        if (e2 > -dy) {
            err -= dy;
            x0 += sx;
        } 
        /* checks if you haven't drifted too far horizontally, then takes a step in y direction */
        if (e2 < dx) {
        err += dx;
        y0 += sy;
        }
    }
}

void plot_rectangle(UINT32 *base, int row, int col, UINT16 length, UINT16 width)
{
    plot_vertical_line(base, row, col, length);
    plot_horizontal_line(base, row, col, width);
    plot_vertical_line(base, row, col + width - 1, length);
    plot_horizontal_line(base, row + length - 1, col, width);
}

void plot_square(UINT32 *base, int row, int col, UINT16 side)
{
    plot_rectangle(base, row, col, side, side);
}

void plot_triangle(UINT32 *base, int row, int col, UINT16 triangle_base, UINT16 height, UINT8 direction)
{  
    int base_ex, base_ey, height_ex, height_ey;
    int minRow = row, maxRow = row, minCol = col, maxCol = col;
    /* top left corner = base to the right and height down */
    if (direction == 0) {
        base_ex = col + triangle_base - 1;
        base_ey = row;
        height_ex = col;
        height_ey = row + height - 1;
    /* top right corner = base to the left and height down */
    } else if (direction == 1) { 
        base_ex = col - (triangle_base - 1);
        base_ey = row;
        height_ex = col;
        height_ey = row + height - 1;
    /* bottom left corner = base to the right and height up */
    } else if (direction == 2) {
        base_ex = col + triangle_base - 1;
        base_ey = row;
        height_ex = col;
        height_ey = row - (height - 1);
    /* bottom right corner = base to the left and height up */
    } else if (direction == 3) {
        base_ex = col - (triangle_base - 1);
        base_ey = row;
        height_ex = col;
        height_ey = row - (height - 1);
    } else return;

    plot_line(base, row, col, base_ey, base_ex);
    plot_line(base, row, col, height_ey, height_ex);
    plot_line(base, base_ey, base_ex, height_ey, height_ex);
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
    int r, c;
    UINT8 *base8 = (UINT8 *)base; 

    for (r = 0; r < height; r++)
    {
        for (c = 0; c < 16; c++) 
        {
            /* Correct: 0x8000 is the leftmost bit of a 16-bit word */
            if (bitmap[r] & (0x8000 >> c))
            {
                plot_pixel(base8, row + r, col + c);
            }
        }
    }
}

void plot_32bit_bitmap(UINT32 *base, int row, int col, const UINT32 *bitmap, UINT16 height)
{
    int r, c;
    UINT8 *base8 = (UINT8 *)base; /* Cast to byte-pointer for plot_pixel */

    for (r = 0; r < height; r++)
    {
        for (c = 0; c < 32; c++)
        {
            /* Use 1UL to force 32-bit logic. 
               We shift 1 left by (31 - c) to check bits from left-to-right. */
            if (bitmap[r] & (1UL << (31 - c)))
            {
                plot_pixel(base8, row + r, col + c);
            }
        }
    }
}

void plot_character(UINT8 *base, int row, int col, char ch)
{
    /* Check that character is allowed*/
    if (IS_PRINTABLE(ch)) 
    {
        /* Get pointer to the 8 bit char */
        const UINT8 *char_bitmap = GLYPH_START(ch);
        
        /* Plot the bitmap to the screen */
        plot_8bit_bitmap(base, row, col, char_bitmap, FONT_HEIGHT);
    }
}

void plot_string(UINT8 *base, int row, int col, char *str)
{
    /* 1. Loop through the string until the null terminator '\0' */
    while (*str != '\0')
    {
        /* 2. Plot the current character */
        plot_character(base, row, col, *str);
        
        /* 3. Move the column over by 8 pixels to make room for the next character */
        col += 8;
        
        /* 4. Move our pointer to the next character in the string */
        str++;
    }
}