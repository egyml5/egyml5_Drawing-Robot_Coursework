#include <stdio.h>
#include <stdlib.h>
#include "F_FontDataToStruct.h"
#include "F_CountLetters.h"
#include "F_DisplayCharacter.h"
#include "S_Characters.h"

int main () {
    Characters *CharacterArray;
    int count;
    int i;
    int ReturnVal1;
    int ReturnVal2;
    int ReturnVal3;
    
    ReturnVal1 = F_CountLetters("FontData.txt", &count);

    ReturnVal2 = F_FontDataToStruct("FontData.txt", &CharacterArray, &count);

    for(i=0; i<count; i++){
        ReturnVal3 = F_DisplayCharacter(CharacterArray[i]);
    }

    printf("\n\nReturnVal1 = %d, ReturnVal2 = %d, ReturnVal3 = %d\n\n",ReturnVal1,ReturnVal2,ReturnVal3);

    return 0;
}