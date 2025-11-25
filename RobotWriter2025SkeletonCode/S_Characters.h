#ifndef S_Characters
#define S_Characters
#include <stdio.h>
#include <stdlib.h>

typedef struct Characters
{
	int ascii;
	int length;
    float *Xpos;
    float *Ypos;
    int *Pen;
} Characters;

#endif