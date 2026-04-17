#ifndef INPUT_H
#define INPUT_H

#include <osbind.h>
#include "types.h"

typedef struct {
       int x;
       int y;
       UINT8 buttons;
       UINT8 pressed;
       UINT8 released;
       UINT8 moved;
} MouseState;

/*----- Function: has_input -----

 PURPOSE: Checks whether a character is waiting to be read in GEMDOS.
        Cconis returns 0 if a character is unavailable, and -1 or 1? if a character is available.

 INPUT: None

 OUTPUT: Returns a non-zero number for true and 0 for false.
*/
int has_input();

/*----- Function: get_input -----

 PURPOSE: Requests an input from GEMDOS to be processed, and waits for one to be available.

 INPUT: None

 OUTPUT: Returns a single character.
*/
char get_input();

/*----- Function: update_mouse -----

 PURPOSE: Updates the mouse once and updates the local struct.

 INPUT: None

 OUTPUT: None
*/
void update_mouse(MouseState *state);

/*----- Function: input_mouse_init -----

 PURPOSE: Installs the ISR and connects to the source.

 INPUT: None

 OUTPUT: None
*/
void ikbd_init(void);
void ikbd_uninstall(void);

extern volatile int mouse_x;
extern volatile int mouse_y;
extern volatile int mouse_buttons;

#endif