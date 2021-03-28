#include "main.h"

int TickShoot = SDL_GetTicks();

InputCode ReadKeysPause(const SDL_Event& Event)
{
	if (Event.type == SDL_KEYDOWN)
	{
		switch (Event.key.keysym.scancode)
		{
		case SDL_SCANCODE_ESCAPE:
			return InputCode::PAUSE_CONTINUE;
		default:
			return InputCode::NOTHING;
		}
	}
	return InputCode::NOTHING;
}

InputCode ReadMousePause(const SDL_Event& Event, const buttons& Buttons)
{
	SDL_GetMouseState(&MousePosWindow.x, &MousePosWindow.y);
	MousePosWindow.x *= (double)TRUE_RESOLUTION_X / WINDOW_RESOLUTION_X;
	MousePosWindow.y *= (double)TRUE_RESOLUTION_Y / WINDOW_RESOLUTION_Y;
	collisionbox MouseCollision = UpdateCollision({ (double)MousePosWindow.x , (double)MousePosWindow.y }, 1, 1);
	if (Event.type == SDL_MOUSEBUTTONDOWN)
	{
		//Кнопка Continue
		if (IsColliding(MouseCollision, Buttons[BTN_INGAME_CONTINUE].Collision))
		{
			return InputCode::PAUSE_CONTINUE;
		}
		//Кнопка Quit to Desktop 
		else if (IsColliding(MouseCollision, Buttons[BTN_INGAME_QUIT_DESKTOP].Collision))
		{
			return InputCode::PAUSE_TO_DESKTOP;
		}
		//Кнопка Restart
		else if (IsColliding(MouseCollision, Buttons[BTN_INGAME_RESTART].Collision))
		{
			return InputCode::PAUSE_RESTART;
		}
		//Кнопка Quit to Main Menu 
		else if (IsColliding(MouseCollision, Buttons[BTN_INGAME_QUIT_MAINMENU].Collision))
		{
			return InputCode::PAUSE_TO_MAIN_MENU;
		}
	}
	return InputCode::NOTHING;
}

InputCode ReadKeysDifficulty(const SDL_Event& Event)
{
	if (Event.type == SDL_KEYDOWN)
	{
		switch (Event.key.keysym.scancode)
		{
		case SDL_SCANCODE_ESCAPE:
			return InputCode::DIFFICULTY_BACK;
		default:
			return InputCode::NOTHING;
		}
	}
	return InputCode::NOTHING;
}

InputCode ReadMouseDifficuly(const SDL_Event& Event, const buttons& Buttons)
{
	SDL_GetMouseState(&MousePosWindow.x, &MousePosWindow.y);
	MousePosWindow.x *= (double)TRUE_RESOLUTION_X / WINDOW_RESOLUTION_X;
	MousePosWindow.y *= (double)TRUE_RESOLUTION_Y / WINDOW_RESOLUTION_Y;
	collisionbox MouseCollision = UpdateCollision({ (double)MousePosWindow.x , (double)MousePosWindow.y }, 1, 1);
	if (Event.type == SDL_MOUSEBUTTONDOWN)
	{
		//Кнопка Continue
		if (IsColliding(MouseCollision, Buttons[BTN_DIFFICULTY_BACK].Collision))
		{
			return InputCode::DIFFICULTY_BACK;
		}
		//Кнопка Quit to Desktop 
		else if (IsColliding(MouseCollision, Buttons[BTN_DIFFICULTY_EASY].Collision))
		{
			return InputCode::DIFFICULTY_EASY;
		}
		//Кнопка Restart
		else if (IsColliding(MouseCollision, Buttons[BTN_DIFFICULTY_NORMAL].Collision))
		{
			return InputCode::DIFFICULTY_NORMAL;
		}
		//Кнопка Quit to Main Menu 
		else if (IsColliding(MouseCollision, Buttons[BTN_DIFFICULTY_HARD].Collision))
		{
			return InputCode::DIFFICULTY_HARD;
		}
	}
	return InputCode::NOTHING;
}

