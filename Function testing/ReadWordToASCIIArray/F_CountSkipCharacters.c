#include <stdio.h>
#include <stdlib.h>

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