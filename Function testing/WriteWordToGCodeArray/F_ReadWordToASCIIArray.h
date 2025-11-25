#ifndef F_ReadWordoASCIIArray_h
#define F_ReadWordoASCIIArray_h

int F_CountSkipCharacters(char* InputText, int Word, int *SkipCount);
int F_CountWords(char* InputText, int *CharacterCount, int *WordCount);
int F_ReadWordToASCIIArray(char* InputText, int Word, int **WordArray, int SkipCount, int *WordCharacterCount);

#endif