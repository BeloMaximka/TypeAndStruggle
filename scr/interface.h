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

enum class DeadMenuCode
{
	TO_MAIN_MENU,
	RETRY,
};

PauseMenuCode PauseMenu();
void HighscoreEnterMenu(DifficultyCode Difficulty, bool ArithmeticMode);
DeadMenuCode DeadMenu(SDL_Texture* BackgroundTexture, DifficultyCode Difficulty, bool ArithmeticMode);
void MainMenu();