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
	MAIN_CLASSIC,
	MAIN_ARITHMETIC,
	MAIN_SCORES,
	MAIN_TO_DESKTOP,
	SCORES_BACK,
};

InputCode ReadKeysPause(const SDL_Event& Event);
InputCode ReadMousePause(const SDL_Event& Event, const buttons& Buttons);
InputCode ReadKeysDifficulty(const SDL_Event& Event);
InputCode ReadMouseDifficuly(const SDL_Event& Event, const buttons& Buttons);
InputCode ReadMouseMain(const SDL_Event& Event, const buttons& Buttons);
InputCode ReadKeysScores(const SDL_Event& Event);
InputCode ReadMouseScores(const SDL_Event& Event, const buttons& Buttons);
void ReadKeys(SDL_Event& Event);
void ReadMouse(SDL_Event& Event);
