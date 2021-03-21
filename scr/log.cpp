#include "SDL.h"
#include "strpp.h"
#include <time.h>
#include <iostream>

bool WriteInLog(const char* StringToWrite, ...) {
    // Открытие текстового файла в корневой директории
    SDL_RWops* LogFile = SDL_RWFromFile("log.txt", "a");

    // Проверка успешного открытия файла
    if (LogFile != nullptr)
    {
        // Выделение 1024 байтов на строку, ибо нельзя легко заранее определить длину строки, которую ввел пользователь
        char* NewString = StrInit(1024);
        // Небольшая строка работы с time.h
        char* TimeString = StrInit(30);

        // Переменная для хранения времени в секундах после 00:00/01.01.1970
        time_t TimeInSeconds;
        //Структура для более удобной работы со временем
        tm TimeStruct;
        // Получаем текущее время в секундах
        time(&TimeInSeconds);
        // Переводим его в адекваатную структуру
        localtime_s(&TimeStruct, &TimeInSeconds);
        // Получаем форматированную строку. В данном случае нам нужно просто время на часах
        strftime(TimeString, 30, "[%X] ", &TimeStruct);

        //Форматируем строку при помощи strarg.h
        va_list argptr;
        va_start(argptr, StringToWrite);
        vsnprintf(NewString, 1023, StringToWrite, argptr);
        va_end(argptr);

        // Добавляем строку со временем в начало основной строки
        StrAddS(NewString, TimeString, 0);
        // Добавляем в конец \r для переноса строк в тексовых файлах Windows
        StrAddC(NewString, '\r');

        // Вызываем функцию SDL_RWrite(), чтобы записать строку в файл.
        SDL_RWwrite(LogFile, NewString, sizeof(char), strlen(NewString));
        // Закрываем файл. Мы прекрасны
        SDL_RWclose(LogFile);

        // Обязательно очищаем память
        delete[] NewString;
        delete[] TimeString;

        // Возвращаем 0, всё прошло успешно
        return 0;

    }
    // Оставил на случай, если буду реализовывать вариант оповещения при ошибке открытия файла
    else
    {
        return 1;
    }
}