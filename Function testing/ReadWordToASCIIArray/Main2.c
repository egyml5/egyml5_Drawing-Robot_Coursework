#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "F_ReadWordToASCIIArray.h"
#include "F_CountWords.h"
#include "F_CountSkipCharacters.h"

int main() {

    int CharacterCount;
    int WordCount;
    int SkipCount = 0;
    int i = 0;
    int k = 0;
    int ReturnVal1 = 0;
    int ReturnVal2 = 0;
    int ReturnVal3 = 0;
    int *WordArray;
    int WordCharacterCount;

    ReturnVal1 = F_CountWords("test.txt", &CharacterCount, &WordCount);

    printf("\n\t\tCharacterCount = %d",CharacterCount);
    printf("\n\t\tWordCount = %d\n",WordCount);

    for (i=1;i<=WordCount;i++){

        ReturnVal2 = F_CountSkipCharacters("test.txt", i, &SkipCount);
        //printf("\n\t\tSkipCount = %d",SkipCount);

        ReturnVal3 = F_ReadWordToASCIIArray("test.txt", i, &WordArray, SkipCount, &WordCharacterCount);

        //printf("\n\t\tWordCharacterCount = %d",WordCharacterCount);

        printf("\n\t\tWordArray =");
        for (k=0;k<WordCharacterCount;k++){
            printf(" %d",WordArray[k]);
        }

    }

    printf("\n\nReturnVal1 = %d, ReturnVal2 = %d, ReturnVal3 = %d\n\n",ReturnVal1,ReturnVal2,ReturnVal3);

    return 0;
}