#include "main.h"
#define SCREENPOS_X_CENTERED TRUE_RESOLUTION_X / 2
#define SCREENPOS_Y_CENTERED TRUE_RESOLUTION_Y / 2
// Небольшой буфер для ФПСА
char FPSString[10] = { '0','\0' };
// Определяет скорость битья сердца
int HeartbeatRate = 100;
//SDL_Color ColorDefaultBlue = { 44, 85, 107, 255 };
SDL_Color ColorDefaultBlue = { 54, 88, 163, 255 };

void UpdateWindowResolution(SDL_Event& Event)
{
	int LowestRes = Event.window.data1 < Event.window.data2 ? Event.window.data1 : Event.window.data2;
	WINDOW_RESOLUTION_X = LowestRes;
	WINDOW_RESOLUTION_Y = LowestRes;
	SDL_SetWindowSize(WindowPrimary, WINDOW_RESOLUTION_X, WINDOW_RESOLUTION_Y);
	SDL_RWops* File = SDL_RWFromFile("data.bin", "r+");
	if (File == nullptr)
	{
		WriteInLog("[ERROR] Unable to save options to the file \"data.bin\"!");
	}
	SDL_RWseek(File, sizeof(highscore) * GameHighscoresSize + sizeof(double) * 2, SEEK_SET);
	SDL_RWwrite(File, &WINDOW_RESOLUTION_X, sizeof(int), 1);
	SDL_RWwrite(File, &WINDOW_RESOLUTION_Y, sizeof(int), 1);
	SDL_RWclose(File);
}

// Рендерит текстуру
void RenderTexture(SDL_Texture* Texture, int PosX, int PosY, int Width, int Height)
{
	SDL_Rect DestinationRectangle{ PosX,PosY,Width,Height };
	SDL_RenderCopy(RendererPrimary, Texture, NULL, &DestinationRectangle);
}

// Рендерит текстуру без масшnабирования
void RenderTexture(SDL_Texture* Texture, int PosX, int PosY)
{
	int Width, Height;
	SDL_QueryTexture(Texture, NULL, NULL, &Width, &Height);
	SDL_Rect DestinationRectangle{ PosX,PosY,Width,Height };
	SDL_RenderCopy(RendererPrimary, Texture, NULL, &DestinationRectangle);
}

// Рендер текста
void RenderText(const char* Text, TTF_Font* Font, int x, int y, Uint8 Red, Uint8 Green, Uint8 Blue, Uint8 Alpha, bool Centered) {
	SDL_Color Color{ Red,Green,Blue,Alpha };
	SDL_Texture* TextTexture = GetTextTexture(Text, Font, Color);
	if (Centered)
	{
		RenderTextureCentered(TextTexture, x, y, 180);
	}
	else
	{
		RenderTexture(TextTexture, x, y);
	}
	SDL_DestroyTexture(TextTexture);
}

// Рендер текста с альтернативным вводом цвета
inline void RenderText(const char* Text, TTF_Font* Font, int x, int y, SDL_Color Color, bool Centered) {
	RenderText(Text, Font, x, y, Color.r, Color.g, Color.b, Color.a, Centered);
}

void RenderTextureCentered(SDL_Texture* Texture, int PosX, int PosY, double Angle = 0) {
	int Width, Height;
	SDL_QueryTexture(Texture, NULL, NULL, &Width, &Height);

	SDL_Rect DestinationRectangle{ PosX - Width / 2,PosY - Height / 2,Width,Height };

	SDL_RendererFlip RendererFlip = (SDL_RendererFlip)(SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL);
	SDL_RenderCopyEx(RendererPrimary, Texture, NULL, &DestinationRectangle, Angle, NULL, RendererFlip);
}

void RenderTextureCentered(SDL_Texture* Texture, int PosX, int PosY, int Width, int Height, double Angle = 0) {
	SDL_Rect DestinationRectangle{ PosX - Width / 2,PosY - Height / 2,Width,Height };

	SDL_RendererFlip RendererFlip = (SDL_RendererFlip)(SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL);
	SDL_RenderCopyEx(RendererPrimary, Texture, NULL, &DestinationRectangle, Angle, NULL, RendererFlip);
}

