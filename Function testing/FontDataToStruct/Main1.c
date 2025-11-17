#include <stdio.h>
#include <stdlib.h>
#include "F_FontDataToStruct.h"
#include "F_CountLetters.h"
#include "S_Characters.h"


int main () {
    Characters *Goeffrey;
    int count;
    int a;
    int b;
    
    a = F_CountLetters("FontData.txt", &count);

    b = F_FontDataToStruct("FontData.txt", &Goeffrey, &count);

    printf("a = %d, b = %d\n\n",a,b);

    return 0;
}