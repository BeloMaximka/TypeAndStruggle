#pragma once
//-------------------------------------------------------------
// strpp.h
//-------------------------------------------------------------
// ��� �������� ���������� ������� ��� ������ � �-��������
//-------------------------------------------------------------

// �������� ������ ��� ��������� ���������� ��������� (�� ��������� 1)
// � ��������� ������ ������� �������� � ����� 0, ����� ���� ��������� ����� �� ���������� ������
char* StrInit(int Size = 1);
// ��������� ������ � ������ �� ����������� ������
void StrAddC(char*& StringPtr, const char Element, const int Index);
// ��������� ������ � ����� ������
void StrAddC(char*& StringPtr, const char Element);
// �������� ������ �� ������ �� ����������� �������
void StrRemoveC(char*& StringPtr, const int Index);
// ������� ��������� ������
void StrRemoveC(char*& StringPtr);
// ��������� ������ �� ��������� ������
void StrAddS(char*& StringPtrDest, const char* StringPtrScr, const int Index);
// ��������� ������ � ����� ��� ���������
void StrAddS(char*& StringPtrDest, const char* StringPtrScr);
// ������� Size �������� �� ����������� �������
void StrRemoveS(char*& StringPtr, const int Index, const int Size);