void DrawButton(int ButtonId, int LineThickness) {
	SDL_Rect Line;
	SDL_SetRenderDrawColor(RendererPrimary, ColorDefaultBlue.r, ColorDefaultBlue.g, ColorDefaultBlue.b, ColorDefaultBlue.a);
	// Верхняя
	Line = { (int)GameButtons[ButtonId].Pos.x - GameButtons[ButtonId].Width / 2,(int)GameButtons[ButtonId].Pos.y - GameButtons[ButtonId].Heigth / 2, GameButtons[ButtonId].Width, LineThickness };
	SDL_RenderFillRect(RendererPrimary, &Line);
	// Нижняя
	Line = { (int)GameButtons[ButtonId].Pos.x - GameButtons[ButtonId].Width / 2,(int)GameButtons[ButtonId].Pos.y + GameButtons[ButtonId].Heigth / 2, GameButtons[ButtonId].Width, LineThickness };
	SDL_RenderFillRect(RendererPrimary, &Line);
	// Левая
	Line = { (int)GameButtons[ButtonId].Pos.x - GameButtons[ButtonId].Width / 2,(int)GameButtons[ButtonId].Pos.y - GameButtons[ButtonId].Heigth / 2, LineThickness, GameButtons[ButtonId].Heigth };
	SDL_RenderFillRect(RendererPrimary, &Line);
	// Правая
	Line = { (int)GameButtons[ButtonId].Pos.x + GameButtons[ButtonId].Width / 2,(int)GameButtons[ButtonId].Pos.y - GameButtons[ButtonId].Heigth / 2, LineThickness, GameButtons[ButtonId].Heigth + LineThickness };
	SDL_RenderFillRect(RendererPrimary, &Line);
	RenderText(Text[GameButtons[ButtonId].TextID].c_str(), MenuFont, GameButtons[ButtonId].Pos.x, GameButtons[ButtonId].Pos.y, ColorDefaultBlue, true);
}

void DrawSlider(Slider& SliderToDraw, bool Centered)
{
	SDL_SetRenderDrawColor(RendererPrimary, ColorDefaultBlue.r, ColorDefaultBlue.g, ColorDefaultBlue.b, ColorDefaultBlue.a);
	// Горизонтальная линия
	SDL_Rect Line = { SliderToDraw.Pos.x, SliderToDraw.Pos.y,
					  SliderToDraw.Width, SliderToDraw.Heigth / 5 };
	if (Centered)
	{
		Line.x -= SliderToDraw.Width / 2;
	}
	SDL_RenderFillRect(RendererPrimary, &Line);
	RenderText(Text[SliderToDraw.TextID].c_str(), MenuFont, Line.x + SliderToDraw.Width / 2, SliderToDraw.Pos.y - SliderToDraw.Heigth * 7 / 5, ColorDefaultBlue, true);
	// Вертинальная линия
	Line = { int(Line.x + SliderToDraw.Width * SliderToDraw.Value), int(SliderToDraw.Pos.y - SliderToDraw.Heigth * 2 / 5), SliderToDraw.Heigth / 5 , SliderToDraw.Heigth };
	SDL_RenderFillRect(RendererPrimary, &Line);

}

void DrawOptionsFrame()
{
	if (FramesPerSecondPresent > 10000) FramesPerSecondPresent = 0;
	FramesPerSecondPresent++;

	// Фон
	RenderTexture(Textures[GIMG_MAP], 0, 0, ArenaWidth, ArenaHeight);
	// Кнопка Back
	DrawButton(BTN_OPTIONS_BACK, 5);
	// Напись
	RenderText(Text[TXT_OPTIONS].c_str(), MenuFont, SCREENPOS_X_CENTERED, SCREENPOS_Y_CENTERED / 4 + SCREENPOS_Y_CENTERED / 8, ColorDefaultBlue, true);
	// Линия под написью
	SDL_Rect Line = { SCREENPOS_X_CENTERED - 250,SCREENPOS_Y_CENTERED / 4 + 55 + SCREENPOS_Y_CENTERED / 8, 500, 5 };
	SDL_SetRenderDrawColor(RendererPrimary, ColorDefaultBlue.r, ColorDefaultBlue.g, ColorDefaultBlue.b, ColorDefaultBlue.a);
	SDL_RenderFillRect(RendererPrimary, &Line);
	SDL_SetRenderDrawColor(RendererPrimary, 255, 255, 255, 255);
	// Слайдеры
	DrawSlider(GameSliders[SLDR_SFX], true); // SFX
	DrawSlider(GameSliders[SLDR_MUSIC], true); // Music

	// ФПС, если включён
	if (FPSCounter) {
		RenderText(FPSString, NormalFont, 0, 0, 0, 0, 0, 255, false);
		if (TickCurrent - TicksToSecond_FPS >= 1000)
		{
			TicksToSecond_FPS = TickCurrent;
			_itoa_s(FramesPerSecondPresent, FPSString, 10);
			FramesPerSecondPresent = 0;
		}
	}

	// Курсор
	RenderTexture(Textures[GIMG_INTERFACE_CURSOR], MousePosWindow.x, MousePosWindow.y);
}

