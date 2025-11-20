#include <stdio.h>
#include <stdlib.h>
#include "S_Characters.h"

int F_ResizeStructs(int FontSize, Characters Character){

    int i;
    int length;
    float OldX;
    float OldY;
    float NewX;
    float NewY;

    length = Character.length;


    for(i=0; i<length; i++){
        OldX = Character.Xpos[i];
        //printf("\n\t\tOldX = %f",OldX);
        NewX = (float)OldX*((float)FontSize/(float)18);
        //printf("\n\t\tNewX = %f",NewX);
        Character.Xpos[i] = NewX;
    }

    for(i=0; i<length; i++){
        OldY = Character.Ypos[i];
        //printf("\n\t\tOldY = %f",OldY);
        NewY = (float)OldY*((float)FontSize/(float)18);
        //printf("\n\t\tNewY = %f",NewY);
        Character.Ypos[i] = NewY;
    }

    return 0;
}