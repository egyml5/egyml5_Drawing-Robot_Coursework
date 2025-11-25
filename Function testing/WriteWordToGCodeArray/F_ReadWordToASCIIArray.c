#include <stdio.h>
#include <stdlib.h>
#include "F_ReadWordToASCIIArray.h"

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