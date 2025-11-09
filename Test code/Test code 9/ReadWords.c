#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    
    // Character that store the read
    // character
    char ch;
    int ASCII = 0;
    int wordLength = -1;
    int i;
    int wordArray[50];
    int *word;

    // Opening file in reading mode
    FILE *fptr = fopen("InputText.txt", "r");

    while (ASCII != 32){
        wordLength++;
        ch = fgetc(fptr);
        ASCII = (int)ch;
    }
    fclose(fptr);

    word = calloc ( wordLength , sizeof (int));
    if ( word == NULL)
    {
        printf ("\nMemory could not be allocated - terminating");
        return -1;  // Use minus one as we did not exit sucesfully
    }

    FILE *fptr2 = fopen("InputText.txt", "r");
    
    printf("Word array = ");

    for(i=1; i<=wordLength; i++){
        word[i] = (int)fgetc(fptr2);
        printf("%d " ,word[i]);
    }
    printf("\n\n");

    fclose(fptr2);
    return 0;
}