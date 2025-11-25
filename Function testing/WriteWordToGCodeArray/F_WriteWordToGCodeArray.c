#include <stdio.h>
#include <stdlib.h>
#include "S_Characters.h"
#include "F_WriteWordToGCodeArray.h"

int F_FindLengthGCodeArray(int *WordArray, int *ptrGCodeArrayLength, Characters *CharacterArray, int WordCharacterCount, int NewLineCount){

    int i;
    int q;
    int k;
    int GCodeArraylength = 0;
    int OldPen = 0;
    int *PenArray;
    int LetterASCII;

    for (i=NewLineCount;i<WordCharacterCount;i++){
        LetterASCII = WordArray[i];

        GCodeArraylength = GCodeArraylength + CharacterArray[LetterASCII].length;
        PenArray = CharacterArray[LetterASCII].Pen;

        for (q=0;q<CharacterArray[LetterASCII].length;q++){
            if(PenArray[q] != OldPen){
                GCodeArraylength++;
            }
            OldPen = PenArray[q];
        }

    }

    *ptrGCodeArrayLength = GCodeArraylength;

    return 0;
}