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

int FontToGCode (struct DataSet character, int *Array){
    int i;
    int j=1;
    for(i=1; i<=character.length; i++){
        Array[j] = character.Pen[i];
        j++;
        Array[j] = character.Xpos[i];
        j++;
        Array[j] = character.Ypos[i];
        j++;
    }
    return (0);
}

int main (void)
{
    int j;
    int q;
    int i;
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
        Pen[j]=1;
    }

    struct DataSet character;
    character.Xpos = Xpos;
    character.Ypos = Ypos;
    character.Pen = Pen;
    character.length = size;

    displayFunction (character);

    q = size*3;
    int Array[q];
    int retVal;

    retVal = FontToGCode (character, Array);

    printf("\nG-Code Array");
    for(i=1; i<=q; i++){
        printf("\n %d",Array[i]);
    }
    
    return (0);     // Exit indicating success
}