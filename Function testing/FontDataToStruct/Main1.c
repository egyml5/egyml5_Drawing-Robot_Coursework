#include <stdio.h>
#include <stdlib.h>
#include "F_FontDataToStruct.h"
#include "S_Characters.h"


int main () {
    Characters *Goeffrey;
    int count;
    
    F_CountLetters("FontData.txt", &count);
    F_FontDataToStruct("FontData.txt", &Goeffrey, &count);
}