#include "main.h"

Sliders GameSliders;

// Создание слайдеров
void InitSliders(Sliders& GameSliders)
{
	Slider SliderToAdd;
	// SFX
	SliderToAdd.Text = "SFX Volume: ";
	SliderToAdd.ID = SLDR_SFX;
	SliderToAdd.Pos = { TRUE_RESOLUTION_X / 2.0, TRUE_RESOLUTION_Y / 2.0 - TRUE_RESOLUTION_Y / 8.0 };
	SliderToAdd.Heigth = 40;
	SliderToAdd.Width = TRUE_RESOLUTION_X * 0.75;
	SliderToAdd.Collision = UpdateCollision(SliderToAdd.Pos, SliderToAdd.Heigth, SliderToAdd.Width);
	SliderToAdd.Value = SFXVolume;
	GameSliders.push_back(SliderToAdd);
	// Music
	SliderToAdd.Text = "Music Volume: ";
	SliderToAdd.ID = SLDR_MUSIC;
	SliderToAdd.Pos = { TRUE_RESOLUTION_X / 2.0, TRUE_RESOLUTION_Y / 2.0};
	SliderToAdd.Heigth = 40;
	SliderToAdd.Width = TRUE_RESOLUTION_X * 0.75;
	SliderToAdd.Collision = UpdateCollision(SliderToAdd.Pos, SliderToAdd.Heigth, SliderToAdd.Width);
	SliderToAdd.Value = MusicVolume;
	GameSliders.push_back(SliderToAdd);
}

