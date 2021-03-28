#pragma once
enum class PauseMenuCode
{
    CONTINUE,
    RESTART,
    TO_MAIN_MENU,
    TO_DESKTOP,
};

enum class DifficultyCode
{
    BACK,
    EASY,
    NORMAL,
    HARD,
};

PauseMenuCode PauseMenu();