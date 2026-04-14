#ifndef DOUBLE_H
#define DOUBLE_H

#include "TYPES.H"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 400
#define SCREEN_SIZE ((SCREEN_WIDTH * SCREEN_HEIGHT) / 8)
#define ALIGNMENT 256

void init_buffer();
void swap_buffer();
void clear_buffer();
void test_swap();
void restore_screen();

UINT8 *get_front_buffer(void);
UINT8 *get_back_buffer(void);

#endif