void DrawPauseMenuFrame()
{
	if (FramesPerSecondPresent > 10000) FramesPerSecondPresent = 0;
	FramesPerSecondPresent++;

	RenderTexture(Textures[GIMG_MAP], 0, 0, ArenaWidth, ArenaHeight);
	SDL_Rect Line = { SCREENPOS_X_CENTERED - 275,SCREENPOS_Y_CENTERED / 4 + 55 + SCREENPOS_Y_CENTERED / 8, 550, 5 };
	SDL_SetRenderDrawColor(RendererPrimary, ColorDefaultBlue.r, ColorDefaultBlue.g, ColorDefaultBlue.b, ColorDefaultBlue.a);
	SDL_RenderFillRect(RendererPrimary, &Line);
	SDL_SetRenderDrawColor(RendererPrimary, 255, 255, 255, 255);
	RenderText(Text[TXT_PAUSED].c_str(), MenuFont, SCREENPOS_X_CENTERED, SCREENPOS_Y_CENTERED / 4 + SCREENPOS_Y_CENTERED / 8, ColorDefaultBlue, true);
	// Continue
	DrawButton(BTN_INGAME_CONTINUE, 5);
	// Restart
	DrawButton(BTN_INGAME_RESTART, 5);
	// Options
	DrawButton(BTN_INGAME_OPTIONS, 5);
	// Quit to Main Menu
	DrawButton(BTN_INGAME_QUIT_MAINMENU, 5);
	// Quit to Desktop
	DrawButton(BTN_INGAME_QUIT_DESKTOP, 5);

	// ФПС, если включён
	if (FPSCounter) {
		RenderText(FPSString, NormalFont, 0, 0, 0, 0, 0, 255, false);
		if (TickCurrent - TicksToSecond_FPS >= 1000)
		{
			TicksToSecond_FPS = TickCurrent;
			_itoa_s(FramesPerSecondPresent, FPSString, 10);
			FramesPerSecondPresent = 0;
		}
	}

	// Курсор
	RenderTexture(Textures[GIMG_INTERFACE_CURSOR], MousePosWindow.x, MousePosWindow.y);
}

void DrawDifficultyFrame()
{
	if (FramesPerSecondPresent > 10000) FramesPerSecondPresent = 0;
	FramesPerSecondPresent++;

	// Фон
	RenderTexture(Textures[GIMG_MAP], 0, 0, ArenaWidth, ArenaHeight);
	// Линия
	SDL_Rect Line = { SCREENPOS_X_CENTERED - 370,SCREENPOS_Y_CENTERED / 4 + 55 + SCREENPOS_Y_CENTERED / 8, 740, 5 };
	SDL_SetRenderDrawColor(RendererPrimary, ColorDefaultBlue.r, ColorDefaultBlue.g, ColorDefaultBlue.b, ColorDefaultBlue.a);
	SDL_RenderFillRect(RendererPrimary, &Line);
	SDL_SetRenderDrawColor(RendererPrimary, 255, 255, 255, 255);
	RenderText(Text[TXT_CHOOSEDIFF].c_str(), MenuFont, SCREENPOS_X_CENTERED, SCREENPOS_Y_CENTERED / 4 + SCREENPOS_Y_CENTERED / 8, ColorDefaultBlue, true);
	// Easy
	DrawButton(BTN_DIFFICULTY_EASY, 5);
	// Normal
	DrawButton(BTN_DIFFICULTY_NORMAL, 5);
	// Hard        
	DrawButton(BTN_DIFFICULTY_HARD, 5);
	// Back        
	DrawButton(BTN_DIFFICULTY_BACK, 5);

	// ФПС, если включён
	if (FPSCounter) {
		RenderText(FPSString, NormalFont, 0, 0, 0, 0, 0, 255, false);
		if (TickCurrent - TicksToSecond_FPS >= 1000)
		{
			TicksToSecond_FPS = TickCurrent;
			_itoa_s(FramesPerSecondPresent, FPSString, 10);
			FramesPerSecondPresent = 0;
		}
	}

	// Курсор
	RenderTexture(Textures[GIMG_INTERFACE_CURSOR], MousePosWindow.x, MousePosWindow.y);
}

