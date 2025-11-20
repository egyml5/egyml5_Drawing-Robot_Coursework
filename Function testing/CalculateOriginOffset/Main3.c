#include <stdio.h>
#include <stdlib.h>
#include "F_FindWordOrigin.h"
#include "F_FindLetterOrigin.h"

int main () {

    int WordArray1[3] = {84, 104, 101};
    int WordArray2[6] = {32, 113, 117, 105, 99, 107};
    int WordArray5[7] = {10, 106, 117, 109, 112, 101, 100};

    int LengthOfArray1 = 3;
    int LengthOfArray2 = 6;
    int LengthOfArray5 = 7;

    int FontSize = 5;
    int OldOriginXY[2] = {80, -FontSize};
    int NewX;
    int NewY;
    int PageWidth = 100;
    int LineGap = 5;
    int i;

    int *LetterOriginArray[2] = {0};

    int ReturnVal1 = 0;
    int ReturnVal2 = 0;

    ReturnVal1 = F_FindWordOrigin(PageWidth, LineGap, OldOriginXY, WordArray1, LengthOfArray1, FontSize, &NewX, &NewY);

    printf("\n\t\tNew Word Origin XY = %d %d\n",NewX,NewY);

    LetterOriginArray[0] = calloc ( LengthOfArray1, sizeof(int));
    if ( LetterOriginArray[0] == NULL){
        printf ("\nMemory could not be allocated - terminating\n");
        return -1;
    }
    LetterOriginArray[1] = calloc ( LengthOfArray1, sizeof(int));
    if ( LetterOriginArray[1] == NULL){
        printf ("\nMemory could not be allocated - terminating\n");
        return -1;
    }

    ReturnVal2 = F_FindLetterOrigin(WordArray1, LengthOfArray1, FontSize, NewX, NewY, LetterOriginArray);

    //for (i=0; i<LengthOfArray1; i++){
    //    printf("\n\t\tLetter %d XY =  %d %d",(i+1),LetterOriginArray[0][i],LetterOriginArray[1][i]);
    //}

    printf("\n\n\t\tReturnVal1 = %d, ReturnVal2 = %d\n\n",ReturnVal1,ReturnVal2);

    return 0;
}