#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "F_FontDataToStruct.h"
#include "F_CalculateOriginOffset.h"
#include "S_Characters.h"
#include "F_ReadWordToASCIIArray.h"
#include "F_WriteWordToGCodeArray.h"

int main () {
    
    //Input values
    int FontSize = 7;
    int PageWidth = 100;
    int LineGap = 5;
    
    //Calculation variables
    Characters *CharacterArray;
    int NumberOfASCIICharacters;
    int CharacterCount;
    int WordCount;

    //Loop Variables
    int i;
    int k;

    //Return Values
    int ReturnVal1;
    int ReturnVal2;
    int ReturnVal3;
    int ReturnVal4;
    int ReturnVal5;
    int ReturnVal6;
    int ReturnVal7;
    int ReturnVal8;
    int ReturnVal9;
    int ReturnVal10;
    int ReturnVal11;
    
    //Code to read, convert and store input text and font in a usable format
    ReturnVal1 = F_CountLetters("FontData.txt", &NumberOfASCIICharacters);

    ReturnVal2 = F_FontDataToStruct("FontData.txt", &CharacterArray, &NumberOfASCIICharacters);

    for(i=0; i<NumberOfASCIICharacters; i++){
        ReturnVal3 = F_ResizeStructs(FontSize, CharacterArray[i]);
    }

    for(i=0; i<NumberOfASCIICharacters; i++){
        ReturnVal4 = F_DisplayCharacter(CharacterArray[i]);
    }
    
    ReturnVal5 = F_CountWords("test.txt", &CharacterCount, &WordCount);

    //loop to read each word and convert to GCode
    //Loop calculation variables
    int SkipCount = 0;
    int *WordArray;
    int WordCharacterCount;
    int OldWordEndXY[2] = {0, -FontSize};
    int NewWordStartXY[2];
    int NewLineCount;
    int LengthOfWord;
    int *LetterOriginArray[2] = {0};
    int GCodeArrayLength;
    char *GCodeArray;

    //Loop loop variables
    int q;
    int z;

    for (k=1;k<=WordCount;k++){

        ReturnVal6 = F_CountSkipCharacters("test.txt", k, &SkipCount);

        ReturnVal7 = F_ReadWordToASCIIArray("test.txt", k, &WordArray, SkipCount, &WordCharacterCount);

        ReturnVal8 = F_FindWordOrigin(PageWidth, LineGap, OldWordEndXY, WordArray, WordCharacterCount, FontSize, NewWordStartXY, &NewLineCount);

        LengthOfWord = WordCharacterCount-NewLineCount;
        LetterOriginArray[0] = calloc ( LengthOfWord, sizeof(int));
        if ( LetterOriginArray[0] == NULL){
            printf ("\nMemory could not be allocated - terminating\n");
            return -1;
        }
        LetterOriginArray[1] = calloc ( LengthOfWord, sizeof(int));
        if ( LetterOriginArray[1] == NULL){
            printf ("\nMemory could not be allocated - terminating\n");
            return -1;
        }

        ReturnVal9 = F_FindLetterOrigin(PageWidth, LineGap, WordArray, LengthOfWord, FontSize, NewWordStartXY, LetterOriginArray);

        /*
        printf("\n\t\tNew Word Origin XY = %d %d",NewWordStartXY[0],NewWordStartXY[1]);
        printf("\n\t\tNewLineCount = %d",NewLineCount);
        printf("\n\t\tWordArray =");
        for (q=0;q<WordCharacterCount;q++){
            printf(" %d",WordArray[q]);
        }
        for (q=0; q<LengthOfWord; q++){
        printf("\n\t\tLetter %d XY =  %d %d",(q+NewLineCount+1),LetterOriginArray[0][q],LetterOriginArray[1][q]);
        }
        */

        OldWordEndXY[0] = LetterOriginArray[0][LengthOfWord-1]+FontSize;
        OldWordEndXY[1] = LetterOriginArray[1][LengthOfWord-1];

        ReturnVal10 = F_FindLengthGCodeArray(WordArray, &GCodeArrayLength, CharacterArray, WordCharacterCount, NewLineCount);
        //printf("\n\t\tGCodeArray length = %d\n",GCodeArrayLength);

        ReturnVal11 = F_WriteGCodeWordArray(WordArray, LetterOriginArray, GCodeArrayLength, CharacterArray, WordCharacterCount, NewLineCount, GCodeArray);

        //printf("\n");
    }

    printf("\n\nRV1 = %d, RV2 = %d, RV3 = %d, RV4 = %d, RV5 = %d, RV6 = %d, RV7 = %d, RV8 = %d, RV9 = %d\n\n",ReturnVal1,ReturnVal2,ReturnVal3,ReturnVal4,ReturnVal5,ReturnVal6,ReturnVal7,ReturnVal8,ReturnVal9);



    return 0;
}

