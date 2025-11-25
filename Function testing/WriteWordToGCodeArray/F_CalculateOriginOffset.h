#ifndef F_CalculateOriginOffset_h
#define F_CalculateOriginOffset_h

int F_FindWordOrigin(int PageWidth, int LineGap, int* OldWordEndXY, int* WordArray, int LengthArray, int FontSize, int *NewXY,int *PtrNewLineCount);
int F_FindLetterOrigin(int PageWidth, int LineGap, int* WordArray, int LengthOfArray, int FontSize, int *NewWordStartXY, int *LetterOriginArray[]);

#endif