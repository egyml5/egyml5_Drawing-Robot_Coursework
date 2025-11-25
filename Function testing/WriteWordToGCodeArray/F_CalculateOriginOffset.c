#include <stdio.h>
#include <stdlib.h>
#include "F_CalculateOriginOffset.h"

int F_FindWordOrigin(int PageWidth, int LineGap, int* OldWordEndXY, int* WordArray, int LengthWordArray, int FontSize, int* NewXY, int *PtrNewLineCount){

    int NewOriginXY[2] = {0};
    int OldX = OldWordEndXY[0];
    int OldY = OldWordEndXY[1];
    int LengthCheck;
    int NewLineCount = 0;
    int i;

    //printf("\n\t\tOldX = %d",OldX);
    //printf("\n\t\tOldY = %d",OldY);

    for(i=0; i<LengthWordArray; i++){
        if(WordArray[i] == 10){
            NewLineCount++;
        }
    }

    //printf("\n\t\tNewLineCount = %d",NewLineCount);

    LengthWordArray = LengthWordArray-NewLineCount;
    
    if(NewLineCount>0){
        //printf("\n\t\tSending to new line");
        NewOriginXY[0] = 0;
        NewOriginXY[1] = OldY-((FontSize+LineGap)*NewLineCount);
    }

    if(NewLineCount == 0){
        LengthCheck = (FontSize*LengthWordArray)+OldX;
        printf("\n\t\tLengthCheck = %d",LengthCheck);

        if (LengthCheck>100){
            printf("\n\t\tSending to new line");
            NewOriginXY[0] = 0;
            NewOriginXY[1] = OldY-FontSize-LineGap;
        }

        if (LengthCheck<=100){
            printf("\n\t\tNot sending to new line");
            NewOriginXY[0] = OldX;
            NewOriginXY[1] = OldY;
        }
    }

    //printf("\n\t\tNew word origin XY = %d %d",OldX,OldY);

    NewXY[0] = NewOriginXY[0];
    NewXY[1] = NewOriginXY[1];

    *PtrNewLineCount = NewLineCount;

    return 0;
}

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