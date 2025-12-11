#include <stdio.h>
#include <stdlib.h>
#include "F_ReadWordToASCIIArray.h"

int F_CountSkipCharacters(char* InputText, int Word, int *SkipCount){
    /*
    counts the number of characters before the word being read
    */

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

int F_CountWords(char* InputText, int *WordCount){
    /*
    opens the input text file and counts the number of words. A word is defined as some text (not ASCII 32 or 10)
    bookended by a space, newline, start of file or end of file
    */

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
    
    *WordCount = NumberOfWords;

    return 0;
}

int F_ReadWordToASCIIArray(char* InputText, int Word, int **WordArray, int SkipCount, int *WordCharacterCount){
    /*
    Function opens the input text file and skips over the characters before the word.
    It then reads each character of the word into an array
    */

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

    *WordArray = ASCIIArray;
    *WordCharacterCount = CharacterCount;
    
    return 0;
}

int F_FindWordOrigin(int PageWidth, int LineGap, int* OldWordEndXY, int* WordArray, int LengthWordArray, int FontSize, int* NewXY, int *PtrNewLineCountIn, int *PtrNewLineCountOut){
    /*
    Function decides where the word origin is. If the word starts with a newline (ASCII 10) it send the word to a newline.
    If not it checks if the word will overspill the page and if so sends it to a new line. If not it sets NewXY = OldWordEndXY
    */

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
    
    if(NewLineCountIn>0){
        //printf("\n\t\tSending to new line");
        NewOriginXY[0] = 0;
        NewOriginXY[1] = OldY-((FontSize+LineGap)*NewLineCountIn);
    }
    

    if(NewLineCountIn == 0){
        LengthCheck = (FontSize*LengthWordArray)+OldX;
        //printf("\n\t\tLengthCheck = %d",LengthCheck);

        if (LengthCheck>100 && OldX>0){
            //printf("\n\t\tSending to new line");
            NewOriginXY[0] = 0;
            NewOriginXY[1] = OldY-FontSize-LineGap;
            NewLineCountOut++;
        }

        if (LengthCheck>100 && OldX==0){
            //printf("\n\t\tSending to new line");
            NewOriginXY[0] = OldX;
            NewOriginXY[1] = OldY;
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
    /*
    Makes an array containing the X and Y for the origin of each letter in the word
    */

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
    
        SpacesCount = SpacesCount+NewLineCountIn;

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