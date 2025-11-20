#include <stdio.h>
#include <stdlib.h>
#include "F_FontDataToStruct.h"
#include "F_CountLetters.h"
#include "F_DisplayCharacter.h"
#include "S_Characters.h"
#include "F_ResizeStructs.h"

int main () {
    Characters *CharacterArray;
    int count;
    int i;
    int ReturnVal1;
    int ReturnVal2;
    int ReturnVal3;
    int ReturnVal4;
    int FontSize = 10;
    
    ReturnVal1 = F_CountLetters("FontData.txt", &count);

    ReturnVal2 = F_FontDataToStruct("FontData.txt", &CharacterArray, &count);

    for(i=0; i<count; i++){
        ReturnVal3 = F_ResizeStructs(FontSize, CharacterArray[i]);
    }

    for(i=0; i<count; i++){
        ReturnVal4 = F_DisplayCharacter(CharacterArray[i]);
    }

    printf("\n\nReturnVal1 = %d, ReturnVal2 = %d, ReturnVal3 = %d, ReturnVal4 = %d\n\n",ReturnVal1,ReturnVal2,ReturnVal3,ReturnVal4);

    return 0;
}