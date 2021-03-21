#include "main.h"

int TickShoot = SDL_GetTicks();
void ReadKeys(SDL_Event Event) {

	// ��������� ������� �������
	if (Event.type == SDL_KEYDOWN) {
		// ESC
		if (Event.key.keysym.scancode == SDL_SCANCODE_ESCAPE && !MainMenuShow && !ChoosingDifficultyShow && !PlayerDead && !HighscoresEnterShow && !HighscoresShow)
		{
			GamePaused = GamePaused == true ? false : true;
			IngameMenuShow = IngameMenuShow == true ? false : true;
		}
		if (!GamePaused || HighscoresEnterShow)
		{
			if (Event.key.keysym.scancode == SDL_SCANCODE_BACKSPACE && WordInput.length() > 0)
			{
				// ���� ������ ������ �����, ������� ����� ���
				if (WordInput[WordInput.length() - 1] < 0)
				{
					WordInput = WordInput.substr(0, WordInput.length() - 2);
				}
				// ���� ������ ������������, ������� ���� ������
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
						// ������ ��������
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
						// ��������� ����
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
						
						// ������� ����������
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
						// ������ ���������
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
						// ������� �����
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
		// ���� ������
		if (Event.type == SDL_TEXTINPUT)
		{
			WordInput += Event.text.text;
		}

		// ��������� ������� �������
		if (Event.type == SDL_KEYUP) {

		}
	}
}
void ReadMouse(SDL_Event Event) {
	double ResolutionRatio = (double)TRUE_RESOLUTION_X / WINDOW_RESOLUTION_X > (double)TRUE_RESOLUTION_Y / WINDOW_RESOLUTION_Y ? (double)TRUE_RESOLUTION_X / WINDOW_RESOLUTION_X : (double)TRUE_RESOLUTION_Y / WINDOW_RESOLUTION_Y;
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
				//������ Continue
				if (IsColliding(MouseCollision, Buttons[BTN_INGAME_CONTINUE].Collision))
				{
					IngameMenuShow = false;
					GamePaused = false;
				}
				//������ Quit to Desktop 
				else if (IsColliding(MouseCollision, Buttons[BTN_INGAME_QUIT_DESKTOP].Collision))
				{
					QuitGame();				
				}
				//������ Restart
				else if (IsColliding(MouseCollision, Buttons[BTN_INGAME_RESTART].Collision))
				{
					Restart = true;
					IngameMenuShow = false;
					GamePaused = false;
				}
				//������ Quit to Main Menu 
				else if (IsColliding(MouseCollision, Buttons[BTN_INGAME_QUIT_MAINMENU].Collision))
				{					
					IngameMenuShow = false;
					// �������� �� ������
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
				//������ Play Classic
				if (IsColliding(MouseCollision, Buttons[BTN_MENU_CLASSIC].Collision))
				{
					ArithmeticMode = false;
					MainMenuShow = false;
					ChoosingDifficultyShow = true;
				}
				//������ Arithmetic
				else if (IsColliding(MouseCollision, Buttons[BTN_MENU_ARITHMETIC].Collision))
				{
					ArithmeticMode = true;
					MainMenuShow = false;
					ChoosingDifficultyShow = true;
				}
				//������ Scores
				else if (IsColliding(MouseCollision, Buttons[BTN_MENU_SCORES].Collision))
				{					
					MainMenuShow = false;
					HighscoresShow = true;
				}
				//������ Quit to Desktop
				else if (IsColliding(MouseCollision, Buttons[BTN_MENU_QUIT_DESKTOP].Collision))
				{
					QuitGame();
				}
			}
			else if (ChoosingDifficultyShow)
			{
				//������ Easy
				if (IsColliding(MouseCollision, Buttons[BTN_DIFFICULTY_EASY].Collision))
				{
					Difficulty = DIFFICULTY_EASY;
					ChoosingDifficultyShow = false;
					GamePaused = false;
					Restart = true;
				}
				//������ Normal
				else if (IsColliding(MouseCollision, Buttons[BTN_DIFFICULTY_NORMAL].Collision))
				{
					Difficulty = DIFFICULTY_NORMAL;
					ChoosingDifficultyShow = false;
					GamePaused = false;
					Restart = true;
				}
				//������ Hard
				else if (IsColliding(MouseCollision, Buttons[BTN_DIFFICULTY_HARD].Collision))
				{
					Difficulty = DIFFICULTY_HARD;
					ChoosingDifficultyShow = false;
					GamePaused = false;
					Restart = true;
				}
				//������ Back
				else if (IsColliding(MouseCollision, Buttons[BTN_DIFFICULTY_BACK].Collision))
				{
					ChoosingDifficultyShow = false;
					MainMenuShow = true;
				}
			}
			else if (PlayerDead)
			{
				// �������
				if (IsColliding(MouseCollision, Buttons[BTN_DEAD_RETRY].Collision))
				{
					Restart = true;
				}
				// ������ � ����
				else if (IsColliding(MouseCollision, Buttons[BTN_DEAD_QUIT_MAINMENU].Collision))
				{
					// �������� �� ������
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
				if (IsColliding(MouseCollision, Buttons[BTN_SCORES_BACK].Collision))
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