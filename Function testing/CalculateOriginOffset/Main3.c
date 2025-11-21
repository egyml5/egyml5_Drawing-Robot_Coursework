#include <stdio.h>
#include <stdlib.h>
#include "F_FindWordOrigin.h"
#include "F_FindLetterOrigin.h"

int main () {

    int WordArray1[3] = {84, 104, 101};
    int WordArray2[6] = {32, 113, 117, 105, 99, 107};
    int WordArray5[7] = {10, 10, 10, 106, 117, 109, 112, 101, 100, 100, 100, 100};

    int LengthOfArray1 = 3;
    int LengthOfArray2 = 6;
    int LengthOfArray5 = 12;

    int FontSize = 5;
    int OldWordEndXY[2] = {0, -FontSize};
    int NewWordStartXY[2];
    int NewY;
    int PageWidth = 30;
    int LineGap = 5;
    int i;
    int k = 1;
    int NewLineCount;

    int *LetterOriginArray[2] = {0};

    int ReturnVal1 = 0;
    int ReturnVal2 = 0;

    printf("\n\t\tOld Word End XY = %d %d\n",OldWordEndXY[0],OldWordEndXY[1]);

    ReturnVal1 = F_FindWordOrigin(PageWidth, LineGap, OldWordEndXY, WordArray5, LengthOfArray5, FontSize, NewWordStartXY, &NewLineCount);

    printf("\n\t\tNew Word Origin XY = %d %d\n",NewWordStartXY[0],NewWordStartXY[1]);
    printf("\n\t\tNewLineCount = %d\n",NewLineCount);

    LengthOfArray5 = LengthOfArray5-NewLineCount;

    LetterOriginArray[0] = calloc ( LengthOfArray5, sizeof(int));
    if ( LetterOriginArray[0] == NULL){
        printf ("\nMemory could not be allocated - terminating\n");
        return -1;
    }
    LetterOriginArray[1] = calloc ( LengthOfArray5, sizeof(int));
    if ( LetterOriginArray[1] == NULL){
        printf ("\nMemory could not be allocated - terminating\n");
        return -1;
    }

    ReturnVal2 = F_FindLetterOrigin(PageWidth, LineGap, WordArray5, LengthOfArray5, FontSize, NewWordStartXY, LetterOriginArray);

    k = 1+NewLineCount;

    for (i=0; i<LengthOfArray5; i++){
        printf("\n\t\tLetter %d XY =  %d %d",(i+k),LetterOriginArray[0][i],LetterOriginArray[1][i]);
    }

    printf("\n\n\t\tReturnVal1 = %d, ReturnVal2 = %d\n\n",ReturnVal1,ReturnVal2);

    return 0;
}