void DrawMainMenuFrame()
{
	if (FramesPerSecondPresent > 10000) FramesPerSecondPresent = 0;
	FramesPerSecondPresent++;

	// Фон
	RenderTexture(Textures[GIMG_MAP], 0, 0, ArenaWidth, ArenaHeight);
	// Линия
	SDL_Rect Line = { SCREENPOS_X_CENTERED - 250,SCREENPOS_Y_CENTERED / 4 + 55 + SCREENPOS_Y_CENTERED / 8, 500, 5 };
	SDL_SetRenderDrawColor(RendererPrimary, ColorDefaultBlue.r, ColorDefaultBlue.g, ColorDefaultBlue.b, ColorDefaultBlue.a);
	SDL_RenderFillRect(RendererPrimary, &Line);
	SDL_SetRenderDrawColor(RendererPrimary, 255, 255, 255, 255);
	RenderText(Text[TXT_MAINMENU].c_str(), MenuFont, SCREENPOS_X_CENTERED, SCREENPOS_Y_CENTERED / 4 + SCREENPOS_Y_CENTERED / 8, ColorDefaultBlue, true);
	// Play classic        
	DrawButton(BTN_MENU_CLASSIC, 5);
	// Play arithmeitc
	DrawButton(BTN_MENU_ARITHMETIC, 5);
	// Scores        
	DrawButton(BTN_MENU_SCORES, 5);
	// Options
	DrawButton(BTN_MENU_OPTIONS, 5);
	// Quit        
	DrawButton(BTN_MENU_QUIT_DESKTOP, 5);
	// ФПС, если включён
	if (FPSCounter) {
		RenderText(FPSString, NormalFont, 0, 0, 0, 0, 0, 255, false);
		if (TickCurrent - TicksToSecond_FPS >= 1000)
		{
			TicksToSecond_FPS = TickCurrent;
			_itoa_s(FramesPerSecondPresent, FPSString, 10);
			FramesPerSecondPresent = 0;
		}
	}

	// Курсор
	RenderTexture(Textures[GIMG_INTERFACE_CURSOR], MousePosWindow.x, MousePosWindow.y);
}

