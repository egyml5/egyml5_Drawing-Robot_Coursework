#include <stdio.h>
#include <stdlib.h>
#include "S_Characters.h"
#include "F_DisplayCharacter.h"

int F_DisplayCharacter(Characters Character){
     int i;
     char name = Character.ascii;
     printf("\n\t\t ascii = %c ", name);
     printf("\n\t\t length = %d ",Character.length);

     printf("\n\t\t Xpos = ");
     for (i=0; i<Character.length; i++){
        printf(" %.2f ",Character.Xpos[i]);
     }
     printf("\n\t\t Ypos = ");
     for (i=0; i<Character.length; i++){
        printf(" %.2f ",Character.Ypos[i]);
     }
     printf("\n\t\t Pen = ");
     for (i=0; i<Character.length; i++){
        printf(" %d ",Character.Pen[i]);
     }
     printf("\n\n");

     return 0;
}