InputCode ReadKeysMain(const SDL_Event& Event) // TODO
{
	if (Event.type == SDL_KEYDOWN)
	{
		switch (Event.key.keysym.scancode)
		{
		case SDL_SCANCODE_ESCAPE:
			return InputCode::MAIN_TO_DESKTOP;
		default:
			return InputCode::NOTHING;
		}
	}
	return InputCode::NOTHING;
}

InputCode ReadMouseMain(const SDL_Event& Event, const buttons& Buttons)
{
	SDL_GetMouseState(&MousePosWindow.x, &MousePosWindow.y);
	MousePosWindow.x *= (double)TRUE_RESOLUTION_X / WINDOW_RESOLUTION_X;
	MousePosWindow.y *= (double)TRUE_RESOLUTION_Y / WINDOW_RESOLUTION_Y;
	collisionbox MouseCollision = UpdateCollision({ (double)MousePosWindow.x , (double)MousePosWindow.y }, 1, 1);
	if (Event.type == SDL_MOUSEBUTTONDOWN)
	{
		//Кнопка Play Classic
		if (IsColliding(MouseCollision, GameButtons[BTN_MENU_CLASSIC].Collision))
		{
			return InputCode::MAIN_CLASSIC;
		}
		//Кнопка Arithmetic
		else if (IsColliding(MouseCollision, GameButtons[BTN_MENU_ARITHMETIC].Collision))
		{
			return InputCode::MAIN_ARITHMETIC;
		}
		//Кнопка Scores
		else if (IsColliding(MouseCollision, GameButtons[BTN_MENU_SCORES].Collision))
		{
			return InputCode::MAIN_SCORES;
		}
		//Кнопка Quit to Desktop
		else if (IsColliding(MouseCollision, GameButtons[BTN_MENU_QUIT_DESKTOP].Collision))
		{
			return InputCode::MAIN_TO_DESKTOP;
		}
	}
	return InputCode::NOTHING;
}

InputCode ReadKeysScores(const SDL_Event& Event)
{
	if (Event.type == SDL_KEYDOWN)
	{
		switch (Event.key.keysym.scancode)
		{
		case SDL_SCANCODE_ESCAPE:
			return InputCode::SCORES_BACK;
		default:
			return InputCode::NOTHING;
		}
	}
	return InputCode::NOTHING;
}

InputCode ReadMouseScores(const SDL_Event& Event, const buttons& Buttons)
{
	SDL_GetMouseState(&MousePosWindow.x, &MousePosWindow.y);
	MousePosWindow.x *= (double)TRUE_RESOLUTION_X / WINDOW_RESOLUTION_X;
	MousePosWindow.y *= (double)TRUE_RESOLUTION_Y / WINDOW_RESOLUTION_Y;
	collisionbox MouseCollision = UpdateCollision({ (double)MousePosWindow.x , (double)MousePosWindow.y }, 1, 1);
	if (Event.type == SDL_MOUSEBUTTONDOWN)
	{
		//Кнопка Back
		if (IsColliding(MouseCollision, GameButtons[BTN_SCORES_BACK].Collision))
		{
			return InputCode::SCORES_BACK;
		}
	}
	return InputCode::NOTHING;
}

InputCode ReadKeysScoreEnter(const SDL_Event& Event, std::string& WordInput)
{
	if (Event.type == SDL_KEYDOWN)
	{
		switch (Event.key.keysym.scancode)
		{
		case SDL_SCANCODE_ESCAPE:
			return InputCode::SCORESENTER_SKIP;
		case SDL_SCANCODE_BACKSPACE:
			if (WordInput.length() > 0)
			{
				// если символ больше байта, удаляем сразу два
				if (WordInput[WordInput.length() - 1] < 0)
				{
					WordInput = WordInput.substr(0, WordInput.length() - 2);
				}
				// если символ однобайтовый, удаляем один символ
				else
				{
					WordInput = WordInput.substr(0, WordInput.length() - 1);
				}
			}
			break;
		case SDL_SCANCODE_RETURN:
			if (WordInput == "")
			{
				return InputCode::SCORESENTER_SKIP;
			}
			else
			{
				return InputCode::SCORESENTER_ENTER;
			}
			break;
		default:
			return InputCode::NOTHING;
		}
	}
	// Ввод текста
	if (Event.type == SDL_TEXTINPUT)
	{
		WordInput += Event.text.text;
	}
	return InputCode::NOTHING;
}


