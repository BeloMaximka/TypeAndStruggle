#pragma once
//-------------------------------------------------------------
// strpp.h
//-------------------------------------------------------------
// Тут хранятся самописные функции для работы с С-строками
//-------------------------------------------------------------

// Выделяет память под указанное количество елементов (по умолчанию 1)
// и заполняет первый елемент символом с кодом 0, после чего возращает адрес на выделенную память
char* StrInit(int Size = 1);
// Добавляет символ к строке на определённый индекс
void StrAddC(char*& StringPtr, const char Element, const int Index);
// Добавляет символ к концу строки
void StrAddC(char*& StringPtr, const char Element);
// Удалячет символ со строки на определённом индексе
void StrRemoveC(char*& StringPtr, const int Index);
// Удаляет последний символ
void StrRemoveC(char*& StringPtr);
// Добавляет строку на указанный иденкс
void StrAddS(char*& StringPtrDest, const char* StringPtrScr, const int Index);
// Добавляет строку в конец уже имеющийся
void StrAddS(char*& StringPtrDest, const char* StringPtrScr);
// Убирает Size символов на определённом индексе
void StrRemoveS(char*& StringPtr, const int Index, const int Size);