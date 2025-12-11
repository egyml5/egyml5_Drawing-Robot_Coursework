#ifndef F_ReadWordoASCIIArray_h
#define F_ReadWordoASCIIArray_h
#include "S_Characters.h"

int F_CountSkipCharacters(char* InputText, int Word, int *SkipCount);
int F_CountWords(char* InputText, int *WordCount);
int F_ReadWordToASCIIArray(char* InputText, int Word, int **WordArray, int SkipCount, int *WordCharacterCount);
int F_FindWordOrigin(int PageWidth, int LineGap, int* OldWordEndXY, int* WordArray, int LengthArray, int FontSize, int *NewXY,int *PtrNewLineCountIn, int *PtrNewLineCountOut);
int F_FindLetterOrigin(int PageWidth, int LineGap, int* WordArray, int LengthOfArray, int FontSize, int *NewWordStartXY, int *LetterOriginArray[], int NewLineCountOut, int NewLineCountIn);

#endif