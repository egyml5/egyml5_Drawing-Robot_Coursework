#include <stdio.h>
#include <stdlib.h>

// Main () - execution starts here
int main (void)
{
    // Declare file stream variables
    FILE *fInput, *fOutput;

    // Other variables needed
    int i,d;

    // Try and open the text "sample.txt" (in the current directory) file for writing
    fOutput = fopen ("numbers.txt", "w");

    // Check we were able to open the file
    if ( fOutput == NULL)
    {
        printf ("\nthe file could not be opened for writing, exiting");
        return -1;
    }

    // Use a loop to write values to the newly created file
    for ( i = 1 ; i <= 10 ; i++)
    {
        fprintf (fOutput, "%d", i);
        fprintf (fOutput, " ");
    }

    // And close the file
    fclose (fOutput);

    return (0);     // Exit indicating success
}