#include <stdio.h>
#include <stdlib.h>

int F_FindWordOrigin(int PageWidth, int LineGap, int* OldOriginXY, int* WordArray, int LengthArray, int FontSize, int *NewX, int *NewY){

    int NewOriginXY[2] = {0};
    int OldX = OldOriginXY[0];
    int OldY = OldOriginXY[1];
    int LengthCheck;
    int NewLineCount = 0;
    int i;

    //printf("\n\t\tOldX = %d",OldX);
    //printf("\n\t\tOldY = %d",OldY);

    for(i=0; i<LengthArray; i++){
        if(WordArray[i] == 10){
            NewLineCount++;
        }
    }

    //printf("\n\t\tNewLineCount = %d",NewLineCount);

    LengthArray = LengthArray-NewLineCount;
    
    if(NewLineCount>0){
        //printf("\n\t\tSending to new line");
        NewOriginXY[0] = 0;
        NewOriginXY[1] = OldY-((FontSize+LineGap)*NewLineCount);
    }

    if(NewLineCount == 0){
        LengthCheck = (FontSize*LengthArray)+OldX;
        //printf("\n\t\tLengthCheck = %d",LengthCheck);

        if (LengthCheck>100){
            //printf("\n\t\tSending to new line");
            NewOriginXY[0] = 0;
            NewOriginXY[1] = OldY-FontSize-LineGap;
        }

        if (LengthCheck<100){
            //printf("\n\t\tNot sending to new line");
            NewOriginXY[0] = LengthCheck;
            NewOriginXY[1] = OldY;
        }
    }


    *NewX = NewOriginXY[0];
    *NewY = NewOriginXY[1];

    return 0;
}