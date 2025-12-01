#include <stdio.h>
#include <stdlib.h>
//#include <conio.h>
//#include <windows.h>
#include "rs232.h"
#include "serial.h"
#include "F_FontDataToStruct.h"
#include "S_Characters.h"
#include "F_ReadWordToASCIIArray.h"
#include "F_WriteWordToGCodeArray.h"

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
    int FontSize = 7;
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
    int ReturnVal1;
    int ReturnVal2;
    int ReturnVal3;
    int ReturnVal4;
    int ReturnVal5;
    int ReturnVal6;
    int ReturnVal7;
    int ReturnVal8;
    int ReturnVal9;
    int ReturnVal10;
    int ReturnVal11;
    
    //Code to read, convert and store input text and font in a usable format
    ReturnVal1 = F_CountLetters("FontData.txt", &NumberOfASCIICharacters);

    ReturnVal2 = F_FontDataToStruct("FontData.txt", &CharacterArray, &NumberOfASCIICharacters);

    for(i=0; i<NumberOfASCIICharacters; i++){
        ReturnVal3 = F_ResizeStructs(FontSize, CharacterArray[i]);
    }

    for(i=0; i<NumberOfASCIICharacters; i++){
        ReturnVal4 = F_DisplayCharacter(CharacterArray[i]);
    }
    
    ReturnVal5 = F_CountWords("test.txt", &CharacterCount, &WordCount);

    //loop to read each word and convert to GCode
    //Loop calculation variables
    int SkipCount = 0;
    int *WordArray;
    int WordCharacterCount;
    int OldWordEndXY[2] = {0, -FontSize};
    int NewWordStartXY[2];
    int NewLineCount;
    int LengthOfWord;
    int *LetterOriginArray[2] = {0};
    int GCodeArrayLength;
    char *GCodeArray;

    //Loop loop variables
    int q;
    int z;
    int v;

    for (k=1;k<=WordCount;k++){

        ReturnVal6 = F_CountSkipCharacters("test.txt", k, &SkipCount);

        ReturnVal7 = F_ReadWordToASCIIArray("test.txt", k, &WordArray, SkipCount, &WordCharacterCount);

        ReturnVal8 = F_FindWordOrigin(PageWidth, LineGap, OldWordEndXY, WordArray, WordCharacterCount, FontSize, NewWordStartXY, &NewLineCount);

        LengthOfWord = WordCharacterCount-NewLineCount;
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

        ReturnVal9 = F_FindLetterOrigin(PageWidth, LineGap, WordArray, LengthOfWord, FontSize, NewWordStartXY, LetterOriginArray);

        OldWordEndXY[0] = LetterOriginArray[0][LengthOfWord-1]+FontSize;
        OldWordEndXY[1] = LetterOriginArray[1][LengthOfWord-1];

        ReturnVal10 = F_FindLengthGCodeArray(WordArray, &GCodeArrayLength, CharacterArray, WordCharacterCount, NewLineCount);
        //printf("\n\t\tGCodeArray length = %d\n",GCodeArrayLength);

        ReturnVal11 = F_WriteGCodeWordArray(WordArray, LetterOriginArray, GCodeArrayLength, CharacterArray, WordCharacterCount, NewLineCount, GCodeArray);
        
    }

    printf("\n\nRV1 = %d, RV2 = %d, RV3 = %d, RV4 = %d, RV5 = %d, RV6 = %d, RV7 = %d, RV8 = %d, RV9 = %d\n\n",ReturnVal1,ReturnVal2,ReturnVal3,ReturnVal4,ReturnVal5,ReturnVal6,ReturnVal7,ReturnVal8,ReturnVal9);

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
