#include <stdio.h>
#include <stdlib.h>
#include "S_Characters.h"

int F_FontDataToStruct(char* FontData, Characters **Goeffrey, int *count){

    int check;
    int ascii;
    int length;
    int ignore;
    int EndCheck;
    int NumberOfCharacters = &count;
    int i;
    int ii;
    int end = 0;
    struct Characters *CharacterArray;
    int *Xpos;
    int *Ypos;
    int *Pen;

    FILE *fInput;
    fInput = fopen (FontData, "r");
    if ( fInput == NULL)
    {
        printf ("\nthe file could not be opened for reading, exiting");
        return -1;
    }

    while (end == 0) {
        EndCheck = fscanf (fInput, "%d %d %d", &check, &ascii, &length);

        printf("check = %d, ascii = %d, length = %d\n",check, ascii, length);

        if (EndCheck == EOF){
            break;
        }
        if (check == 999){
            count++;
        }

        for (i=1; i<=length; i++){
            fscanf (fInput, "%d %d %d", &ignore, &ignore, &ignore);

            if (EndCheck == EOF){
                break;
            }
        }
        
    }
    fclose (fInput);

    printf("count = %d\n",count);

    CharacterArray = calloc ( count , sizeof(struct Characters));
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

    for (ii=1; ii<=NumberOfCharacters; ii++){
        fscanf (fInput, "%d %d %d", &check, &ascii, &length);

        CharacterArray[NumberOfCharacters].ascii = ascii;
        CharacterArray[NumberOfCharacters].length = length;

        Xpos = calloc ( length , sizeof (int));
        Ypos = calloc ( length , sizeof (int));
        Pen = calloc ( length , sizeof (int));

        if ( Xpos == NULL || Ypos == NULL || Pen == NULL){
            printf ("\nMemory could not be allocated - terminating");
            return -1;  // Use minus one as we did not exit sucesfully
        }

        for (i=1; i<=length; i++){
            fscanf (fInput, "%d %d %d", Xpos[i], Ypos[i], Pen[i]);
        }

        CharacterArray[NumberOfCharacters].Xpos = Xpos;
        CharacterArray[NumberOfCharacters].Ypos = Ypos;
        CharacterArray[NumberOfCharacters].Pen = Pen;
    }

    *Goeffrey = CharacterArray;
    return 0;
}