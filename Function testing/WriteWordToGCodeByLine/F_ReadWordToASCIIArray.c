#include <stdio.h>
#include <stdlib.h>
#include "F_ReadWordToASCIIArray.h"

int F_CountSkipCharacters(char* InputText, int Word, int *SkipCount){

    int WordCount = 1;
    int TempChar;
    int ASCII = -1;
    int PastASCII = -1;
    int CountSkips = 0;

    //printf("\n\t\tWord number = %d",Word);

    FILE *fptr = fopen(InputText, "r");
    if ( fptr == NULL){
        printf ("\n\t\tthe file could not be opened for reading, exiting");
        fclose(fptr);
        return -1;
    }

    if (WordCount == Word){
        *SkipCount = CountSkips;
        fclose (fptr);
        return 0;
    }

    while (1){

        TempChar = fgetc(fptr);
        if (TempChar == EOF){
            printf("\n\t\tError, Reached EOF before Wordcount");
            fclose (fptr);
            return -1;
        }
        ASCII = (int)TempChar;

        if (ASCII == 32 && PastASCII != 10 && PastASCII != 32 && PastASCII != -1){
            WordCount++;
            if (WordCount == Word){
                break;
            }
        }

        if (ASCII == 10 && PastASCII != 10 && PastASCII != 32 && PastASCII != -1){
            WordCount++;
            if (WordCount == Word){
                break;
            }
        }
        CountSkips++;
        PastASCII = ASCII;
    }

    if (WordCount == Word){
        *SkipCount = CountSkips;
        fclose (fptr);
        return 0;
    }

    if (WordCount>Word){
        printf("\n\t\tError Counted past word");
        fclose (fptr);
        return -1;
    }
    
}

int F_CountWords(char* InputText, int *CharacterCount, int *WordCount){

    int NumberOfCharacters = 0;
    int NumberOfWords = 0;
    int EndCheck;
    char TempChar;
    int ASCII = 0;
    int PastASCII = -1;

    FILE *fptr = fopen(InputText, "r");
    if ( fptr == NULL){
        printf ("\n\t\tthe file could not be opened for reading, exiting");
        fclose(fptr);
        return -1;
    }

    while (1){
        TempChar = fgetc(fptr);
        if (TempChar == EOF){
            break;
        }

        ASCII = (int)TempChar;
        NumberOfCharacters++;

        if (ASCII != 32 && ASCII != 10 && PastASCII == -1){
            NumberOfWords++;
        }

        if (ASCII != 32 && ASCII != 10 && PastASCII == 32){
            NumberOfWords++;
        }

        if (ASCII != 32 && ASCII != 10 && PastASCII == 10){
            NumberOfWords++;
        }
        PastASCII = ASCII;
    }

    fclose(fptr);
    
    *CharacterCount = NumberOfCharacters;
    *WordCount = NumberOfWords;

    return 0;
}

int F_ReadWordToASCIIArray(char* InputText, int Word, int **WordArray, int SkipCount, int *WordCharacterCount){

    int EndCheck;
    char TempChar;
    int ASCII = 0;
    int PastASCII = -1;
    int *ASCIIArray;
    int CharacterCount = 0;
    int i;

    //printf("\n\t\tword number = %d",Word);

    FILE *fptr = fopen(InputText, "r");
    if ( fptr == NULL){
        printf ("\n\t\tthe file could not be opened for reading, exiting");
        fclose(fptr);
        return -1;
    }

    for (i=0;i<SkipCount;i++){
        TempChar = fgetc(fptr);
    }

    while (1){

        TempChar = fgetc(fptr);
        if (TempChar == EOF){
            break;
        }
        ASCII = (int)TempChar;

        if (ASCII == 32 && PastASCII != 10 && PastASCII != 32 && PastASCII != -1){
            break;
        }
        if (ASCII == 10 && PastASCII != 10 && PastASCII != 32 && PastASCII != -1){
            break;
        }

        CharacterCount++;
        PastASCII = ASCII;
    }

    //printf("\n\t\tCharacter count = %d",CharacterCount);

    fclose(fptr);

    ASCIIArray = calloc ( CharacterCount , sizeof(int));
    if ( ASCIIArray == NULL){
        printf ("\nMemory could not be allocated - terminating\n");
        return -1;
    }

    fptr = fopen(InputText, "r");
    if ( fptr == NULL){
        printf ("\n\t\tthe file could not be opened for reading, exiting");
        fclose(fptr);
        return -1;
    }

    for (i=0;i<SkipCount;i++){
        TempChar = fgetc(fptr);
    }

    for (i=0;i<CharacterCount;i++){
        TempChar = fgetc(fptr);
        ASCIIArray[i] = (int)TempChar;
    }

    //printf("\n\t\tASCIIArray =");
    //for (i=0;i<CharacterCount;i++){
    //    printf(" %d",ASCIIArray[i]);
    //}

    *WordArray = ASCIIArray;
    *WordCharacterCount = CharacterCount;
    
    return 0;
}

