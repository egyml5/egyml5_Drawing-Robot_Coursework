#include <stdio.h>
#include <stdlib.h>
#include "S_Characters.h"
#include "F_FontDataToStruct.h"

int F_CountLetters(char* FontData, int *count){
    /*
    Function is sent the name of the font data text file. It opens the file and counts how many characters the file has data for.
    It then sends this number to the pointer “count”
    */

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

        if (check != 999){
            printf("\nFont data incorrectly formatted");
            return -1;
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

    //printf("\n\nCount = %d\n\n",*count);

    return 0;
}

int F_FontDataToStruct(char* FontData, Characters **ReturnArray, int count){
    /*
    Function is sent the name of the font data text file and the number of characters “count”.
    It reads the font data for each character into X position, Y position and Pen position arrays and stores
    these arrays in a struct with the length of the arrays “length” and the ASCII code for each character “ascii”.
    These structs are then put in an array and sent to the **ReturnArray
    */

    int check = 0;
    int ascii = 0;
    int length = 0;
    int NumberOfCharacters = count;
    int i;
    int ii;
    struct Characters *CharacterArray;
    float XVal = 0;
    float YVal = 0;
    int PenVal = 0;
    float *Xpos;
    float *Ypos;
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
            Xpos = calloc ( length , sizeof (float));
            Ypos = calloc ( length , sizeof (float));
            Pen = calloc ( length , sizeof (int));

            if ( Xpos == NULL || Ypos == NULL || Pen == NULL){
                printf ("\nMemory could not be allocated - terminating");
                return -1;  // Use minus one as we did not exit sucesfully
            }

            for (i=0; i<length; i++){
                fscanf (fInput, "%f %f %d", &XVal, &YVal, &PenVal);

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

int F_ResizeStructs(int FontSize, Characters Character){
    /*
    Function resizes the font data for the character it is sent
    */

    int i;
    int length;
    float OldX;
    float OldY;
    float NewX;
    float NewY;

    length = Character.length;


    for(i=0; i<length; i++){
        OldX = Character.Xpos[i];
        //printf("\n\t\tOldX = %f",OldX);
        NewX = (float)OldX*((float)FontSize/(float)18);
        //printf("\n\t\tNewX = %f",NewX);
        Character.Xpos[i] = NewX;
    }

    for(i=0; i<length; i++){
        OldY = Character.Ypos[i];
        //printf("\n\t\tOldY = %f",OldY);
        NewY = (float)OldY*((float)FontSize/(float)18);
        //printf("\n\t\tNewY = %f",NewY);
        Character.Ypos[i] = NewY;
    }

    return 0;
}

int F_DisplayCharacter(Characters Character){
    /*
    Funtion to print the data in a struct for diagnostic purposes
    */

     int i;
     char name = Character.ascii;
     printf("\n\t\t ascii int = %d ", Character.ascii);
     printf("\n\t\t ascii char = %c ", name);
     printf("\n\t\t length = %d ",Character.length);

     printf("\n\t\t Xpos = ");
     for (i=0; i<Character.length; i++){
        printf(" %.2f ",Character.Xpos[i]);
     }
     printf("\n\t\t Ypos = ");
     for (i=0; i<Character.length; i++){
        printf(" %.2f ",Character.Ypos[i]);
     }
     printf("\n\t\t Pen = ");
     for (i=0; i<Character.length; i++){
        printf(" %d ",Character.Pen[i]);
     }
     printf("\n\n");

     return 0;
}