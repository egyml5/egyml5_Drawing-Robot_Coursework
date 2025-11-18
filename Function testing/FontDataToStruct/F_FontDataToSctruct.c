#include <stdio.h>
#include <stdlib.h>
#include "S_Characters.h"

int F_FontDataToStruct(char* FontData, Characters **ReturnArray, int *count){

    int check = 0;
    int ascii = 0;
    int length = 0;
    int NumberOfCharacters = *count;
    int i;
    int ii;
    struct Characters *CharacterArray;
    int XVal = 0;
    int YVal = 0;
    int PenVal = 0;
    int *Xpos;
    int *Ypos;
    int *Pen;
    int EndCheck;

    FILE *fInput;
    CharacterArray = calloc ( NumberOfCharacters , sizeof(struct Characters));
    if ( CharacterArray == NULL){
        printf ("\nMemory could not be allocated - terminating\n");
        return -1;  // Use minus one as we did not exit sucesfully
    }

    fInput = fopen (FontData, "r");
    if ( fInput == NULL){
        printf ("\nthe file could not be opened for reading, exiting");
        return -1;
    }

    for (ii=0; ii<NumberOfCharacters; ii++){

        EndCheck = fscanf (fInput, "%d %d %d", &check, &ascii, &length);

        if (EndCheck == EOF){
            printf("EOF");
            break;
        }

        CharacterArray[ii].ascii = ascii;
        CharacterArray[ii].length = length;

        if (length > 0){
            Xpos = calloc ( length , sizeof (int));
            Ypos = calloc ( length , sizeof (int));
            Pen = calloc ( length , sizeof (int));

            if ( Xpos == NULL || Ypos == NULL || Pen == NULL){
                printf ("\nMemory could not be allocated - terminating");
                return -1;  // Use minus one as we did not exit sucesfully
            }

            for (i=0; i<length; i++){
                fscanf (fInput, "%d %d %d", &XVal, &YVal, &PenVal);

                Xpos[i] = XVal;
                Ypos[i] = YVal;
                Pen[i] = PenVal;

                if (EndCheck == EOF){
                    printf("EOF");
                    break;
                }
            }

            CharacterArray[ii].Xpos = Xpos;
            CharacterArray[ii].Ypos = Ypos;
            CharacterArray[ii].Pen = Pen;
            
        }
    }

    free(Xpos);
    free(Ypos);
    free(Pen);

    *ReturnArray = CharacterArray;
    return 0;
}