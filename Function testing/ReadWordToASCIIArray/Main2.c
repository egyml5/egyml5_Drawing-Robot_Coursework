#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "F_ReadWordToASCIIArray.h"
#include "F_CountWords.h"

int main() {

    int CharacterCount;
    int WordCount;
    int i = 0;
    int ReturnVal1 = 0;
    int ReturnVal2 = 0;

    ReturnVal1 = F_CountWords("test.txt", &CharacterCount, &WordCount);

    printf("\n\t\tCharacterCount = %d",CharacterCount);
    printf("\n\t\tWordCount = %d",WordCount);

    //for (i=1;i<=count;i++){
    //   ReturnVal2 = F_ReadWordToASCIIArray("test.txt",i);
    //}

    printf("\n\nReturnVal1 = %d, ReturnVal2 = %d\n\n",ReturnVal1,ReturnVal2);

    return 0;
}