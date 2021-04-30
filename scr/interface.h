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

struct Slider
{
	point Pos;
	std::string Text;
	collisionbox Collision;
	int Heigth;
	int Width;
	int ID;
	int Value = 100;
};

void InitButtons();
PauseMenuCode PauseMenu();
void HighscoreEnterMenu(DifficultyCode Difficulty, bool ArithmeticMode);
DeadMenuCode DeadMenu(SDL_Texture* BackgroundTexture, DifficultyCode Difficulty, bool ArithmeticMode);
void MainMenu();