//Создание кнопок
void InitButtons() {

	button ButtonToAdd;
	// Ingame Continue    
	ButtonToAdd.ID = BTN_INGAME_CONTINUE;
	ButtonToAdd.Pos = { (double)TRUE_RESOLUTION_X / 2, (double)TRUE_RESOLUTION_Y / 4 + (double)TRUE_RESOLUTION_Y / 8 };
	ButtonToAdd.Text = "Continue";
	ButtonToAdd.Heigth = TRUE_RESOLUTION_Y / 10;
	ButtonToAdd.Width = ButtonToAdd.Text.length() * 50;
	ButtonToAdd.Collision = UpdateCollision(ButtonToAdd.Pos, ButtonToAdd.Heigth, ButtonToAdd.Width);
	GameButtons.push_back(ButtonToAdd);
	// Ingame Restart
	ButtonToAdd.ID = BTN_INGAME_RESTART;
	ButtonToAdd.Pos = { (double)TRUE_RESOLUTION_X / 2, (double)TRUE_RESOLUTION_Y / 4 + (double)TRUE_RESOLUTION_Y / 4 };
	ButtonToAdd.Text = "Restart";
	ButtonToAdd.Heigth = TRUE_RESOLUTION_Y / 10;
	ButtonToAdd.Width = ButtonToAdd.Text.length() * 50;
	ButtonToAdd.Collision = UpdateCollision(ButtonToAdd.Pos, ButtonToAdd.Heigth, ButtonToAdd.Width);
	GameButtons.push_back(ButtonToAdd);
	// Options
	ButtonToAdd.ID = BTN_INGAME_OPTIONS;
	ButtonToAdd.Pos = { (double)TRUE_RESOLUTION_X / 2, (double)TRUE_RESOLUTION_Y / 2 + (double)TRUE_RESOLUTION_Y / 8 };
	ButtonToAdd.Text = "Options";
	ButtonToAdd.Heigth = TRUE_RESOLUTION_Y / 10;
	ButtonToAdd.Width = ButtonToAdd.Text.length() * 50;
	ButtonToAdd.Collision = UpdateCollision(ButtonToAdd.Pos, ButtonToAdd.Heigth, ButtonToAdd.Width);
	GameButtons.push_back(ButtonToAdd);
	// Ingame Quit to Main Menu
	ButtonToAdd.ID = BTN_INGAME_QUIT_MAINMENU;
	ButtonToAdd.Pos = { (double)TRUE_RESOLUTION_X / 2, (double)TRUE_RESOLUTION_Y / 4 + (double)TRUE_RESOLUTION_Y / 2 };
	ButtonToAdd.Text = "Quit to Main Menu";
	ButtonToAdd.Heigth = TRUE_RESOLUTION_Y / 10;
	ButtonToAdd.Width = ButtonToAdd.Text.length() * 50;
	ButtonToAdd.Collision = UpdateCollision(ButtonToAdd.Pos, ButtonToAdd.Heigth, ButtonToAdd.Width);
	GameButtons.push_back(ButtonToAdd);
	// Ingame Quit  to Desktop  
	ButtonToAdd.ID = BTN_INGAME_QUIT_DESKTOP;
	ButtonToAdd.Pos = { (double)TRUE_RESOLUTION_X / 2, (double)3 * TRUE_RESOLUTION_Y / 8 + (double)TRUE_RESOLUTION_Y / 2 };
	ButtonToAdd.Text = "Quit to Desktop";
	ButtonToAdd.Heigth = TRUE_RESOLUTION_Y / 10;
	ButtonToAdd.Width = ButtonToAdd.Text.length() * 50;
	ButtonToAdd.Collision = UpdateCollision(ButtonToAdd.Pos, ButtonToAdd.Heigth, ButtonToAdd.Width);
	GameButtons.push_back(ButtonToAdd);
	// Mainmenu play classic    
	ButtonToAdd.ID = BTN_MENU_CLASSIC;
	ButtonToAdd.Pos = { (double)TRUE_RESOLUTION_X / 2, (double)TRUE_RESOLUTION_Y / 4 + (double)TRUE_RESOLUTION_Y / 8 };
	ButtonToAdd.Text = "Play Classic";
	ButtonToAdd.Heigth = TRUE_RESOLUTION_Y / 10;
	ButtonToAdd.Width = ButtonToAdd.Text.length() * 50;
	ButtonToAdd.Collision = UpdateCollision(ButtonToAdd.Pos, ButtonToAdd.Heigth, ButtonToAdd.Width);
	GameButtons.push_back(ButtonToAdd);
	// Mainmenu play arithmetic
	ButtonToAdd.ID = BTN_MENU_ARITHMETIC;
	ButtonToAdd.Pos = { (double)TRUE_RESOLUTION_X / 2, (double)TRUE_RESOLUTION_Y / 4 + (double)TRUE_RESOLUTION_Y / 4 };
	ButtonToAdd.Text = "Play Arithmetic";
	ButtonToAdd.Heigth = TRUE_RESOLUTION_Y / 10;
	ButtonToAdd.Width = ButtonToAdd.Text.length() * 50;
	ButtonToAdd.Collision = UpdateCollision(ButtonToAdd.Pos, ButtonToAdd.Heigth, ButtonToAdd.Width);
	GameButtons.push_back(ButtonToAdd);
	// Mainmenu scores
	ButtonToAdd.ID = BTN_MENU_SCORES;
	ButtonToAdd.Pos = { (double)TRUE_RESOLUTION_X / 2, (double)TRUE_RESOLUTION_Y / 2 + (double)TRUE_RESOLUTION_Y / 8 };
	ButtonToAdd.Text = "Scores";
	ButtonToAdd.Heigth = TRUE_RESOLUTION_Y / 10;
	ButtonToAdd.Width = ButtonToAdd.Text.length() * 50;
	ButtonToAdd.Collision = UpdateCollision(ButtonToAdd.Pos, ButtonToAdd.Heigth, ButtonToAdd.Width);
	GameButtons.push_back(ButtonToAdd);
	// Options
	ButtonToAdd.ID = BTN_MENU_OPTIONS;
	ButtonToAdd.Pos = { (double)TRUE_RESOLUTION_X / 2, (double)TRUE_RESOLUTION_Y / 4 + (double)TRUE_RESOLUTION_Y / 2 };
	ButtonToAdd.Text = "Options";
	ButtonToAdd.Heigth = TRUE_RESOLUTION_Y / 10;
	ButtonToAdd.Width = ButtonToAdd.Text.length() * 50;
	ButtonToAdd.Collision = UpdateCollision(ButtonToAdd.Pos, ButtonToAdd.Heigth, ButtonToAdd.Width);
	GameButtons.push_back(ButtonToAdd);
	// Mainmenu Quit  to Desktop  
	ButtonToAdd.ID = BTN_MENU_QUIT_DESKTOP;
	ButtonToAdd.Pos = { (double)TRUE_RESOLUTION_X / 2, (double)3 * TRUE_RESOLUTION_Y / 8 + (double)TRUE_RESOLUTION_Y / 2 };
	ButtonToAdd.Text = "Quit to Desktop";
	ButtonToAdd.Heigth = TRUE_RESOLUTION_Y / 10;
	ButtonToAdd.Width = ButtonToAdd.Text.length() * 50;
	ButtonToAdd.Collision = UpdateCollision(ButtonToAdd.Pos, ButtonToAdd.Heigth, ButtonToAdd.Width);
	GameButtons.push_back(ButtonToAdd);
	// Difficulty Easy
	ButtonToAdd.ID = BTN_DIFFICULTY_EASY;
	ButtonToAdd.Pos = { (double)TRUE_RESOLUTION_X / 2, (double)TRUE_RESOLUTION_Y / 4 + (double)TRUE_RESOLUTION_Y / 8 };
	ButtonToAdd.Text = "Easy";
	ButtonToAdd.Heigth = TRUE_RESOLUTION_Y / 10;
	ButtonToAdd.Width = ButtonToAdd.Text.length() * 60;
	ButtonToAdd.Collision = UpdateCollision(ButtonToAdd.Pos, ButtonToAdd.Heigth, ButtonToAdd.Width);
	GameButtons.push_back(ButtonToAdd);
	// Difficulty Normal
	ButtonToAdd.ID = BTN_DIFFICULTY_NORMAL;
	ButtonToAdd.Pos = { (double)TRUE_RESOLUTION_X / 2, (double)TRUE_RESOLUTION_Y / 4 + (double)TRUE_RESOLUTION_Y / 4 };
	ButtonToAdd.Text = "Normal";
	ButtonToAdd.Heigth = TRUE_RESOLUTION_Y / 10;
	ButtonToAdd.Width = ButtonToAdd.Text.length() * 60;
	ButtonToAdd.Collision = UpdateCollision(ButtonToAdd.Pos, ButtonToAdd.Heigth, ButtonToAdd.Width);
	GameButtons.push_back(ButtonToAdd);
	// Difficulty Hard
	ButtonToAdd.ID = BTN_DIFFICULTY_HARD;
	ButtonToAdd.Pos = { (double)TRUE_RESOLUTION_X / 2, (double)TRUE_RESOLUTION_Y / 2 + (double)TRUE_RESOLUTION_Y / 8 };
	ButtonToAdd.Text = "Hard";
	ButtonToAdd.Heigth = TRUE_RESOLUTION_Y / 10;
	ButtonToAdd.Width = ButtonToAdd.Text.length() * 60;
	ButtonToAdd.Collision = UpdateCollision(ButtonToAdd.Pos, ButtonToAdd.Heigth, ButtonToAdd.Width);
	GameButtons.push_back(ButtonToAdd);
	// Difficulty Back
	ButtonToAdd.ID = BTN_DIFFICULTY_BACK;
	ButtonToAdd.Pos = { (double)TRUE_RESOLUTION_X / 2, (double)TRUE_RESOLUTION_Y / 2 + (double)TRUE_RESOLUTION_Y / 16 + (double)TRUE_RESOLUTION_Y / 4 };
	ButtonToAdd.Text = "Back";
	ButtonToAdd.Heigth = TRUE_RESOLUTION_Y / 10;
	ButtonToAdd.Width = ButtonToAdd.Text.length() * 60;
	ButtonToAdd.Collision = UpdateCollision(ButtonToAdd.Pos, ButtonToAdd.Heigth, ButtonToAdd.Width);
	GameButtons.push_back(ButtonToAdd);
	// Dead Retry
	ButtonToAdd.ID = BTN_DEAD_RETRY;
	ButtonToAdd.Pos = { (double)TRUE_RESOLUTION_X / 2, (double)TRUE_RESOLUTION_Y / 2 };
	ButtonToAdd.Text = "Retry";
	ButtonToAdd.Heigth = TRUE_RESOLUTION_Y / 10;
	ButtonToAdd.Width = ButtonToAdd.Text.length() * 50;
	ButtonToAdd.Collision = UpdateCollision(ButtonToAdd.Pos, ButtonToAdd.Heigth, ButtonToAdd.Width);
	GameButtons.push_back(ButtonToAdd);
	// Difficulty  Quit to Main Menu
	ButtonToAdd.ID = BTN_DEAD_QUIT_MAINMENU;
	ButtonToAdd.Pos = { (double)TRUE_RESOLUTION_X / 2, (double)TRUE_RESOLUTION_Y / 2 + (double)TRUE_RESOLUTION_Y / 8 };
	ButtonToAdd.Text = "Back to Main Menu";
	ButtonToAdd.Heigth = TRUE_RESOLUTION_Y / 10;
	ButtonToAdd.Width = ButtonToAdd.Text.length() * 48;
	ButtonToAdd.Collision = UpdateCollision(ButtonToAdd.Pos, ButtonToAdd.Heigth, ButtonToAdd.Width);
	GameButtons.push_back(ButtonToAdd);
	// Scores Back
	ButtonToAdd.ID = BTN_SCORES_BACK;
	ButtonToAdd.Pos = { (double)TRUE_RESOLUTION_X / 2, (double)TRUE_RESOLUTION_Y - (double)TRUE_RESOLUTION_Y / 8 };
	ButtonToAdd.Text = "Back";
	ButtonToAdd.Heigth = TRUE_RESOLUTION_Y / 10;
	ButtonToAdd.Width = ButtonToAdd.Text.length() * 69;
	ButtonToAdd.Collision = UpdateCollision(ButtonToAdd.Pos, ButtonToAdd.Heigth, ButtonToAdd.Width);
	GameButtons.push_back(ButtonToAdd);
	// Options Back
	ButtonToAdd.ID = BTN_OPTIONS_BACK;
	ButtonToAdd.Pos = { (double)TRUE_RESOLUTION_X / 2, (double)TRUE_RESOLUTION_Y / 2 + (double)TRUE_RESOLUTION_Y / 16 + (double)TRUE_RESOLUTION_Y / 4 };
	ButtonToAdd.Text = "Back";
	ButtonToAdd.Heigth = TRUE_RESOLUTION_Y / 10;
	ButtonToAdd.Width = ButtonToAdd.Text.length() * 60;
	ButtonToAdd.Collision = UpdateCollision(ButtonToAdd.Pos, ButtonToAdd.Heigth, ButtonToAdd.Width);
	GameButtons.push_back(ButtonToAdd);
}

