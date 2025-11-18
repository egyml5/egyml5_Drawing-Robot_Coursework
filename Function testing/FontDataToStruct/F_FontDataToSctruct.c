#include <stdio.h>
#include <stdlib.h>
#include "S_Characters.h"

int F_FontDataToStruct(char* FontData, Characters **ReturnArray, int *count){

    int check;
    int ascii;
    int length;
    int NumberOfCharacters = *count;
    int i;
    int ii;
    struct Characters *CharacterArray;
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
    if ( fInput == NULL)
    {
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

        char c = CharacterArray[ii].ascii;
        printf("\n\n\t\t ascii = %c", c);
        printf("\n\t\t length = %d ",CharacterArray[ii].length);

        if (length =! 0){
            Xpos = calloc ( length , sizeof (int));
            Ypos = calloc ( length , sizeof (int));
            Pen = calloc ( length , sizeof (int));

            if ( Xpos == NULL || Ypos == NULL || Pen == NULL){
                printf ("\nMemory could not be allocated - terminating");
                return -1;  // Use minus one as we did not exit sucesfully
            }

            for (i=1; i<=length; i++){
                fscanf (fInput, "%d %d %d", &Xpos[i], &Ypos[i], &Pen[i]);

                if (EndCheck == EOF){
                    printf("EOF");
                    break;
                }
            }
        }

        printf("\n\t\t Xpos =");
        for(i=1; i<=length; i++){
            printf(" %d",Xpos[i]);
        }
        printf("\n\t\t Ypos =");
        for(i=1; i<=length; i++){
            printf(" %d",Ypos[i]);
        }
        printf("\n\t\t Pen =");
        for(i=1; i<=length; i++){
            printf(" %d",Pen[i]);
        }


        CharacterArray[ii].Xpos = Xpos;
        CharacterArray[ii].Ypos = Ypos;
        CharacterArray[ii].Pen = Pen;
    }

    *ReturnArray = CharacterArray;
    return 0;
}