void DrawHighscoresFrame()
{
	if (FramesPerSecondPresent > 10000) FramesPerSecondPresent = 0;
	FramesPerSecondPresent++;

	// Фон
	RenderTexture(Textures[GIMG_MAP], 0, 0, ArenaWidth, ArenaHeight);
	// Кнопка Back
	DrawButton(BTN_SCORES_BACK, 5);
	// Напись
	RenderText(Text[TXT_HIGHSCORES].c_str(), MenuFont, SCREENPOS_X_CENTERED, SCREENPOS_Y_CENTERED / 4 - SCREENPOS_Y_CENTERED / 8, ColorDefaultBlue, true);
	RenderText(Text[TXT_HIGHSCORES_CAP].c_str(), ScoresFont, SCREENPOS_X_CENTERED, SCREENPOS_Y_CENTERED / 4 + SCREENPOS_Y_CENTERED / 16, ColorDefaultBlue, true);
	char StrBuffer[13];
	for (int i = 0; i < GameHighscoresSize; i++)
	{
		_itoa_s(i + 1, StrBuffer, 13, 10);
		RenderText(StrBuffer, NormalFont, SCREENPOS_X_CENTERED / 8, SCREENPOS_Y_CENTERED / 4 + SCREENPOS_Y_CENTERED / 8 * (i + 1), ColorDefaultBlue, false);
		// Режим
		if (GameHighscores[i].Mode == 0)
		{
			RenderText(Text[TXT_CLASSIC].c_str(), NormalFont, SCREENPOS_X_CENTERED / 8 + 460, SCREENPOS_Y_CENTERED / 4 + SCREENPOS_Y_CENTERED / 8 * (i + 1) + 27, ColorDefaultBlue, true);
		}
		else if (GameHighscores[i].Mode == 1)
		{
			RenderText(Text[TXT_ARITHMETIC].c_str(), NormalFont, SCREENPOS_X_CENTERED / 8 + 460, SCREENPOS_Y_CENTERED / 4 + SCREENPOS_Y_CENTERED / 8 * (i + 1) + 27, ColorDefaultBlue, true);
		}
		else
		{
			RenderText("_____", NormalFont, SCREENPOS_X_CENTERED / 8 + 460, SCREENPOS_Y_CENTERED / 4 + SCREENPOS_Y_CENTERED / 8 * (i + 1) + 27, ColorDefaultBlue, true);
		}
		// Сложность
		if (GameHighscores[i].Difficulty == DIFFICULTY_EASY)
		{
			RenderText(Text[TXT_EASY].c_str(), NormalFont, SCREENPOS_X_CENTERED / 8 + 670, SCREENPOS_Y_CENTERED / 4 + SCREENPOS_Y_CENTERED / 8 * (i + 1) + 27, ColorDefaultBlue, true);
		}
		else if (GameHighscores[i].Difficulty == DIFFICULTY_NORMAL)
		{
			RenderText(Text[TXT_NORMAL].c_str(), NormalFont, SCREENPOS_X_CENTERED / 8 + 670, SCREENPOS_Y_CENTERED / 4 + SCREENPOS_Y_CENTERED / 8 * (i + 1) + 27, ColorDefaultBlue, true);
		}
		else if (GameHighscores[i].Difficulty == DIFFICULTY_HARD)
		{
			RenderText(Text[TXT_HARD].c_str(), NormalFont, SCREENPOS_X_CENTERED / 8 + 670, SCREENPOS_Y_CENTERED / 4 + SCREENPOS_Y_CENTERED / 8 * (i + 1) + 27, ColorDefaultBlue, true);
		}
		else
		{
			RenderText("____", NormalFont, SCREENPOS_X_CENTERED / 8 + 670, SCREENPOS_Y_CENTERED / 4 + SCREENPOS_Y_CENTERED / 8 * (i + 1) + 27, ColorDefaultBlue, true);
		}
		// Счёт
		if (GameHighscores[i].Score >= 0)
		{
			_itoa_s(GameHighscores[i].Score, StrBuffer, 13, 10);
			RenderText(StrBuffer, NormalFont, SCREENPOS_X_CENTERED / 8 + 870, SCREENPOS_Y_CENTERED / 4 + SCREENPOS_Y_CENTERED / 8 * (i + 1) + 27, ColorDefaultBlue, true);
		}
		else
		{
			RenderText("____", NormalFont, SCREENPOS_X_CENTERED / 8 + 870, SCREENPOS_Y_CENTERED / 4 + SCREENPOS_Y_CENTERED / 8 * (i + 1) + 27, ColorDefaultBlue, true);
		}
		// Имя
		RenderText(GameHighscores[i].Name, NormalFont, SCREENPOS_X_CENTERED / 8 + 100, SCREENPOS_Y_CENTERED / 4 + SCREENPOS_Y_CENTERED / 8 * (i + 1), ColorDefaultBlue, false);
	}

	// ФПС, если включён
	if (FPSCounter) {
		RenderText(FPSString, NormalFont, 0, 0, 0, 0, 0, 255, false);
		if (TickCurrent - TicksToSecond_FPS >= 1000)
		{
			TicksToSecond_FPS = TickCurrent;
			_itoa_s(FramesPerSecondPresent, FPSString, 10);
			FramesPerSecondPresent = 0;
		}
	}

	// Курсор
	RenderTexture(Textures[GIMG_INTERFACE_CURSOR], MousePosWindow.x, MousePosWindow.y);
}

