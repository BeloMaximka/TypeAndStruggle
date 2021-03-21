#include <string.h>

// Выделяет память под указанное количество елементов (по умолчанию 1)
// и заполняет первый елемент символом с кодом 0, после чего возращает адрес на выделенную память
char* StrInit(int Size = 1) {
	char* StrPtr = new char[Size];
	StrPtr[0] = '\0';
	return StrPtr;
}

// Добавляет символ к строке на определённый индекс
void StrAddC(char*& StringPtr, const char Element, const int Index) {
	char* StringPtrSecond;
	int StringPtrSecondSize = strlen(StringPtr) + 2;
	StringPtrSecond = new char[StringPtrSecondSize];
	for (int i = 0; i < Index; i++)
	{
		StringPtrSecond[i] = StringPtr[i];
	}
	StringPtrSecond[Index] = Element;
	for (int i = Index + 1; i < StringPtrSecondSize; i++)
	{
		StringPtrSecond[i] = StringPtr[i - 1];
	}
	delete[] StringPtr;
	StringPtr = StringPtrSecond;
}

// Добавляет символ к концу строки
void StrAddC(char*& StringPtr, const char Element) {
	const int Index = strlen(StringPtr);
	char* StringPtrSecond;
	int StringPtrSecondSize = strlen(StringPtr) + 2;
	StringPtrSecond = new char[StringPtrSecondSize];
	for (int i = 0; i < Index; i++)
	{
		StringPtrSecond[i] = StringPtr[i];
	}
	StringPtrSecond[Index] = Element;
	for (int i = Index + 1; i < StringPtrSecondSize; i++)
	{
		StringPtrSecond[i] = StringPtr[i - 1];
	}
	delete[] StringPtr;
	StringPtr = StringPtrSecond;
}

// Удалячет символ со строки на определённом индексе
void StrRemoveC(char*& StringPtr, const int Index) {
	char* StringPtrSecond;
	int StringPtrSecondSize = strlen(StringPtr) + 2;
	StringPtrSecond = new char[StringPtrSecondSize];
	for (int i = 0; i < Index; i++)
	{
		StringPtrSecond[i] = StringPtr[i];
	}
	for (int i = Index; i < StringPtrSecondSize; i++)
	{
		StringPtrSecond[i] = StringPtr[i + 1];
	}
	delete[] StringPtr;
	StringPtr = StringPtrSecond;
}

// Удаляет последний символ
void StrRemoveC(char*& StringPtr) {
	const int Index = strlen(StringPtr);
	char* StringPtrSecond;
	int StringPtrSecondSize = strlen(StringPtr) + 2;
	StringPtrSecond = new char[StringPtrSecondSize];
	for (int i = 0; i < Index; i++)
	{
		StringPtrSecond[i] = StringPtr[i];
	}
	for (int i = Index; i < StringPtrSecondSize; i++)
	{
		StringPtrSecond[i] = StringPtr[i + 1];
	}
	delete[] StringPtr;
	StringPtr = StringPtrSecond;
}

// Добавляет строку на указанный иденкс
void StrAddS(char*& StringPtrDest, const char* StringPtrScr, const int Index) {
	char* StringPtrSecond;
	int StringPtrSecondSize = strlen(StringPtrDest) + strlen(StringPtrScr) + 1;
	StringPtrSecond = new char[StringPtrSecondSize];
	for (int i = 0; i < Index; i++)
	{
		StringPtrSecond[i] = StringPtrDest[i];
	}
	for (int i = Index, j = 0; i < strlen(StringPtrDest) + strlen(StringPtrScr); i++)
	{
		StringPtrSecond[i] = StringPtrScr[j];
		j++;
	}
	for (int i = Index + strlen(StringPtrScr); i < StringPtrSecondSize; i++)
	{
		StringPtrSecond[i] = StringPtrDest[i - strlen(StringPtrScr)];
	}
	StringPtrSecond[StringPtrSecondSize - 1] = '\0';
	delete[] StringPtrDest;
	StringPtrDest = StringPtrSecond;
}

// Добавляет строку в конец уже имеющийся
void StrAddS(char*& StringPtrDest, const char* StringPtrScr) {
	const int Index = strlen(StringPtrDest);
	char* StringPtrSecond;
	int StringPtrSecondSize = strlen(StringPtrDest) + strlen(StringPtrScr) + 1;
	StringPtrSecond = new char[StringPtrSecondSize];
	for (int i = 0; i < Index; i++)
	{
		StringPtrSecond[i] = StringPtrDest[i];
	}
	for (int i = Index, j = 0; i < strlen(StringPtrDest) + strlen(StringPtrScr); i++)
	{
		StringPtrSecond[i] = StringPtrScr[j];
		j++;
	}
	for (int i = Index + strlen(StringPtrScr); i < StringPtrSecondSize; i++)
	{
		StringPtrSecond[i] = StringPtrDest[i - strlen(StringPtrScr)];
	}
	StringPtrSecond[StringPtrSecondSize - 1] = '\0';
	delete[] StringPtrDest;
	StringPtrDest = StringPtrSecond;
}

// Убирает Size символов на определённом индексе
void StrRemoveS(char*& StringPtr, const int Index, const int Size) {
	char* StringPtrSecond;
	int StringPtrSecondSize = strlen(StringPtr) - Size + 1;
	StringPtrSecond = new char[StringPtrSecondSize];
	for (int i = 0; i < Index; i++)
	{
		StringPtrSecond[i] = StringPtr[i];
	}
	for (int i = Index; i < StringPtrSecondSize; i++)
	{
		StringPtrSecond[i] = StringPtr[i + Size];
	}
	StringPtrSecond[StringPtrSecondSize - 1] = '\0';
	delete[] StringPtr;
	StringPtr = StringPtrSecond;
}