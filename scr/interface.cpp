#include "main.h"

Sliders GameSliders;

// �������� ���������
void InitSliders(Sliders& GameSliders)
{
	Slider SliderToAdd;
	// SFX
	SliderToAdd.TextID = TXT_SFXVOLUME;
	SliderToAdd.ID = SLDR_SFX;
	SliderToAdd.Pos = { TRUE_RESOLUTION_X / 2.0, TRUE_RESOLUTION_Y / 2.0 - TRUE_RESOLUTION_Y / 8.0 };
	SliderToAdd.Heigth = 40;
	SliderToAdd.Width = TRUE_RESOLUTION_X * 0.75;
	SliderToAdd.Collision = UpdateCollision(SliderToAdd.Pos, SliderToAdd.Heigth, SliderToAdd.Width);
	SliderToAdd.Value = 0;
	GameSliders.push_back(SliderToAdd);
	// Music
	SliderToAdd.TextID = TXT_MUSICVOLUME;
	SliderToAdd.ID = SLDR_MUSIC;
	SliderToAdd.Pos = { TRUE_RESOLUTION_X / 2.0, TRUE_RESOLUTION_Y / 2.0 };
	SliderToAdd.Heigth = 40;
	SliderToAdd.Width = TRUE_RESOLUTION_X * 0.75;
	SliderToAdd.Collision = UpdateCollision(SliderToAdd.Pos, SliderToAdd.Heigth, SliderToAdd.Width);
	SliderToAdd.Value = 0;
	GameSliders.push_back(SliderToAdd);
}

