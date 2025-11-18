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
    int a;
    int b;
    int c;
    
    a = F_CountLetters("FontData.txt", &count);

    b = F_FontDataToStruct("FontData.txt", &CharacterArray, &count);

    //for(i=1; i<=count; i++){
    //    c = F_DisplayCharacter(CharacterArray[i]);
    //}

    printf("a = %d, b = %d, c = %d\n\n",a,b,c);

    return 0;
}