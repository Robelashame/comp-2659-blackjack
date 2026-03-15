#ifndef INPUT.H
#define INPUT.H

#include <osbind.h>

/*----- Function: has_input -----

 PURPOSE: Checks whether a character is waiting to be read in GEMDOS.
        Cconis returns 0 if a character is unavailable, and -1 or 1? if a character is available.

 INPUT: None

 OUTPUT: Returns a 1 for true or 0 for false.
*/
bool has_input();

/*----- Function: get_input -----

 PURPOSE: Requests an input from GEMDOS to be processed, and waits for one to be available.

 INPUT: None

 OUTPUT: Returns a single character.
*/
char get_input();

#endif