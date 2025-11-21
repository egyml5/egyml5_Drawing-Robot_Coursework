#include <stdio.h>
#include <stdlib.h>

int F_FindLetterOrigin(int PageWidth, int LineGap, int* WordArray, int LengthOfArray, int FontSize, int* NewWordStartXY, int *LetterOriginArray[]){

    int i;
    int k;
    int OverspillCheck = 0;
    int LetterStartX = NewWordStartXY[0];
    int LetterStartY = NewWordStartXY[1];

    for (k=0; k<LengthOfArray; k++){
        LetterOriginArray[0][k] = LetterStartX;
        LetterOriginArray[1][k] = LetterStartY;

        OverspillCheck = LetterStartX+FontSize;

        if (OverspillCheck>=PageWidth){
            LetterStartX = 0;
            LetterStartY = LetterStartY-FontSize-LineGap;
        }

        if (OverspillCheck<PageWidth){
            LetterStartX = LetterStartX+FontSize;
            LetterStartY = LetterStartY;
        }
    }

    //for (i=0; i<LengthOfArray; i++){
    //    printf("\n\t\tLetter %d XY =  %d %d",(i+1),LetterOriginArray[0][i],LetterOriginArray[1][i]);
    //}

    return 0;
}