void DrawHighscoreEnterFrame(const std::string& WordInput)
{
	if (FramesPerSecondPresent > 10000) FramesPerSecondPresent = 0;
	FramesPerSecondPresent++;

	// Фон
	RenderTexture(Textures[GIMG_MAP], 0, 0, ArenaWidth, ArenaHeight);
	// Напись
	RenderText(Text[TXT_TOPTEN].c_str(), ScoresFont, SCREENPOS_X_CENTERED, SCREENPOS_Y_CENTERED - SCREENPOS_Y_CENTERED / 4, ColorDefaultBlue, true);
	RenderText(Text[TXT_ENTERNAME].c_str(), ScoresFont, SCREENPOS_X_CENTERED, SCREENPOS_Y_CENTERED - SCREENPOS_Y_CENTERED / 8, ColorDefaultBlue, true);
	// Вводимый текст
	RenderText(WordInput.c_str(), NormalFont, SCREENPOS_X_CENTERED, SCREENPOS_Y_CENTERED, ColorDefaultBlue, true);

	// ФПС, если включён
	if (FPSCounter) {
		RenderText(FPSString, NormalFont, 0, 0, 0, 0, 0, 255, false);
		if (TickCurrent - TicksToSecond_FPS >= 1000)
		{
			TicksToSecond_FPS = TickCurrent;
			_itoa_s(FramesPerSecondPresent, FPSString, 10);
			FramesPerSecondPresent = 0;
		}
	}

}

void DrawDeadFrame(SDL_Texture* BackgroundTexture)
{
	if (FramesPerSecondPresent > 10000) FramesPerSecondPresent = 0;
	FramesPerSecondPresent++;

	RenderTexture(BackgroundTexture, 0, 0, ArenaWidth, ArenaHeight);
	std::string Temp;
	char ScoreStrTemp[12];
	_itoa_s(MainPlayer.Score, ScoreStrTemp, 12, 10);
	Temp = Text[TXT_YOURSCORE].c_str();
	Temp += ScoreStrTemp;
	//Слова
	RenderText(Text[TXT_MAYBENEXTTIME].c_str(), MenuFont, SCREENPOS_X_CENTERED, SCREENPOS_Y_CENTERED - SCREENPOS_Y_CENTERED / 2, ColorDefaultBlue, true);
	// Рекорд
	RenderText(Temp.c_str(), MenuFont, SCREENPOS_X_CENTERED, SCREENPOS_Y_CENTERED - SCREENPOS_Y_CENTERED / 4, ColorDefaultBlue, true);
	// Кнопки
	DrawButton(BTN_DEAD_RETRY, 5);
	DrawButton(BTN_DEAD_QUIT_MAINMENU, 5);

	// ФПС, если включён
	if (FPSCounter) {
		RenderText(FPSString, NormalFont, 0, 0, 0, 0, 0, 255, false);
		if (TickCurrent - TicksToSecond_FPS >= 1000)
		{
			TicksToSecond_FPS = TickCurrent;
			_itoa_s(FramesPerSecondPresent, FPSString, 10);
			FramesPerSecondPresent = 0;
		}
	}

	// Курсор
	RenderTexture(Textures[GIMG_INTERFACE_CURSOR], MousePosWindow.x, MousePosWindow.y);
}

