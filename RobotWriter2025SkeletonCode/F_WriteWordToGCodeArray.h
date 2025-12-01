#ifndef F_WriteWordToGCodeArray_h
#define F_WriteWordToGCodeArray_h
#include "S_Characters.h"

int F_FindLengthGCodeArray(int *WordArray, int *ptrGCodeArrayLength, Characters *CharacterArray, int WordCharacterCount, int NewLineCount);
int F_WriteGCodeWordArray(int *WordArray, int **LetterOriginArray, int GCodeArrayLength, Characters *CharacterArray, int WordCharacterCount, int NewLineCount, char *GCodeArray);

#endif