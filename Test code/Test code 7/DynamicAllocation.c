#include <stdio.h>
#include <stdlib.h>

struct DataSet			/* Define a struture called DataSet */
{			
	int length;
    int *Xpos;
    int *Ypos;
    int *Pen;
};

void displayFunction (struct DataSet character){
   int i;
   printf("\n\t\t length = %d ",character.length);

   printf("\n\t\t Xpos = ");
   for(i=1; i<=character.length; i++){
        printf(" %d ",character.Xpos[i]);
   }
   printf("\n\t\t Ypos = ");
   for(i=1; i<=character.length; i++){
        printf(" %d ",character.Ypos[i]);
   }
   printf("\n\t\t Pen = ");
   for(i=1; i<=character.length; i++){
        printf(" %d ",character.Pen[i]);
   }
   printf("\n\n");
}

int main (void)
{
    int i;
    int j;
    int size = 5;

    int *Xpos;
    int *Ypos;
    int *Pen;

    Xpos = calloc ( size , sizeof (int));
    Ypos = calloc ( size , sizeof (int));
    Pen = calloc ( size , sizeof (int));

    if ( Xpos == NULL || Ypos == NULL || Pen == NULL)
    {
        printf ("\nMemory could not be allocated - terminating");
        return -1;  // Use minus one as we did not exit sucesfully
    }

    for(j=1; j<=size; j++){
        Xpos[j]=j;
        Ypos[j]=j;
        Pen[j]=j;
    }

    struct DataSet character;
    character.Xpos = Xpos;
    character.Ypos = Ypos;
    character.Pen = Pen;
    character.length = size;

    displayFunction (character);

    return (0);
}
