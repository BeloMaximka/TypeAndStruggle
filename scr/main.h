#pragma once
// SDL
// Подключаем библиотеку SLD.h для работы и графикой, аудио и инпутом.
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
// С++ билиотеки
#include <stdarg.h>
#include <string.h>
#include <time.h>
#include <iostream>
#include <vector>
#include <math.h>
#include <string>
// Собственные
#include "collision.h"
#include "entities.h"
#include "game_resources.h"
#include "input.h"
#include "log.h"
#include "point.h"
#include "render.h"
#include "strpp.h"
#include "timers.h"

//------------------------------------------------------
// main.h
//------------------------------------------------------
// Дефайны, глобальные значения т.д.
//------------------------------------------------------
#define strcat USEstrcat_s
#define localtime USElocaltime_s
// Использовать математически константы по типу M_PI
#define _USE_MATH_DEFINES
#define NODEBUG_MODE

enum DIFFICULTIES {
	DIFFICULTY_TEST,
	DIFFICULTY_EASY,
	DIFFICULTY_NORMAL,
	DIFFICULTY_HARD,	
};
enum BUTTON_NAMES {
	BTN_INGAME_CONTINUE,
	BTN_INGAME_QUIT_MAINMENU,
	BTN_INGAME_QUIT_DESKTOP,
	BTN_INGAME_RESTART,
	BTN_MENU_CLASSIC,
	BTN_MENU_ARITHMETIC,
	BTN_MENU_SCORES,
	BTN_MENU_QUIT_DESKTOP,
	BTN_DIFFICULTY_EASY,
	BTN_DIFFICULTY_NORMAL,
	BTN_DIFFICULTY_HARD,
	BTN_DIFFICULTY_BACK,
	BTN_DEAD_RETRY,
	BTN_DEAD_QUIT_MAINMENU,
	BTN_SCORES_BACK
};
struct button
{
	point Pos;
	std::string Text;
	int Heigth;
	int Width;
	int ID;
	collisionbox Collision;
};
struct highscore {
	char Name[16];
	int Score;
	int Difficulty;
	int Mode;
};
// Глобальные переменные
extern std::vector<button> Buttons;
extern bool IngameMenuShow;
extern int MapCurrent[24][24];
extern const char* WINDOW_NAME;
extern int TRUE_RESOLUTION_X;
extern int TRUE_RESOLUTION_Y;
extern int WINDOW_RESOLUTION_X;
extern int WINDOW_RESOLUTION_Y;
extern SDL_Renderer* RendererPrimary;
extern SDL_Window* WindowPrimary;
extern bool FPSCounter;
extern Uint32 TickCurrent;
extern Uint32 TicksToSecond_FPS;
extern int TickDifference;
extern int FramesPerSecondPresent;
extern ipoint MousePosWindow;
extern struct EntityPlayer MainPlayer;
extern int ArenaWidth;
extern int ArenaHeight;
extern std::string WordInput;
extern bool GamePaused;
extern bool MainMenuShow;
extern bool Restart;
extern bool ChoosingDifficultyShow;
extern int Difficulty;
extern bool PlayerDead;
extern bool ArithmeticMode;
extern std::vector<std::string> GameWords;
extern double SlowdownTimerMod;
extern double DifficultySpeedModifier;
extern bool HighscoresShow;
extern bool HighscoresEnterShow;

extern const int GameHighscoresSize;
extern highscore GameHighscores[];


void QuitGame();