void SetButtonsSize(buttons& GameButtons, TTF_Font* Font)
{
	for (int i = 0; i < GameButtons.size(); i++)
	{
		TTF_SizeUTF8(Font, Text[GameButtons[i].TextID].c_str(), &GameButtons[i].Width, &GameButtons[i].Heigth);
		GameButtons[i].Heigth = TRUE_RESOLUTION_Y / 10;
		GameButtons[i].Width += 50;
		GameButtons[i].Collision = UpdateCollision(GameButtons[i].Pos, GameButtons[i].Heigth, GameButtons[i].Width);
	}
}
//�������� ������
void InitButtons(buttons& GameButtons)
{

	button ButtonToAdd;
	// Ingame Continue    
	ButtonToAdd.ID = BTN_INGAME_CONTINUE;
	ButtonToAdd.Pos = { (double)TRUE_RESOLUTION_X / 2, (double)TRUE_RESOLUTION_Y / 4 + (double)TRUE_RESOLUTION_Y / 8 };
	ButtonToAdd.TextID = TXT_CONTINUE;
	GameButtons.push_back(ButtonToAdd);
	// Ingame Restart
	ButtonToAdd.ID = BTN_INGAME_RESTART;
	ButtonToAdd.Pos = { (double)TRUE_RESOLUTION_X / 2, (double)TRUE_RESOLUTION_Y / 4 + (double)TRUE_RESOLUTION_Y / 4 };
	ButtonToAdd.TextID = TXT_RESTART;
	GameButtons.push_back(ButtonToAdd);
	// Options
	ButtonToAdd.ID = BTN_INGAME_OPTIONS;
	ButtonToAdd.Pos = { (double)TRUE_RESOLUTION_X / 2, (double)TRUE_RESOLUTION_Y / 2 + (double)TRUE_RESOLUTION_Y / 8 };
	ButtonToAdd.TextID = TXT_OPTIONS;
	GameButtons.push_back(ButtonToAdd);
	// Ingame Quit to Main Menu
	ButtonToAdd.ID = BTN_INGAME_QUIT_MAINMENU;
	ButtonToAdd.Pos = { (double)TRUE_RESOLUTION_X / 2, (double)TRUE_RESOLUTION_Y / 4 + (double)TRUE_RESOLUTION_Y / 2 };
	ButtonToAdd.TextID = TXT_QUITMAINMENU;
	GameButtons.push_back(ButtonToAdd);
	// Ingame Quit  to Desktop  
	ButtonToAdd.ID = BTN_INGAME_QUIT_DESKTOP;
	ButtonToAdd.Pos = { (double)TRUE_RESOLUTION_X / 2, (double)3 * TRUE_RESOLUTION_Y / 8 + (double)TRUE_RESOLUTION_Y / 2 };
	ButtonToAdd.TextID = TXT_QUITDESKTOP;
	GameButtons.push_back(ButtonToAdd);
	// Mainmenu play classic    
	ButtonToAdd.ID = BTN_MENU_CLASSIC;
	ButtonToAdd.Pos = { (double)TRUE_RESOLUTION_X / 2, (double)TRUE_RESOLUTION_Y / 4 + (double)TRUE_RESOLUTION_Y / 8 };
	ButtonToAdd.TextID = TXT_PLAYCLASSIC;
	GameButtons.push_back(ButtonToAdd);
	// Mainmenu play arithmetic
	ButtonToAdd.ID = BTN_MENU_ARITHMETIC;
	ButtonToAdd.Pos = { (double)TRUE_RESOLUTION_X / 2, (double)TRUE_RESOLUTION_Y / 4 + (double)TRUE_RESOLUTION_Y / 4 };
	ButtonToAdd.TextID = TXT_PLAYARITHMETIC;
	GameButtons.push_back(ButtonToAdd);
	// Mainmenu scores
	ButtonToAdd.ID = BTN_MENU_SCORES;
	ButtonToAdd.Pos = { (double)TRUE_RESOLUTION_X / 2, (double)TRUE_RESOLUTION_Y / 2 + (double)TRUE_RESOLUTION_Y / 8 };
	ButtonToAdd.TextID = TXT_SCORES;
	GameButtons.push_back(ButtonToAdd);
	// Options
	ButtonToAdd.ID = BTN_MENU_OPTIONS;
	ButtonToAdd.Pos = { (double)TRUE_RESOLUTION_X / 2, (double)TRUE_RESOLUTION_Y / 4 + (double)TRUE_RESOLUTION_Y / 2 };
	ButtonToAdd.TextID = TXT_OPTIONS;
	GameButtons.push_back(ButtonToAdd);
	// Mainmenu Quit  to Desktop  
	ButtonToAdd.ID = BTN_MENU_QUIT_DESKTOP;
	ButtonToAdd.Pos = { (double)TRUE_RESOLUTION_X / 2, (double)3 * TRUE_RESOLUTION_Y / 8 + (double)TRUE_RESOLUTION_Y / 2 };
	ButtonToAdd.TextID = TXT_QUITDESKTOP;
	GameButtons.push_back(ButtonToAdd);
	// Difficulty Easy
	ButtonToAdd.ID = BTN_DIFFICULTY_EASY;
	ButtonToAdd.Pos = { (double)TRUE_RESOLUTION_X / 2, (double)TRUE_RESOLUTION_Y / 4 + (double)TRUE_RESOLUTION_Y / 8 };
	ButtonToAdd.TextID = TXT_EASY;
	GameButtons.push_back(ButtonToAdd);
	// Difficulty Normal
	ButtonToAdd.ID = BTN_DIFFICULTY_NORMAL;
	ButtonToAdd.Pos = { (double)TRUE_RESOLUTION_X / 2, (double)TRUE_RESOLUTION_Y / 4 + (double)TRUE_RESOLUTION_Y / 4 };
	ButtonToAdd.TextID = TXT_NORMAL;
	GameButtons.push_back(ButtonToAdd);
	// Difficulty Hard
	ButtonToAdd.ID = BTN_DIFFICULTY_HARD;
	ButtonToAdd.Pos = { (double)TRUE_RESOLUTION_X / 2, (double)TRUE_RESOLUTION_Y / 2 + (double)TRUE_RESOLUTION_Y / 8 };
	ButtonToAdd.TextID = TXT_HARD;
	GameButtons.push_back(ButtonToAdd);
	// Difficulty Back
	ButtonToAdd.ID = BTN_DIFFICULTY_BACK;
	ButtonToAdd.Pos = { (double)TRUE_RESOLUTION_X / 2, (double)TRUE_RESOLUTION_Y / 2 + (double)TRUE_RESOLUTION_Y / 16 + (double)TRUE_RESOLUTION_Y / 4 };
	ButtonToAdd.TextID = TXT_BACK;
	GameButtons.push_back(ButtonToAdd);
	// Dead Retry
	ButtonToAdd.ID = BTN_DEAD_RETRY;
	ButtonToAdd.Pos = { (double)TRUE_RESOLUTION_X / 2, (double)TRUE_RESOLUTION_Y / 2 };
	ButtonToAdd.TextID = TXT_RETRY;
	GameButtons.push_back(ButtonToAdd);
	// Difficulty  Quit to Main Menu
	ButtonToAdd.ID = BTN_DEAD_QUIT_MAINMENU;
	ButtonToAdd.Pos = { (double)TRUE_RESOLUTION_X / 2, (double)TRUE_RESOLUTION_Y / 2 + (double)TRUE_RESOLUTION_Y / 8 };
	ButtonToAdd.TextID = TXT_BACKMAINMENU;
	GameButtons.push_back(ButtonToAdd);
	// Scores Back
	ButtonToAdd.ID = BTN_SCORES_BACK;
	ButtonToAdd.Pos = { (double)TRUE_RESOLUTION_X / 2, (double)TRUE_RESOLUTION_Y - (double)TRUE_RESOLUTION_Y / 8 };
	ButtonToAdd.TextID = TXT_BACK;
	GameButtons.push_back(ButtonToAdd);
	// Options Back
	ButtonToAdd.ID = BTN_OPTIONS_BACK;
	ButtonToAdd.Pos = { (double)TRUE_RESOLUTION_X / 2, (double)TRUE_RESOLUTION_Y / 2 + (double)TRUE_RESOLUTION_Y / 16 + (double)TRUE_RESOLUTION_Y / 4 };
	ButtonToAdd.TextID = TXT_BACK;
	GameButtons.push_back(ButtonToAdd);
	// Options Back
	ButtonToAdd.ID = BTN_EN;
	ButtonToAdd.Pos = { (double)TRUE_RESOLUTION_X / 2 + TRUE_RESOLUTION_X / 8.0, (double)TRUE_RESOLUTION_Y / 2 + (double)TRUE_RESOLUTION_Y / 8 };
	ButtonToAdd.TextID = TXT_EN;
	GameButtons.push_back(ButtonToAdd);
	// Options Back
	ButtonToAdd.ID = BTN_RU;
	ButtonToAdd.Pos = { (double)TRUE_RESOLUTION_X / 2 - TRUE_RESOLUTION_X / 8.0, (double)TRUE_RESOLUTION_Y / 2 + (double)TRUE_RESOLUTION_Y / 8 };
	ButtonToAdd.TextID = TXT_RU;
	GameButtons.push_back(ButtonToAdd);

	SetButtonsSize(GameButtons, MenuFont);
}