void DrawGameSessionFrame(const std::string& WordInput) {
	if (FramesPerSecondPresent > 10000) FramesPerSecondPresent = 0;
	FramesPerSecondPresent++;

	// Фон
	RenderTexture(Textures[GIMG_MAP], 0, 0, ArenaWidth, ArenaHeight);
	// Косметические частицы
	for (int i = 0; i < GameCosmetics.size(); i++)
	{
		if (TimerCosmeticHeartDecrease > 5)
		{
			GameCosmetics[i].Size -= 3 * ((101 - SlowdownTimerMod) / 100.0);
			if (GameCosmetics[i].Size < 1)
			{
				GameCosmetics.erase(GameCosmetics.begin() + i);
				i--;
				continue;
			}
		}
		if (GameCosmetics[i].Type == PRTCL_HEART)
		{
			RenderTextureCentered(Textures[GIMG_SPRITES_COSMETIC_HEART], GameCosmetics[i].Pos.x, GameCosmetics[i].Pos.y, GameCosmetics[i].Size, GameCosmetics[i].Size, 90);
		}
		else
		{
			RenderTextureCentered(Textures[GIMG_SPRITES_COSMETIC_STAR], GameCosmetics[i].Pos.x, GameCosmetics[i].Pos.y, GameCosmetics[i].Size, GameCosmetics[i].Size, 90);
		}


	}
	if (TimerCosmeticHeartDecrease > 10)
	{
		TimerCosmeticHeartDecrease = 0;
	}
	// Бонусы
	for (int i = 0; i < GameBonuses.size(); i++)
	{
		RenderTextureCentered(Textures[GameBonuses[i].TextureIndex], GameBonuses[i].Pos.x, GameBonuses[i].Pos.y, GameBonuses[i].Size, GameBonuses[i].Size, GameBonuses[i].Rotation);
		if (GameBonuses[i].Size == GameBonuses[i].FullSize)
		{
			RenderText(GameBonuses[i].Word.c_str(), NormalFont, GameBonuses[i].Pos.x, GameBonuses[i].Pos.y - GameBonuses[i].Size / 2 - 10, ColorDefaultBlue, true);
		}
	}

	// Противники
	for (int i = 0; i < GameEnemies.size(); i++)
	{
		RenderTextureCentered(Textures[GameEnemies[i].TextureIndex], GameEnemies[i].Pos.x, GameEnemies[i].Pos.y, GameEnemies[i].Width, GameEnemies[i].Height, GameEnemies[i].Rotation);
		RenderText(GameEnemies[i].Word.c_str(), NormalFont, GameEnemies[i].Pos.x, GameEnemies[i].Pos.y - GameEnemies[i].Height / 2, ColorDefaultBlue, true);
	}
	// Персонаж
	if (GamePlayerHearts.size() == 0)
	{
		HeartbeatRate = 25;
	}
	else if (GamePlayerHearts.size() == 1)
	{
		HeartbeatRate = 50;
	}
	else
	{
		HeartbeatRate = 100;
	}
	if (MainPlayer.IsDamaged == true)
	{
		RenderTextureCentered(Textures[GIMG_SPRITES_PLAYER_DAMAGED], MainPlayer.Pos.x, MainPlayer.Pos.y, MainPlayer.Width * 0.9, MainPlayer.Height * 0.9, MainPlayer.Rotation);
	}
	else if (TimerHeartbeat > HeartbeatRate)
	{
		if (MainPlayer.IsDamaged == true)
		{
			RenderTextureCentered(Textures[GIMG_SPRITES_PLAYER_DAMAGED], MainPlayer.Pos.x, MainPlayer.Pos.y, MainPlayer.Width * 1.2, MainPlayer.Height * 1.2, MainPlayer.Rotation);
		}
		else
		{
			RenderTextureCentered(Textures[GIMG_SPRITES_PLAYER], MainPlayer.Pos.x, MainPlayer.Pos.y, MainPlayer.Width * 1.2, MainPlayer.Height * 1.2, MainPlayer.Rotation);
		}
	}
	else
	{
		RenderTextureCentered(Textures[GIMG_SPRITES_PLAYER], MainPlayer.Pos.x, MainPlayer.Pos.y, MainPlayer.Width, MainPlayer.Height, MainPlayer.Rotation);
	}
	if (TimerHeartDamaged > 5)
	{
		if (MainPlayer.IsDamaged == true)
		{
			TimerHeartbeat = 0;
		}
		MainPlayer.IsDamaged = false;

	}
	if (TimerHeartbeat > HeartbeatRate + 10)
	{
		TimerHeartbeat = 0;
	}

	// Седрца
	for (int i = 0; i < GamePlayerHearts.size(); i++)
	{
		RenderTextureCentered(Textures[GIMG_SPRITES_HEART], GamePlayerHearts[i].x, GamePlayerHearts[i].y, 32, 32, 90);
	}
	// Вводимый текст    
	RenderText(WordInput.c_str(), NormalFont, SCREENPOS_X_CENTERED, SCREENPOS_Y_CENTERED / 4, ColorDefaultBlue, true);
	char ScoreStrTemp[12];
	_itoa_s(MainPlayer.Score, ScoreStrTemp, 12, 10);
	RenderText(ScoreStrTemp, NormalFont, SCREENPOS_X_CENTERED, TRUE_RESOLUTION_Y - 50, ColorDefaultBlue, true);
	// ФПС, если включён
	if (FPSCounter) {
		RenderText(FPSString, NormalFont, 0, 0, 0, 0, 0, 255, false);
	}

	// Если счётчик FPS включён, отобразить FPS
	if (FPSCounter == true && TickCurrent - TicksToSecond_FPS >= 1000)
	{
		TicksToSecond_FPS = TickCurrent;
		_itoa_s(FramesPerSecondPresent, FPSString, 10);
		FramesPerSecondPresent = 0;
	}
}