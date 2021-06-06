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

enum Langs
{
	LANG_EN,
	LANG_RU,
};

struct Slider
{
	point Pos;
	collisionbox Collision;
	double Value = 1;
	int TextID;
	int Heigth;
	int Width;
	int ID;
};

typedef std::vector<Slider> Sliders;

extern Sliders GameSliders;

void SetButtonsSize(buttons& GameButtons, TTF_Font* Font);
void InitSliders(Sliders& GameSliders);
void InitButtons(buttons& GameButtons);
PauseMenuCode PauseMenu();
void HighscoreEnterMenu(DifficultyCode Difficulty, bool ArithmeticMode);
DeadMenuCode DeadMenu(SDL_Texture* BackgroundTexture, DifficultyCode Difficulty, bool ArithmeticMode);
void MainMenu();