void OptionsMenu(bool FromPause = false)
{
	Uint32 TicksToNextFrame = SDL_GetTicks();
	Uint32 TickCurrent = SDL_GetTicks();

	while (true)
	{
		// ����� ���� ������� ����� �� �����������
		if (TickCurrent - SDL_GetTicks() < REPEAT_DELAY)
		{
			SDL_Delay(REPEAT_DELAY);
		}
		if (TickCurrent - TicksToNextFrame > (1.0 / FramesPerSecondTarget) * 1000)
		{
			TicksToNextFrame = TickCurrent;
			DrawOptionsFrame(FromPause);
			SDL_RenderPresent(RendererPrimary);
			SDL_RenderClear(RendererPrimary);
		}
		TickCurrent = SDL_GetTicks();
		SDL_Event Event;
		if (SDL_PollEvent(&Event))
		{
			if (Event.type == SDL_WINDOWEVENT && Event.window.event == SDL_WINDOWEVENT_RESIZED) {
				UpdateWindowResolution(Event);
			}
			if (Event.type == SDL_WINDOWEVENT && Event.window.event == SDL_WINDOWEVENT_MAXIMIZED) {
				SDL_SetWindowPosition(WindowPrimary, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
			}
			if (Event.type == SDL_QUIT)
			{
				QuitGame();
			}

			InputCode MouseCode = ReadMouseOptions(Event, GameButtons, GameSliders);
			InputCode KeyCode = ReadKeysOptions(Event);
			if (MouseCode == InputCode::OPTIONS_BACK || KeyCode == InputCode::OPTIONS_BACK)
			{
				SDL_RWops* File = SDL_RWFromFile("data.bin", "r+");
				if (File == nullptr)
				{
					WriteInLog("[ERROR] Unable to save options to the file \"data.bin\"!");
				}
				else
				{
					SDL_RWseek(File, sizeof(highscore) * GameHighscoresSize, SEEK_SET);
					SDL_RWwrite(File, &GameSliders[SLDR_SFX].Value, sizeof(double), 1);
					SDL_RWwrite(File, &GameSliders[SLDR_MUSIC].Value, sizeof(double), 1);
					SDL_RWclose(File);
				}
				return;
			}
		}
	}
}

PauseMenuCode PauseMenu()
{
	Uint32 TicksToNextFrame = SDL_GetTicks();
	Uint32 TickCurrent = SDL_GetTicks();

	while (true)
	{
		// ����� ���� ������� ����� �� �����������
		if (TickCurrent - SDL_GetTicks() < REPEAT_DELAY)
		{
			SDL_Delay(REPEAT_DELAY);
		}
		if (TickCurrent - TicksToNextFrame > (1.0 / FramesPerSecondTarget) * 1000)
		{
			TicksToNextFrame = TickCurrent;
			DrawPauseMenuFrame();
			SDL_RenderPresent(RendererPrimary);
			SDL_RenderClear(RendererPrimary);
		}
		TickCurrent = SDL_GetTicks();
		SDL_Event Event;
		if (SDL_PollEvent(&Event))
		{
			if (Event.type == SDL_WINDOWEVENT && Event.window.event == SDL_WINDOWEVENT_RESIZED) {
				UpdateWindowResolution(Event);
			}
			if (Event.type == SDL_WINDOWEVENT && Event.window.event == SDL_WINDOWEVENT_MAXIMIZED) {
				SDL_SetWindowPosition(WindowPrimary, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
			}
			if (Event.type == SDL_QUIT)
			{
				QuitGame();
			}

			InputCode KeyCode = ReadKeysPause(Event);
			InputCode MouseCode = ReadMousePause(Event, GameButtons);
			if (KeyCode == InputCode::PAUSE_CONTINUE || MouseCode == InputCode::PAUSE_CONTINUE)
			{
				return PauseMenuCode::CONTINUE;
			}
			else if (MouseCode == InputCode::PAUSE_RESTART)
			{
				return PauseMenuCode::RESTART;
			}
			else if (MouseCode == InputCode::PAUSE_OPTIONS)
			{
				OptionsMenu(true);
			}
			else if (MouseCode == InputCode::PAUSE_TO_DESKTOP)
			{
				return PauseMenuCode::TO_DESKTOP;
			}
			else if (MouseCode == InputCode::PAUSE_TO_MAIN_MENU)
			{
				return PauseMenuCode::TO_MAIN_MENU;
			}
		}
	}
}

DifficultyCode DifficultyMenu()
{
	Uint32 TicksToNextFrame = SDL_GetTicks();
	Uint32 TickCurrent = SDL_GetTicks();

	while (true)
	{
		// ����� ���� ������� ����� �� �����������
		if (TickCurrent - SDL_GetTicks() < REPEAT_DELAY)
		{
			SDL_Delay(REPEAT_DELAY);
		}
		if (TickCurrent - TicksToNextFrame > (1.0 / FramesPerSecondTarget) * 1000)
		{
			TicksToNextFrame = TickCurrent;
			DrawDifficultyFrame();
			SDL_RenderPresent(RendererPrimary);
			SDL_RenderClear(RendererPrimary);
		}
		TickCurrent = SDL_GetTicks();
		SDL_Event Event;
		if (SDL_PollEvent(&Event))
		{
			if (Event.type == SDL_WINDOWEVENT && Event.window.event == SDL_WINDOWEVENT_RESIZED) {
				UpdateWindowResolution(Event);
			}
			if (Event.type == SDL_WINDOWEVENT && Event.window.event == SDL_WINDOWEVENT_MAXIMIZED) {
				SDL_SetWindowPosition(WindowPrimary, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
			}
			if (Event.type == SDL_QUIT)
			{
				QuitGame();
			}

			InputCode KeyCode = ReadKeysDifficulty(Event);
			InputCode MouseCode = ReadMouseDifficuly(Event, GameButtons);
			if (KeyCode == InputCode::DIFFICULTY_BACK || MouseCode == InputCode::DIFFICULTY_BACK)
			{
				return DifficultyCode::BACK;
			}
			else if (MouseCode == InputCode::DIFFICULTY_EASY)
			{
				return DifficultyCode::EASY;
			}
			else if (MouseCode == InputCode::DIFFICULTY_NORMAL)
			{
				return DifficultyCode::NORMAL;
			}
			else if (MouseCode == InputCode::DIFFICULTY_HARD)
			{
				return DifficultyCode::HARD;
			}
		}
	}
}

void HighscoresMenu()
{
	Uint32 TicksToNextFrame = SDL_GetTicks();
	Uint32 TickCurrent = SDL_GetTicks();

	while (true)
	{
		// ����� ���� ������� ����� �� �����������
		if (TickCurrent - SDL_GetTicks() < REPEAT_DELAY)
		{
			SDL_Delay(REPEAT_DELAY);
		}
		if (TickCurrent - TicksToNextFrame > (1.0 / FramesPerSecondTarget) * 1000)
		{
			TicksToNextFrame = TickCurrent;
			DrawHighscoresFrame();
			SDL_RenderPresent(RendererPrimary);
			SDL_RenderClear(RendererPrimary);
		}
		TickCurrent = SDL_GetTicks();
		SDL_Event Event;
		if (SDL_PollEvent(&Event))
		{
			if (Event.type == SDL_WINDOWEVENT && Event.window.event == SDL_WINDOWEVENT_RESIZED) {
				UpdateWindowResolution(Event);
			}
			if (Event.type == SDL_WINDOWEVENT && Event.window.event == SDL_WINDOWEVENT_MAXIMIZED) {
				SDL_SetWindowPosition(WindowPrimary, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
			}
			if (Event.type == SDL_QUIT)
			{
				QuitGame();
			}

			InputCode KeyCode = ReadKeysScores(Event);
			InputCode MouseCode = ReadMouseScores(Event, GameButtons);
			if (KeyCode == InputCode::SCORES_BACK || MouseCode == InputCode::SCORES_BACK)
			{
				return;
			}
		}
	}
}

void HighscoreEnterMenu(DifficultyCode Difficulty, bool ArithmeticMode)
{
	Uint32 TicksToNextFrame = SDL_GetTicks();
	Uint32 TickCurrent = SDL_GetTicks();

	std::string WordInput;
	while (true)
	{
		// ����� ���� ������� ����� �� �����������
		if (TickCurrent - SDL_GetTicks() < REPEAT_DELAY)
		{
			SDL_Delay(REPEAT_DELAY);
		}
		if (TickCurrent - TicksToNextFrame > (1.0 / FramesPerSecondTarget) * 1000)
		{
			TicksToNextFrame = TickCurrent;
			DrawHighscoreEnterFrame(WordInput);
			SDL_RenderPresent(RendererPrimary);
			SDL_RenderClear(RendererPrimary);
		}
		TickCurrent = SDL_GetTicks();
		SDL_Event Event;
		if (SDL_PollEvent(&Event))
		{
			if (Event.type == SDL_WINDOWEVENT && Event.window.event == SDL_WINDOWEVENT_RESIZED) {
				UpdateWindowResolution(Event);
			}
			if (Event.type == SDL_WINDOWEVENT && Event.window.event == SDL_WINDOWEVENT_MAXIMIZED) {
				SDL_SetWindowPosition(WindowPrimary, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
			}
			if (Event.type == SDL_QUIT)
			{
				QuitGame();
			}

			InputCode KeyCode = ReadKeysScoreEnter(Event, WordInput);
			if (KeyCode == InputCode::SCORESENTER_SKIP)
			{
				return;
			}
			else if (KeyCode == InputCode::SCORESENTER_ENTER)
			{
				bool BreakCycle = false;
				for (int i = 0; i < GameHighscoresSize; i++)
				{
					if (MainPlayer.Score > GameHighscores[i].Score)
					{
						BreakCycle = true;
						for (int j = GameHighscoresSize - 1; j > i; j--)
						{
							GameHighscores[j] = GameHighscores[j - 1];
						}
						for (int j = 0; j < 16; j++)
						{
							GameHighscores[i].Name[j] = '\0';
						}
						for (int j = 0; j < 15 && j < WordInput.length(); j++)
						{
							GameHighscores[i].Name[j] = WordInput[j];
						}
						GameHighscores[i].Score = MainPlayer.Score;
						GameHighscores[i].Difficulty = (int)Difficulty;
						GameHighscores[i].Mode = ArithmeticMode;
					}
					if (BreakCycle == true)
					{
						break;
					}
				}
				SDL_RWops* File = SDL_RWFromFile("data.bin", "w");
				for (int i = 0; i < GameHighscoresSize; i++)
				{
					SDL_RWwrite(File, &GameHighscores[i].Name, sizeof(char), 16);
					SDL_RWwrite(File, &GameHighscores[i].Score, sizeof(int), 1);
					SDL_RWwrite(File, &GameHighscores[i].Difficulty, sizeof(int), 1);
					SDL_RWwrite(File, &GameHighscores[i].Mode, sizeof(int), 1);
				}
				SDL_RWclose(File);
				return;
			}
		}
	}
}

DeadMenuCode DeadMenu(SDL_Texture* BackgroundTexture, DifficultyCode Difficulty, bool ArithmeticMode)
{
	Uint32 TicksToNextFrame = SDL_GetTicks();
	Uint32 TickCurrent = SDL_GetTicks();

	while (true)
	{
		// ����� ���� ������� ����� �� �����������
		if (TickCurrent - SDL_GetTicks() < REPEAT_DELAY)
		{
			SDL_Delay(REPEAT_DELAY);
		}
		if (TickCurrent - TicksToNextFrame > (1.0 / FramesPerSecondTarget) * 1000)
		{
			TicksToNextFrame = TickCurrent;
			DrawDeadFrame(BackgroundTexture);
			SDL_RenderPresent(RendererPrimary);
			SDL_RenderClear(RendererPrimary);
		}
		TickCurrent = SDL_GetTicks();
		SDL_Event Event;
		if (SDL_PollEvent(&Event))
		{
			if (Event.type == SDL_WINDOWEVENT && Event.window.event == SDL_WINDOWEVENT_RESIZED) {
				UpdateWindowResolution(Event);
			}
			if (Event.type == SDL_WINDOWEVENT && Event.window.event == SDL_WINDOWEVENT_MAXIMIZED) {
				SDL_SetWindowPosition(WindowPrimary, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
			}
			if (Event.type == SDL_QUIT)
			{
				QuitGame();
			}

			InputCode KeyCode = ReadKeysDead(Event);
			InputCode MouseCode = ReadMouseDead(Event, GameButtons);
			if (KeyCode == InputCode::DEAD_RETRY || MouseCode == InputCode::DEAD_RETRY)
			{
				return DeadMenuCode::RETRY;
			}
			else if (KeyCode == InputCode::DEAD_TO_MAIN_MENU || MouseCode == InputCode::DEAD_TO_MAIN_MENU)
			{
				for (int i = 0; i < GameHighscoresSize; i++)
				{
					if (GameHighscores[i].Score != 0 && MainPlayer.Score > GameHighscores[i].Score && MainPlayer.Score != 0)
					{
						HighscoreEnterMenu(Difficulty, ArithmeticMode);
						break;
					}
				}
				return DeadMenuCode::TO_MAIN_MENU;
			}
		}
	}
}

void MainMenu()
{
	Uint32 TicksToNextFrame = SDL_GetTicks();
	Uint32 TickCurrent = SDL_GetTicks();

	while (true)
	{
		// ����� ���� ������� ����� �� �����������
		if (TickCurrent - SDL_GetTicks() < REPEAT_DELAY)
		{
			SDL_Delay(REPEAT_DELAY);
		}
		if (TickCurrent - TicksToNextFrame > (1.0 / FramesPerSecondTarget) * 1000)
		{
			TicksToNextFrame = TickCurrent;
			DrawMainMenuFrame();
			SDL_RenderPresent(RendererPrimary);
			SDL_RenderClear(RendererPrimary);
		}
		TickCurrent = SDL_GetTicks();
		SDL_Event Event;
		if (SDL_PollEvent(&Event))
		{
			if (Event.type == SDL_WINDOWEVENT && Event.window.event == SDL_WINDOWEVENT_RESIZED) {
				UpdateWindowResolution(Event);
			}
			if (Event.type == SDL_WINDOWEVENT && Event.window.event == SDL_WINDOWEVENT_MAXIMIZED) {
				SDL_SetWindowPosition(WindowPrimary, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
			}
			if (Event.type == SDL_QUIT)
			{
				QuitGame();
			}

			InputCode MouseCode = ReadMouseMain(Event, GameButtons);
			if (MouseCode == InputCode::MAIN_TO_DESKTOP)
			{
				QuitGame();
			}
			else if (MouseCode == InputCode::MAIN_CLASSIC)
			{
				DifficultyCode Difficulty = DifficultyMenu();
				if (Difficulty != DifficultyCode::BACK)
				{
					GameSession(false, Difficulty);
				}
			}
			else if (MouseCode == InputCode::MAIN_ARITHMETIC)
			{
				DifficultyCode Difficulty = DifficultyMenu();
				if (Difficulty != DifficultyCode::BACK)
				{
					GameSession(true, Difficulty);
				}
			}
			else if (MouseCode == InputCode::MAIN_SCORES)
			{
				HighscoresMenu();
			}
			else if (MouseCode == InputCode::MAIN_OPTIONS)
			{
				OptionsMenu();
			}
		}
	}
}