void ReadKeys(SDL_Event& Event) {

	// Проверяем нажатые клавиши
	if (Event.type == SDL_KEYDOWN) {
		// ESC
		if (Event.key.keysym.scancode == SDL_SCANCODE_ESCAPE && !MainMenuShow && !ChoosingDifficultyShow && !PlayerDead && !HighscoresEnterShow && !HighscoresShow)
		{
			PauseMenu();
			//GamePaused = GamePaused == true ? false : true;
			//IngameMenuShow = IngameMenuShow == true ? false : true;
		}
		if (!GamePaused || HighscoresEnterShow)
		{
			if (Event.key.keysym.scancode == SDL_SCANCODE_BACKSPACE && WordInput.length() > 0)
			{
				// если символ больше байта, удаляем сразу два
				if (WordInput[WordInput.length() - 1] < 0)
				{
					WordInput = WordInput.substr(0, WordInput.length() - 2);
				}
				// если символ однобайтовый, удаляем один символ
				else
				{
					WordInput = WordInput.substr(0, WordInput.length() - 1);
				}
			}
			if (Event.key.keysym.scancode == SDL_SCANCODE_RETURN && !HighscoresEnterShow)
			{
				for (int i = 0; i < GameEnemies.size(); i++)
				{
					if ((!ArithmeticMode && WordInput == GameEnemies[i].Word) || (ArithmeticMode && WordInput == GameEnemies[i].ArithmeticAnswer))
					{
						// Создаём сердечки
						EntityCosmeticParticle CosmeticHeartToAdd;
						CosmeticHeartToAdd.Type = PRTCL_HEART;
						CosmeticHeartToAdd.Size = 32;
						CosmeticHeartToAdd.Pos.x = GameEnemies[i].Pos.x - GameEnemies[i].Width / 6;
						CosmeticHeartToAdd.Pos.y = GameEnemies[i].Pos.y - GameEnemies[i].Height / 6;
						GameCosmetics.push_back(CosmeticHeartToAdd);
						CosmeticHeartToAdd.Pos.x = GameEnemies[i].Pos.x + GameEnemies[i].Width / 6;
						CosmeticHeartToAdd.Pos.y = GameEnemies[i].Pos.y - GameEnemies[i].Height / 8;
						GameCosmetics.push_back(CosmeticHeartToAdd);
						CosmeticHeartToAdd.Pos.x = GameEnemies[i].Pos.x;
						CosmeticHeartToAdd.Pos.y = GameEnemies[i].Pos.y + GameEnemies[i].Height / 6;
						GameCosmetics.push_back(CosmeticHeartToAdd);
						// Добавляем очки
						double ScoreModifier = 1;
						if (Difficulty == DIFFICULTY_EASY)
						{
							ScoreModifier = 0.5;
						}
						else if (Difficulty == DIFFICULTY_NORMAL)
						{
							ScoreModifier = 1;
						}
						else if (Difficulty == DIFFICULTY_HARD)
						{
							ScoreModifier = 1.5;
						}
						if (ArithmeticMode && (GameEnemies[i].Word.find("*") != std::string::npos || GameEnemies[i].Word.find("/") != std::string::npos))
						{
							ScoreModifier += 1;
						}
						if (ArithmeticMode)
						{
							MainPlayer.Score += 50 * GameEnemies[i].ArithmeticAnswer.length() * ScoreModifier;
						}
						else
						{
							MainPlayer.Score += 25 * GameEnemies[i].Word.length() * ScoreModifier;
						}

						// Удаляем противника
						GameEnemies.erase(GameEnemies.begin() + i);

						i--;
					}
				}
				for (int i = 0; i < GameBonuses.size(); i++)
				{
					if (((!ArithmeticMode && WordInput == GameBonuses[i].Word) || (ArithmeticMode && WordInput == GameBonuses[i].ArithmeticAnswer)) && GameBonuses[i].Size == GameBonuses[i].FullSize)
					{
						if (GameBonuses[i].ID == BNS_RANDOM)
						{
							GameBonuses[i].ID = rand() % BNS_LAST;
						}
						if (GameBonuses[i].ID == BNS_HEART)
						{
							AddHearts(1);
						}
						else if (GameBonuses[i].ID == BNS_X2)
						{
							MainPlayer.Score *= 2;
						}
						else if (GameBonuses[i].ID == BNS_SLOWDOWN)
						{
							SlowdownTimerMod = 100;
						}
						// Создаём звездочки
						EntityCosmeticParticle CosmeticHeartToAdd;
						CosmeticHeartToAdd.Type = PRTCL_STAR;
						CosmeticHeartToAdd.Size = 32;
						CosmeticHeartToAdd.Pos.x = GameBonuses[i].Pos.x - GameBonuses[i].Size / 6;
						CosmeticHeartToAdd.Pos.y = GameBonuses[i].Pos.y - GameBonuses[i].Size / 6;
						GameCosmetics.push_back(CosmeticHeartToAdd);
						CosmeticHeartToAdd.Pos.x = GameBonuses[i].Pos.x + GameBonuses[i].Size / 6;
						CosmeticHeartToAdd.Pos.y = GameBonuses[i].Pos.y - GameBonuses[i].Size / 8;
						GameCosmetics.push_back(CosmeticHeartToAdd);
						CosmeticHeartToAdd.Pos.x = GameBonuses[i].Pos.x;
						CosmeticHeartToAdd.Pos.y = GameBonuses[i].Pos.y + GameBonuses[i].Size / 6;
						GameCosmetics.push_back(CosmeticHeartToAdd);
						// Удаляем бонус
						GameBonuses.erase(GameBonuses.begin() + i);
						i--;
					}
				}
				WordInput = "";
			}
			else if (Event.key.keysym.scancode == SDL_SCANCODE_RETURN && HighscoresEnterShow)
			{
				if (WordInput == "")
				{
					MainMenuShow = true;
					HighscoresEnterShow = false;
					GamePaused = true;
				}
				else
				{
					MainMenuShow = true;
					HighscoresEnterShow = false;
					GamePaused = true;
					for (int i = 0, BreakCycle = 0; i < GameHighscoresSize; i++)
					{
						if (MainPlayer.Score > GameHighscores[i].Score)
						{
							BreakCycle = 1;
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
							GameHighscores[i].Difficulty = Difficulty;
							GameHighscores[i].Mode = ArithmeticMode;
						}
						if (BreakCycle == 1)
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
				}
			}
#ifdef DEBUG_MODE
			if (Event.key.keysym.scancode == SDL_SCANCODE_RCTRL)
			{
				AddHearts(1);
			}
#endif
		}
	}
	if (!GamePaused || HighscoresEnterShow)
	{
		// Ввод текста
		if (Event.type == SDL_TEXTINPUT)
		{
			WordInput += Event.text.text;
		}

		// Проверяем отжатые клавиши
		if (Event.type == SDL_KEYUP) {

		}
	}
}
void ReadMouse(SDL_Event& Event) {
	SDL_GetMouseState(&MousePosWindow.x, &MousePosWindow.y);
	MousePosWindow.x *= (double)TRUE_RESOLUTION_X / WINDOW_RESOLUTION_X;
	MousePosWindow.y *= (double)TRUE_RESOLUTION_Y / WINDOW_RESOLUTION_Y;
	collisionbox MouseCollision = UpdateCollision({ (double)MousePosWindow.x , (double)MousePosWindow.y }, 1, 1);
	if (Event.type == SDL_MOUSEBUTTONDOWN)
	{
		if (Event.button.button == SDL_BUTTON_LEFT)
		{
			if (IngameMenuShow)
			{
				//Кнопка Continue
				if (IsColliding(MouseCollision, GameButtons[BTN_INGAME_CONTINUE].Collision))
				{
					IngameMenuShow = false;
					GamePaused = false;
				}
				//Кнопка Quit to Desktop 
				else if (IsColliding(MouseCollision, GameButtons[BTN_INGAME_QUIT_DESKTOP].Collision))
				{
					QuitGame();
				}
				//Кнопка Restart
				else if (IsColliding(MouseCollision, GameButtons[BTN_INGAME_RESTART].Collision))
				{
					Restart = true;
					IngameMenuShow = false;
					GamePaused = false;
				}
				//Кнопка Quit to Main Menu 
				else if (IsColliding(MouseCollision, GameButtons[BTN_INGAME_QUIT_MAINMENU].Collision))
				{
					IngameMenuShow = false;
					// Проверка на рекорд
					for (int i = 0; i < GameHighscoresSize; i++)
					{
						if (GameHighscores[i].Score != 0 && MainPlayer.Score > GameHighscores[i].Score && MainPlayer.Score != 0)
						{
							HighscoresEnterShow = true;
						}
					}
					if (!HighscoresEnterShow)
					{
						MainMenuShow = true;
					}
				}
			}
			else if (MainMenuShow)
			{
				//Кнопка Play Classic
				if (IsColliding(MouseCollision, GameButtons[BTN_MENU_CLASSIC].Collision))
				{
					ArithmeticMode = false;
					MainMenuShow = false;
					ChoosingDifficultyShow = true;
				}
				//Кнопка Arithmetic
				else if (IsColliding(MouseCollision, GameButtons[BTN_MENU_ARITHMETIC].Collision))
				{
					ArithmeticMode = true;
					MainMenuShow = false;
					ChoosingDifficultyShow = true;
				}
				//Кнопка Scores
				else if (IsColliding(MouseCollision, GameButtons[BTN_MENU_SCORES].Collision))
				{
					MainMenuShow = false;
					HighscoresShow = true;
				}
				//Кнопка Quit to Desktop
				else if (IsColliding(MouseCollision, GameButtons[BTN_MENU_QUIT_DESKTOP].Collision))
				{
					QuitGame();
				}
			}
			else if (PlayerDead)
			{
				// Рестарт
				if (IsColliding(MouseCollision, GameButtons[BTN_DEAD_RETRY].Collision))
				{
					Restart = true;
				}
				// Кнопка в меню
				else if (IsColliding(MouseCollision, GameButtons[BTN_DEAD_QUIT_MAINMENU].Collision))
				{
					PlayerDead = false;
					// Проверка на рекорд
					for (int i = 0; i < GameHighscoresSize; i++)
					{
						if (GameHighscores[i].Score != 0 && MainPlayer.Score > GameHighscores[i].Score && MainPlayer.Score != 0)
						{
							HighscoresEnterShow = true;
						}
					}
					if (!HighscoresEnterShow)
					{
						MainMenuShow = true;
					}

				}
			}
			else if (HighscoresShow)
			{
				// Back
				if (IsColliding(MouseCollision, GameButtons[BTN_SCORES_BACK].Collision))
				{
					MainMenuShow = true;
					HighscoresShow = false;
				}

			}

		}
	}
#ifdef DEBUG_MODE
	if (!GamePaused)
	{
		if (Event.type == SDL_MOUSEBUTTONUP)
		{
			if (Event.button.button == SDL_BUTTON_LEFT)
			{
				SpawnEnemy();
			}
			if (Event.button.button == SDL_BUTTON_RIGHT)
			{
				SpawnBonus();
			}
		}
	}
#endif
}