void OptionsMenu()
{
	Uint32 TicksToNextFrame = SDL_GetTicks();
	Uint32 TickCurrent = SDL_GetTicks();

	while (true)
	{
		// Чтобы игра слишком часто не обновлялась
		if (TickCurrent - SDL_GetTicks() < REPEAT_DELAY)
		{
			SDL_Delay(REPEAT_DELAY);
		}
		if (TickCurrent - TicksToNextFrame > (1.0 / FramesPerSecondTarget) * 1000)
		{
			TicksToNextFrame = TickCurrent;
			DrawOptionsFrame();
			SDL_RenderPresent(RendererPrimary);
			SDL_RenderClear(RendererPrimary);
		}
		TickCurrent = SDL_GetTicks();
		SDL_Event Event;
		if (SDL_PollEvent(&Event))
		{
			if (Event.type == SDL_WINDOWEVENT && Event.window.event == SDL_WINDOWEVENT_RESIZED) {
				int LowestRes = Event.window.data1 < Event.window.data2 ? Event.window.data1 : Event.window.data2;
				WINDOW_RESOLUTION_X = LowestRes;
				WINDOW_RESOLUTION_Y = LowestRes;
				SDL_SetWindowSize(WindowPrimary, WINDOW_RESOLUTION_X, WINDOW_RESOLUTION_Y);
			}
			if (Event.type == SDL_WINDOWEVENT && Event.window.event == SDL_WINDOWEVENT_MAXIMIZED) {
				SDL_SetWindowPosition(WindowPrimary, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
			}
			if (Event.type == SDL_QUIT)
			{
				QuitGame();
			}

			InputCode MouseCode = ReadMouseOptions(Event, GameButtons);
			InputCode KeyCode = ReadKeysOptions(Event);
			if (MouseCode == InputCode::OPTIONS_BACK || KeyCode == InputCode::OPTIONS_BACK)
			{
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
		// Чтобы игра слишком часто не обновлялась
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
				int LowestRes = Event.window.data1 < Event.window.data2 ? Event.window.data1 : Event.window.data2;
				WINDOW_RESOLUTION_X = LowestRes;
				WINDOW_RESOLUTION_Y = LowestRes;
				SDL_SetWindowSize(WindowPrimary, WINDOW_RESOLUTION_X, WINDOW_RESOLUTION_Y);
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
				OptionsMenu();
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
		// Чтобы игра слишком часто не обновлялась
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
				int LowestRes = Event.window.data1 < Event.window.data2 ? Event.window.data1 : Event.window.data2;
				WINDOW_RESOLUTION_X = LowestRes;
				WINDOW_RESOLUTION_Y = LowestRes;
				SDL_SetWindowSize(WindowPrimary, WINDOW_RESOLUTION_X, WINDOW_RESOLUTION_Y);
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
		// Чтобы игра слишком часто не обновлялась
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
				int LowestRes = Event.window.data1 < Event.window.data2 ? Event.window.data1 : Event.window.data2;
				WINDOW_RESOLUTION_X = LowestRes;
				WINDOW_RESOLUTION_Y = LowestRes;
				SDL_SetWindowSize(WindowPrimary, WINDOW_RESOLUTION_X, WINDOW_RESOLUTION_Y);
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
		// Чтобы игра слишком часто не обновлялась
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
				int LowestRes = Event.window.data1 < Event.window.data2 ? Event.window.data1 : Event.window.data2;
				WINDOW_RESOLUTION_X = LowestRes;
				WINDOW_RESOLUTION_Y = LowestRes;
				SDL_SetWindowSize(WindowPrimary, WINDOW_RESOLUTION_X, WINDOW_RESOLUTION_Y);
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
		// Чтобы игра слишком часто не обновлялась
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
				int LowestRes = Event.window.data1 < Event.window.data2 ? Event.window.data1 : Event.window.data2;
				WINDOW_RESOLUTION_X = LowestRes;
				WINDOW_RESOLUTION_Y = LowestRes;
				SDL_SetWindowSize(WindowPrimary, WINDOW_RESOLUTION_X, WINDOW_RESOLUTION_Y);
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
		// Чтобы игра слишком часто не обновлялась
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
				int LowestRes = Event.window.data1 < Event.window.data2 ? Event.window.data1 : Event.window.data2;
				WINDOW_RESOLUTION_X = LowestRes;
				WINDOW_RESOLUTION_Y = LowestRes;
				SDL_SetWindowSize(WindowPrimary, WINDOW_RESOLUTION_X, WINDOW_RESOLUTION_Y);
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