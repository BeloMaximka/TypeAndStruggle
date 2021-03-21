#include "SDL.h"
#include "strpp.h"
#include <time.h>
#include <iostream>

bool WriteInLog(const char* StringToWrite, ...) {
    // �������� ���������� ����� � �������� ����������
    SDL_RWops* LogFile = SDL_RWFromFile("log.txt", "a");

    // �������� ��������� �������� �����
    if (LogFile != nullptr)
    {
        // ��������� 1024 ������ �� ������, ��� ������ ����� ������� ���������� ����� ������, ������� ���� ������������
        char* NewString = StrInit(1024);
        // ��������� ������ ������ � time.h
        char* TimeString = StrInit(30);

        // ���������� ��� �������� ������� � �������� ����� 00:00/01.01.1970
        time_t TimeInSeconds;
        //��������� ��� ����� ������� ������ �� ��������
        tm TimeStruct;
        // �������� ������� ����� � ��������
        time(&TimeInSeconds);
        // ��������� ��� � ����������� ���������
        localtime_s(&TimeStruct, &TimeInSeconds);
        // �������� ��������������� ������. � ������ ������ ��� ����� ������ ����� �� �����
        strftime(TimeString, 30, "[%X] ", &TimeStruct);

        //����������� ������ ��� ������ strarg.h
        va_list argptr;
        va_start(argptr, StringToWrite);
        vsnprintf(NewString, 1023, StringToWrite, argptr);
        va_end(argptr);

        // ��������� ������ �� �������� � ������ �������� ������
        StrAddS(NewString, TimeString, 0);
        // ��������� � ����� \r ��� �������� ����� � �������� ������ Windows
        StrAddC(NewString, '\r');

        // �������� ������� SDL_RWrite(), ����� �������� ������ � ����.
        SDL_RWwrite(LogFile, NewString, sizeof(char), strlen(NewString));
        // ��������� ����. �� ���������
        SDL_RWclose(LogFile);

        // ����������� ������� ������
        delete[] NewString;
        delete[] TimeString;

        // ���������� 0, �� ������ �������
        return 0;

    }
    // ������� �� ������, ���� ���� ������������� ������� ���������� ��� ������ �������� �����
    else
    {
        return 1;
    }
}