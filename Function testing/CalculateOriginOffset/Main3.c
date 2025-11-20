#include <stdio.h>
#include <stdlib.h>
#include "F_FindWordOrigin.h"

int main () {

    int WordArray1[3] = {84, 104, 101};
    int WordArray2[6] = {32, 113, 117, 105, 99, 107};
    int WordArray5[7] = {10, 106, 117, 109, 112, 101, 100};

    int LengthArray1 = 3;
    int LengthArray2 = 6;
    int LengthArray5 = 7;

    int FontSize = 10;
    int OldOriginXY[2] = {90, -FontSize};
    int NewX;
    int NewY;
    int PageWidth = 100;
    int LineGap = 5;

    int ReturnVal1 = 0;
    int ReturnVal2 = 0;

    ReturnVal1 = F_FindWordOrigin(PageWidth, LineGap, OldOriginXY, WordArray1, LengthArray1, FontSize, &NewX, &NewY);

    printf("\n\t\tNew Origin XY = %d %d\n\n",NewX,NewY);

    //ReturnVal2 = F_FindLetterOrigin();

    return 0;
}