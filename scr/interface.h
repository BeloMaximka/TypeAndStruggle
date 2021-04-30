#pragma once

enum SLIDERSIDS
{
	SLDR_SFX,
	SLDR_MUSIC
};

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
	double Value = 1;
	int Heigth;
	int Width;
	int ID;
};

typedef std::vector<Slider> Sliders;

extern Sliders GameSliders;

void InitSliders(Sliders& GameSliders);
void InitButtons();
PauseMenuCode PauseMenu();
void HighscoreEnterMenu(DifficultyCode Difficulty, bool ArithmeticMode);
DeadMenuCode DeadMenu(SDL_Texture* BackgroundTexture, DifficultyCode Difficulty, bool ArithmeticMode);
void MainMenu();