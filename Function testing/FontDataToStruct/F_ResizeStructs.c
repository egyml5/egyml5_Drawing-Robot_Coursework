#include <stdio.h>
#include <stdlib.h>
#include "S_Characters.h"

int F_ResizeStructs(int FontSize, Characters Character){

    int i;
    int length;
    int OldX;
    int OldY;
    int NewX;
    int NewY;

    length = Character.length;


    for(i=0; i<length; i++){
        OldX = Character.Xpos[i];
        NewX = OldX*((float)FontSize/(float)18);
        Character.Xpos[i] = NewX;
    }

    for(i=0; i<length; i++){
        OldY = Character.Ypos[i];
        NewY = OldY*((float)FontSize/(float)18);
        Character.Ypos[i] = NewY;
    }

    return 0;
}