int F_FindWordOrigin(int PageWidth, int LineGap, int* OldWordEndXY, int* WordArray, int LengthWordArray, int FontSize, int* NewXY, int *PtrNewLineCountIn, int *PtrNewLineCountOut){

    int NewOriginXY[2] = {0};
    int OldX = OldWordEndXY[0];
    int OldY = OldWordEndXY[1];
    int LengthCheck;
    int NewLineCountIn = 0;
    int NewLineCountOut = 0;
    int i;

    //printf("\n\t\tOldX = %d",OldX);
    //printf("\n\t\tOldY = %d",OldY);

    for(i=0; i<LengthWordArray; i++){
        if(WordArray[i] == 10){
            NewLineCountIn++;
        }
    }

    //printf("\n\t\tNewLineCount = %d",NewLineCount);

    //LengthWordArray = LengthWordArray-NewLineCountIn;
    
    if(NewLineCountIn>0){
        //printf("\n\t\tSending to new line");
        NewOriginXY[0] = 0;
        NewOriginXY[1] = OldY-((FontSize+LineGap)*NewLineCountIn);
    }

    if(NewLineCountIn == 0){
        LengthCheck = (FontSize*LengthWordArray)+OldX;
        //printf("\n\t\tLengthCheck = %d",LengthCheck);

        if (LengthCheck>100){
            //printf("\n\t\tSending to new line");
            NewOriginXY[0] = 0;
            NewOriginXY[1] = OldY-FontSize-LineGap;
            NewLineCountOut++;
        }

        if (LengthCheck<=100){
            //printf("\n\t\tNot sending to new line");
            NewOriginXY[0] = OldX;
            NewOriginXY[1] = OldY;
        }
    }

    //printf("\n\t\tNew word origin XY = %d %d",OldX,OldY);

    NewXY[0] = NewOriginXY[0];
    NewXY[1] = NewOriginXY[1];

    *PtrNewLineCountIn = NewLineCountIn;
    *PtrNewLineCountOut = NewLineCountOut;

    return 0;
}

int F_FindLetterOrigin(int PageWidth, int LineGap, int* WordArray, int LengthOfArray, int FontSize, int* NewWordStartXY, int *LetterOriginArray[], int NewLineCountOut, int NewLineCountIn){

    int i;
    int k;
    int OverspillCheck = 0;
    int SpacesCount = 0;
    int LetterStartX = NewWordStartXY[0];
    int LetterStartY = NewWordStartXY[1];

        if (NewLineCountOut>0){
        for(k=0; k<LengthOfArray; k++){
            if (WordArray[k] == 32){
                SpacesCount++;
            }
        }
    }

    if (NewLineCountIn>0){
        for (k=SpacesCount; k<LengthOfArray; k++){
            LetterOriginArray[0][k-1] = LetterStartX;
            LetterOriginArray[1][k-1] = LetterStartY;

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
    }


        for (k=SpacesCount; k<LengthOfArray; k++){
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