#include <stdio.h>
#include <stdlib.h>
#include "S_Characters.h"

int F_DisplayCharacter(Characters Character){
    int i;
    char name = Character.ascii;
    printf("\n\t\t ascii = %d ", name);
   printf("\n\t\t length = %d ",Character.length);

   printf("\n\t\t Xpos = ");
   for (i=1; i<=Character.length; i++){
        printf(" %d ",Character.Xpos[i]);
   }
   printf("\n\t\t Ypos = ");
   for (i=1; i<=Character.length; i++){
        printf(" %d ",Character.Ypos[i]);
   }
   printf("\n\t\t Pen = ");
   for (i=1; i<=Character.length; i++){
        printf(" %d ",Character.Pen[i]);
   }
   printf("\n\n");

   return 0;
}