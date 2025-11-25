#include <stdio.h>
#include <stdlib.h>
#include "F_CountLetters.h"

int F_CountLetters(char* FontData, int *count){

    int check;
    int ascii;
    int length;
    int ignore;
    int EndCheck;
    int NumberOfCharacters = 0;
    int i;
    int end = 0;

    FILE *fInput;
    fInput = fopen (FontData, "r");

    if ( fInput == NULL)
    {
        printf ("\nthe file could not be opened for reading, exiting");
        return -1;
    }

    while (1) {
        EndCheck = fscanf (fInput, "%d %d %d", &check, &ascii, &length);

        //printf("check = %d, ascii = %d, length = %d\n",check, ascii, length);

        if (EndCheck == EOF){
            break;
        }
        if (check == 999){
            NumberOfCharacters++;
        }

        for (i=1; i<=length; i++){
            EndCheck = fscanf (fInput, "%d %d %d", &ignore, &ignore, &ignore);

            if (EndCheck == EOF){
                break;
            }
        }
        
    }
    fclose (fInput);

    *count = NumberOfCharacters;

    printf("\n\nCount = %d\n\n",*count);

    return 0;
}