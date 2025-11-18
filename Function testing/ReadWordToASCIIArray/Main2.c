#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "F_ReadWordToASCIIArray.h"
#include "F_CountWords.h"

int main() {

    int *count;
    int i;
    int ReturnVal1;
    int ReturnVal2;

    ReturnVal1 = F_CountWords("test.txt", &count);

    for (i=1;i<=count;i++){
        ReturnVal2 = F_ReadWordToASCIIArray("test.txt",i);
    }

    printf("\n\nReturnVal1 = %d, ReturnVal2 = %d\n\n",ReturnVal1,ReturnVal2);

    return 0;
}