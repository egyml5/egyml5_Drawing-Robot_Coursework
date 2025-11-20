#include <stdio.h>
#include <stdlib.h>

int F_FindLetterOrigin(int* WordArray, int LengthOfArray, int FontSize, int NewX, int NewY, int *LetterOriginArray[]){

    int i;

    

    for (i=0; i<LengthOfArray; i++){
        printf("\n\t\tLetter %d XY =  %d %d",(i+1),LetterOriginArray[0][i],LetterOriginArray[1][i]);
    }

    return 0;
}