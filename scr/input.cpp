﻿#include "main.h"

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

InputCode ReadKeysDead(const SDL_Event& Event)
{
	if (Event.type == SDL_KEYDOWN)
	{
		switch (Event.key.keysym.scancode)
		{
		case SDL_SCANCODE_ESCAPE:
			return InputCode::DEAD_TO_MAIN_MENU;
		default:
			return InputCode::NOTHING;
		}
	}
	return InputCode::NOTHING;
}

InputCode ReadMouseDead(const SDL_Event& Event, const buttons& Buttons)
{
	SDL_GetMouseState(&MousePosWindow.x, &MousePosWindow.y);
	MousePosWindow.x *= (double)TRUE_RESOLUTION_X / WINDOW_RESOLUTION_X;
	MousePosWindow.y *= (double)TRUE_RESOLUTION_Y / WINDOW_RESOLUTION_Y;
	collisionbox MouseCollision = UpdateCollision({ (double)MousePosWindow.x , (double)MousePosWindow.y }, 1, 1);
	if (Event.type == SDL_MOUSEBUTTONDOWN)
	{
		//Кнопка Retry
		if (IsColliding(MouseCollision, GameButtons[BTN_DEAD_RETRY].Collision))
		{
			return InputCode::DEAD_RETRY;
		}
		// Кнопка Return to Main Menu
		else if (IsColliding(MouseCollision, GameButtons[BTN_DEAD_QUIT_MAINMENU].Collision))
		{
			return InputCode::DEAD_TO_MAIN_MENU;
		}
	}
	return InputCode::NOTHING;
}

InputCode ReadGameSessionKeys(SDL_Event& Event, std::string& WordInput) {

	// Проверяем нажатые клавиши
	if (Event.type == SDL_KEYDOWN) {
		// ESC
		if (Event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
		{
			return InputCode::GAMESESSION_PAUSE;
		}
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
		if (Event.key.keysym.scancode == SDL_SCANCODE_RETURN)
		{
			return InputCode::GAMESESSION_ENTER;
		}
	}
#ifdef DEBUG_MODE
	if (Event.key.keysym.scancode == SDL_SCANCODE_RCTRL)
	{
		AddHearts(1);
	}
#endif
	// Ввод текста
	if (Event.type == SDL_TEXTINPUT)
	{
		WordInput += Event.text.text;
		SlowdownTimerMod = 100;
	}
	return InputCode::NOTHING;
}

void ReadMouse(SDL_Event& Event) {
	SDL_GetMouseState(&MousePosWindow.x, &MousePosWindow.y);
	MousePosWindow.x *= (double)TRUE_RESOLUTION_X / WINDOW_RESOLUTION_X;
	MousePosWindow.y *= (double)TRUE_RESOLUTION_Y / WINDOW_RESOLUTION_Y;
	collisionbox MouseCollision = UpdateCollision({ (double)MousePosWindow.x , (double)MousePosWindow.y }, 1, 1);
#ifdef DEBUG_MODE
	if (Event.type == SDL_MOUSEBUTTONDOWN)
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
#endif
}