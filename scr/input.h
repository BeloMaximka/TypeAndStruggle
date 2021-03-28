#pragma once
#include "main.h"

enum class InputCode
{
	NOTHING,
	PAUSE_TO_MAIN_MENU,
	PAUSE_TO_DESKTOP,
	PAUSE_RESTART,
	PAUSE_CONTINUE,
	DIFFICULTY_BACK,
	DIFFICULTY_EASY,
	DIFFICULTY_NORMAL,
	DIFFICULTY_HARD,
};

InputCode ReadKeysPause(const SDL_Event& Event);
InputCode ReadMousePause(const SDL_Event& Event, const buttons& Buttons);
InputCode ReadKeysDifficulty(const SDL_Event& Event);
InputCode ReadMouseDifficuly(const SDL_Event& Event, const buttons& Buttons);
void ReadKeys(SDL_Event& Event);
void ReadMouse(SDL_Event& Event);
