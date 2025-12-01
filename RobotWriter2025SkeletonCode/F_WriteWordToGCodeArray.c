#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "S_Characters.h"
#include "F_WriteWordToGCodeArray.h"

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

int F_WriteGCodeWordArray(int *WordArray, int **LetterOriginArray, int GCodeArrayLength, Characters *CharacterArray, int WordCharacterCount, int NewLineCount, char *ptrGCodeArray){

    int i;
    int q;
    int z;
    int w;
    int JaggedLength[GCodeArrayLength];
    int StringLength;
    int RowNumber = 0;
    float *XArray;
    float *YArray;
    int *PenArray;
    int LetterASCII;
    int LetterLength;
    int OldPen = 0;
    float XPos;
    float YPos;
    int Pen;
    char XString[9];
    char YString[9];
    char PenString[1];

    char buffer[100];

    // makes an array the length of GCodeArrayLength with each element a pointer
    char **GCodeArray = calloc(GCodeArrayLength, sizeof(char*));
    if(GCodeArray == NULL){
            printf("\nMemory could not be allocated - terminating\n");
            return -1;
    }
    
    //Runs through each row of GCodeArray and fills with strings
    for (i=NewLineCount;i<WordCharacterCount;i++){

        LetterASCII = WordArray[i];

        LetterLength = CharacterArray[LetterASCII].length;
        XArray = CharacterArray[LetterASCII].Xpos;
        YArray = CharacterArray[LetterASCII].Ypos;
        PenArray = CharacterArray[LetterASCII].Pen;

        // finds the length of each element of the jagged GCode array
        for(q=0;q<LetterLength;q++){
            if(PenArray[q] > OldPen){
                //S1000\n
                JaggedLength[RowNumber] = 7;
                GCodeArray[RowNumber] = calloc(7, sizeof(char));
                strcpy(GCodeArray[RowNumber], "S1000\n");
                printf("%s",GCodeArray[RowNumber]);

                sprintf (buffer, GCodeArray[RowNumber]);
                SendCommands(buffer);

                RowNumber++;
            }

            if(PenArray[q] < OldPen){
                //S0\n
                JaggedLength[RowNumber] = 4;
                GCodeArray[RowNumber] = calloc(4, sizeof(char));
                strcpy(GCodeArray[RowNumber], "S0\n");
                printf("%s",GCodeArray[RowNumber]);

                sprintf (buffer, GCodeArray[RowNumber]);
                SendCommands(buffer);

                RowNumber++;
            }

            if(PenArray[q] == OldPen){
                //Nothing
                RowNumber = RowNumber;
            }

            //G X Y \n
            JaggedLength[RowNumber] = 25;
            XPos = XArray[q] + LetterOriginArray[0][i];
            YPos = YArray[q] + LetterOriginArray[1][i];
            Pen = PenArray[q];

            GCodeArray[RowNumber] = calloc(30, sizeof(char));
            snprintf(GCodeArray[RowNumber], 30, "G%d X%.2f Y%.2f\n",Pen,XPos,YPos);
            printf("%s",GCodeArray[RowNumber]);

            sprintf (buffer, GCodeArray[RowNumber]);
            SendCommands(buffer);

            RowNumber++;
            OldPen = PenArray[q];
        }

    }
    *ptrGCodeArray = **GCodeArray;

    return 0;
}