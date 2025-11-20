#include <stdio.h>
#include <stdlib.h>

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