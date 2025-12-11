#include <stdio.h>
#include <stdlib.h>
//#include <conio.h>
//#include <windows.h>
#include "rs232.h"
#include "serial.h"
#include "F_FontDataToStruct.h"
#include "S_Characters.h"
#include "F_ReadWordToASCIIArray.h"

#define bdrate 115200               /* 115200 baud */

void SendCommands (char *buffer );

int main()
{

    //char mode[]= {'8','N','1',0};
    char buffer[100];

    // If we cannot open the port then give up immediately
    if ( CanRS232PortBeOpened() == -1 )
    {
        printf ("\nUnable to open the COM port (specified in serial.h) ");
        exit (0);
    }

    // Time to wake up the robot
    printf ("\nAbout to wake up the robot\n");

    // We do this by sending a new-line
    sprintf (buffer, "\n");
     // printf ("Buffer to send: %s", buffer); // For diagnostic purposes only, normally comment out
    PrintBuffer (&buffer[0]);
    Sleep(100);

    // This is a special case - we wait  until we see a dollar ($)
    WaitForDollar();

    printf ("\nThe robot is now ready to draw\n");

        //These commands get the robot into 'ready to draw mode' and need to be sent before any writing commands
    sprintf (buffer, "G1 X0 Y0 F1000\n");
    SendCommands(buffer);
    sprintf (buffer, "M3\n");
    SendCommands(buffer);
    sprintf (buffer, "S0\n");
    SendCommands(buffer);

//Input values
    int FontSize;
    int PageWidth = 100;
    int LineGap = 5;
    
    //Calculation variables
    Characters *CharacterArray;
    int NumberOfASCIICharacters;
    int CharacterCount;
    int WordCount;

    //Loop Variables
    int i;
    int k;

    //Return Values
    int ReturnVal1 = 0;
    int ReturnVal2 = 0;
    int ReturnVal3 = 0;
    int ReturnVal4 = 0;
    int ReturnVal5 = 0;
    int ReturnVal6 = 0;
    int ReturnVal7 = 0;
    int ReturnVal8 = 0;
    int ReturnVal9 = 0;

    while (1){
        printf ("Please enter a fontsize between 4 and 10\n");
        scanf ("%d",&FontSize);

        if (FontSize<=10 && FontSize>=4){
            break;
        }
        printf ("Fontsize outside permissable range, Please enter a different value\n");
    }

    printf ("The value you entered for fontSize is %d\n", FontSize);
    
    //Code to read, convert and store input text and font in a usable format
    ReturnVal1 = F_CountLetters("FontData.txt", &NumberOfASCIICharacters);

    ReturnVal2 = F_FontDataToStruct("FontData.txt", &CharacterArray, &NumberOfASCIICharacters);

    for(i=0; i<NumberOfASCIICharacters; i++){
        ReturnVal3 = F_ResizeStructs(FontSize, CharacterArray[i]);
    }

    /*
    for(i=0; i<NumberOfASCIICharacters; i++){
        ReturnVal4 = F_DisplayCharacter(CharacterArray[i]);
    }
    */
    
    ReturnVal5 = F_CountWords("InputText.txt", &CharacterCount, &WordCount);

    //loop to read each word and convert to GCode
    //Loop calculation variables
    int SkipCount = 0;
    int *WordArray;
    int WordCharacterCount;
    int OldWordEndXY[2] = {0, -FontSize};
    int NewWordStartXY[2];
    int NewLineCountIn;
    int NewLineCountOut;
    int LengthOfWord;
    int *LetterOriginArray[2] = {0};
    int GCodeArrayLength;
    char *GCodeArray;
    int OldPen = 0;
    float *XArray;
    float *YArray;
    int *PenArray;
    int LetterASCII;
    int LetterLength;
    float XPos;
    float YPos;
    int Pen;

    //Loop loop variables
    int q;
    int z;
    int v;

    for (k=1;k<=WordCount;k++){

        ReturnVal6 = F_CountSkipCharacters("InputText.txt", k, &SkipCount);

        ReturnVal7 = F_ReadWordToASCIIArray("InputText.txt", k, &WordArray, SkipCount, &WordCharacterCount);

        ReturnVal8 = F_FindWordOrigin(PageWidth, LineGap, OldWordEndXY, WordArray, WordCharacterCount, FontSize, NewWordStartXY, &NewLineCountIn, &NewLineCountOut);

        LengthOfWord = WordCharacterCount-NewLineCountIn;
        LetterOriginArray[0] = calloc ( LengthOfWord, sizeof(int));
        if ( LetterOriginArray[0] == NULL){
            printf ("\nMemory could not be allocated - terminating\n");
            return -1;
        }
        LetterOriginArray[1] = calloc ( LengthOfWord, sizeof(int));
        if ( LetterOriginArray[1] == NULL){
            printf ("\nMemory could not be allocated - terminating\n");
            return -1;
        }

        ReturnVal9 = F_FindLetterOrigin(PageWidth, LineGap, WordArray, LengthOfWord, FontSize, NewWordStartXY, LetterOriginArray, NewLineCountOut, NewLineCountIn);

        /*
        printf("\n\t\tNew Word Origin XY = %d %d",NewWordStartXY[0],NewWordStartXY[1]);
        printf("\n\t\tNewLineCountIn = %d",NewLineCountIn);
        printf("\n\t\tNewLineCountOut = %d",NewLineCountOut);
        printf("\n\t\tWordArray =");
        for (q=0;q<WordCharacterCount;q++){
            printf(" %d",WordArray[q]);
        }
        for (q=0; q<LengthOfWord; q++){
        printf("\n\t\tLetter %d XY =  %d %d",(q+NewLineCountIn+1),LetterOriginArray[0][q],LetterOriginArray[1][q]);
        }
        printf("\n");
        */

        OldWordEndXY[0] = LetterOriginArray[0][LengthOfWord-1]+FontSize;
        OldWordEndXY[1] = LetterOriginArray[1][LengthOfWord-1];
        
        OldPen = 0;

        for (i=NewLineCountIn;i<WordCharacterCount;i++){

            LetterASCII = WordArray[i];

            LetterLength = CharacterArray[LetterASCII].length;
            XArray = CharacterArray[LetterASCII].Xpos;
            YArray = CharacterArray[LetterASCII].Ypos;
            PenArray = CharacterArray[LetterASCII].Pen;

            // finds the length of each element of the jagged GCode array
            for(q=0;q<LetterLength;q++){
                if(PenArray[q] > OldPen){
                    //printf("S1000\n");
                    sprintf (buffer, "S1000\n");
                    SendCommands(buffer);
                }

                if(PenArray[q] < OldPen){
                    //printf("S0\n");
                    sprintf (buffer, "S0\n");
                    SendCommands(buffer);
                }

                //G X Y \n
                XPos = XArray[q] + LetterOriginArray[0][i];
                YPos = YArray[q] + LetterOriginArray[1][i];
                Pen = PenArray[q];

                //printf("G%d X%.2f Y%.2f\n",Pen,XPos,YPos);
                sprintf (buffer, "G%d X%.2f Y%.2f\n",Pen,XPos,YPos);
                SendCommands(buffer);

                OldPen = PenArray[q];
            }

        }

    }

    // Before we exit the program we need to close the COM port
    CloseRS232Port();
    printf("Com port now closed\n");

    return (0);
}

// Send the data to the robot - note in 'PC' mode you need to hit space twice
// as the dummy 'WaitForReply' has a getch() within the function.
void SendCommands (char *buffer )
{
    // printf ("Buffer to send: %s", buffer); // For diagnostic purposes only, normally comment out
    PrintBuffer (&buffer[0]);
    WaitForReply();
    Sleep(100); // Can omit this when using the writing robot but has minimal effect
    // getch(); // Omit this once basic testing with emulator has taken place
}
