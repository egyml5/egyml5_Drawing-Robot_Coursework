#ifndef F_FontDataToStruct_h
#define F_FontDataToStruct_h
#include "S_Characters.h"

int F_CountLetters(char* FontData, int *count);
int F_FontDataToStruct(char* FontData, Characters **Goeffrey, int *count);
int F_ResizeStructs(int FontSize, Characters Character);
int F_DisplayCharacter(Characters Character);

#endif