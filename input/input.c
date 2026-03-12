#include "input.h"

int has_input() 
{
    return Cconis() != 0;
}

char get_input()
{
    char in;
    in = Cconin();
    return (char)in;
}