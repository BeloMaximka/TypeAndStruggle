#pragma once
#include "main.h"

enum class InputCode
{
	NOTHING,
	PAUSE_TO_MAIN_MENU,
	PAUSE_TO_DESKTOP,
	PAUSE_RESTART,
	PAUSE_OPTIONS,
	PAUSE_CONTINUE,
	DIFFICULTY_BACK,
	DIFFICULTY_EASY,
	DIFFICULTY_NORMAL,
	DIFFICULTY_HARD,
	MAIN_CLASSIC,
	MAIN_ARITHMETIC,
	MAIN_SCORES,
	MAIN_OPTIONS,
	MAIN_TO_DESKTOP,
	SCORES_BACK,
	SCORESENTER_SKIP,
	SCORESENTER_ENTER,
	DEAD_RETRY,
	DEAD_TO_MAIN_MENU,
	GAMESESSION_ENTER,
	GAMESESSION_PAUSE,
	OPTIONS_BACK,
	OPTIONS_EN,
	OPTIONS_RU,
};

InputCode ReadKeysOptions(const SDL_Event& Event);
InputCode ReadMouseOptions(const SDL_Event& Event, const buttons& Buttons, Sliders& GameSliders, bool FromPause);
InputCode ReadKeysPause(const SDL_Event& Event);
InputCode ReadMousePause(const SDL_Event& Event, const buttons& Buttons);
InputCode ReadKeysDifficulty(const SDL_Event& Event);
InputCode ReadMouseDifficuly(const SDL_Event& Event, const buttons& Buttons);
InputCode ReadMouseMain(const SDL_Event& Event, const buttons& Buttons);
InputCode ReadKeysScores(const SDL_Event& Event);
InputCode ReadMouseScores(const SDL_Event& Event, const buttons& Buttons);
InputCode ReadKeysScoreEnter(const SDL_Event& Event, std::string& WordInput);
InputCode ReadKeysDead(const SDL_Event& Event);
InputCode ReadMouseDead(const SDL_Event& Event, const buttons& Buttons);
InputCode ReadGameSessionKeys(SDL_Event& Event, std::string& WordInput);
void ReadMouse(SDL_Event& Event);
