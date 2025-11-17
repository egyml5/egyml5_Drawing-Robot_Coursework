#ifndef S_Characters
#define S_Characters
#include <stdio.h>
#include <stdlib.h>

typedef struct Characters
{
	int ascii;
	int length;
    int *Xpos;
    int *Ypos;
    int *Pen;
} Characters;

#endif