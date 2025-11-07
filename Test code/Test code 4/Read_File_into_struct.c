#include <stdio.h>
#include <stdlib.h>

struct DataSet			/* Define a struture called DataSet */
{
	int ascii;			/* The X data */
	int length;
    int *Xpos;
    int *Ypos;
    int *Pen;
};

void displayFunction (struct DataSet character){
   int i;
   char c = character.ascii;
   printf("\n\t\t ascii = %c ", c);
   printf("\n\t\t length = %d ",character.length);

   printf("\n\t\t Xpos = ");
   for (i=1; i<=character.length; i++){
        printf(" %d ",character.Xpos[i]);
   }
   printf("\n\t\t Ypos = ");
   for (i=1; i<=character.length; i++){
        printf(" %d ",character.Ypos[i]);
   }
   printf("\n\t\t Pen = ");
   for (i=1; i<=character.length; i++){
        printf(" %d ",character.Pen[i]);
   }
   printf("\n\n");
}

// Main () - execution starts here
int main (void)
{
    // Declare file stream variables
    FILE *fInput;

    // Other variables needed
    int a=0;
    int b=0;
    int c=0;
    int d=0;
    int e=0;
    int z=0;
    int i=0;
    int q=0;
    int ii=0;
    int *Xpos;
    int *Ypos;
    int *Pen;

    // Try and open the binary "numbers " (in the current directory) file for reading

    fInput = fopen ("FontData.txt", "r");

    // Check we were able to open the file
    if ( fInput == NULL)
    {
        printf ("\nthe file could not be opened for reading, exiting");
        return -1;
    }
 
    fscanf (fInput, "%d", &q);

    for (ii=1; ii<=q; ii++){
        
        fscanf (fInput, "%d", &z);
        if (z ==999){
            fscanf (fInput, "%d", &a);
            struct DataSet character[a];
            fscanf (fInput, "%d", &b);
            character[a].ascii = a;
            character[a].length = b;

            Xpos = calloc ( b , sizeof (int));
            Ypos = calloc ( b , sizeof (int));
            Pen = calloc ( b , sizeof (int));

            if ( Xpos == NULL || Ypos == NULL || Pen == NULL){
                printf ("\nMemory could not be allocated - terminating");
                return -1;  // Use minus one as we did not exit sucesfully
            }

            for (i=1; i<=b; i++){
                fscanf (fInput, "%d", &c);
                fscanf (fInput, "%d", &d);
                fscanf (fInput, "%d", &e);
                if(c!=999){
                    Xpos[i] = c;
                    Ypos[i] = d;
                    Pen[i] = e;
                }
                else{
                    printf ("\ntxt file improperly formatted\n\n");
                }
            }
            character[a].Xpos = Xpos;
            character[a].Ypos = Ypos;
            character[a].Pen = Pen;
            displayFunction (character[a]);
        }
        else{
            printf ("\ntxt file improperly formatted\n\n");
        }
    }

    // And close the file
    fclose (fInput);

    return (0);     // Exit indicating success
}