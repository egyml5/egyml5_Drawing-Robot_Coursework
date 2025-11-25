#include <stdio.h>
#include <stdlib.h>
#include "F_FontDataToStruct.h"
#include "F_CountLetters.h"
#include "S_Characters.h"
#include "F_ResizeStructs.h"
#include "F_ReadWordToASCIIArray.h"
#include "F_CountWords.h"
#include "F_CountSkipCharacters.h"
#include "F_FindWordOrigin.h"
#include "F_FindLetterOrigin.h"

typedef struct Characters
{
	int ascii;
	int length;
    float *Xpos;
    float *Ypos;
    int *Pen;
} Characters;

int main () {
    
    //Input values
    int FontSize = 10;
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
    
    //Code to read, convert and store input text and font in a usable format
    ReturnVal1 = F_CountLetters("FontData.txt", &NumberOfASCIICharacters);

    ReturnVal2 = F_FontDataToStruct("FontData.txt", &CharacterArray, &NumberOfASCIICharacters);

    for(i=0; i<NumberOfASCIICharacters; i++){
        ReturnVal3 = F_ResizeStructs(FontSize, CharacterArray[i]);
    }

    ReturnVal4 = F_CountWords("test.txt", &CharacterCount, &WordCount);

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

    //Loop loop variables
    int q;

    for (k=1;k<=WordCount;k++){

        ReturnVal5 = F_CountSkipCharacters("test.txt", k, &SkipCount);

        ReturnVal6 = F_ReadWordToASCIIArray("test.txt", k, &WordArray, SkipCount, &WordCharacterCount);

        ReturnVal7 = F_FindWordOrigin(PageWidth, LineGap, OldWordEndXY, WordArray, WordCharacterCount, FontSize, NewWordStartXY, &NewLineCount);

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

        ReturnVal8 = F_FindLetterOrigin(PageWidth, LineGap, WordArray, LengthOfWord, FontSize, NewWordStartXY, LetterOriginArray);



        printf("\n\t\tNew Word Origin XY = %d %d",NewWordStartXY[0],NewWordStartXY[1]);
        printf("\n\t\tNewLineCount = %d",NewLineCount);
        printf("\n\t\tWordArray =");
        for (q=0;q<WordCharacterCount;q++){
            printf(" %d",WordArray[q]);
        }
        for (q=0; q<LengthOfWord; q++){
        printf("\n\t\tLetter %d XY =  %d %d",(q+NewLineCount+1),LetterOriginArray[0][q],LetterOriginArray[1][q]);
        }

    }

    printf("\n\nRV1 = %d, RV2 = %d, RV3 = %d, RV4 = %d, RV5 = %d, RV6 = %d, RV7 = %d, RV8 = %d\n\n",ReturnVal1,ReturnVal2,ReturnVal3,ReturnVal4,ReturnVal5,ReturnVal6,ReturnVal7,ReturnVal8);

    return 0;
}