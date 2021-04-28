#include "main.h"

std::vector<EntityEnemy> GameEnemies;
std::vector<point> GamePlayerHearts;
std::vector<EntityCosmeticParticle> GameCosmetics;
std::vector<EntityBonus> GameBonuses;
double HeartRotateStep = 0;
double EnemyRotateStep = 0;
bool PlayerNoDefense = false;

void AddHearts(int Count) {
	if (Count > 0)
	{
		PlayerNoDefense = false;
	}
	for (int i = 0; i < Count; i++)
	{
		GamePlayerHearts.push_back({ 0,0 });
	}
	double RotateAngle = 360 / GamePlayerHearts.size();
	point HeartPos = MainPlayer.Pos;
	point Rotate = { MainPlayer.Width,0 };

	for (int i = 0; i < GamePlayerHearts.size(); i++)
	{
		Rotate = RotateVector(Rotate, RotateAngle);
		GamePlayerHearts[i] = SumVectors(HeartPos, Rotate);
	}
}
void RemoveHearts(int Count) {
	if (GamePlayerHearts.size() == 0)
	{
		if (PlayerNoDefense)
		{
			PlayerDead = true;
		}
		PlayerNoDefense = true;
		return;
	}
	for (int i = 0; i < Count; i++)
	{
		GamePlayerHearts.pop_back();
	}
	if (GamePlayerHearts.size() == 0)
	{
		PlayerNoDefense = true;
		return;
	}
	double RotateAngle = 360 / GamePlayerHearts.size();
	point HeartPos = MainPlayer.Pos;
	point Rotate = { MainPlayer.Width,0 };
	for (int i = 0; i < GamePlayerHearts.size(); i++)
	{
		Rotate = RotateVector(Rotate, RotateAngle);
		GamePlayerHearts[i] = SumVectors(HeartPos, Rotate);
	}
}
void SpawnEnemy(DifficultyCode Difficulty, bool ArithmeticMode) {
	if (rand() % 6 > -1)
	{
		EntityEnemy EnemyToAdd;
		int  EnemyPosOffet = 100;
		if (rand() % 2)
		{
			if (rand() % 2)
			{
				EnemyToAdd.Pos.x = -EnemyPosOffet;
				EnemyToAdd.Pos.y = rand() % (ArenaHeight + EnemyPosOffet * 2) - EnemyPosOffet;
			}
			else
			{
				EnemyToAdd.Pos.x = ArenaWidth + EnemyPosOffet;
				EnemyToAdd.Pos.y = rand() % (ArenaHeight + EnemyPosOffet * 2) - EnemyPosOffet;
			}
		}
		else
		{
			if (rand() % 2)
			{
				EnemyToAdd.Pos.x = rand() % (ArenaHeight + EnemyPosOffet * 2) - EnemyPosOffet;
				EnemyToAdd.Pos.y = -EnemyPosOffet;
			}
			else
			{
				EnemyToAdd.Pos.x = rand() % (ArenaWidth + EnemyPosOffet * 2) - EnemyPosOffet;
				EnemyToAdd.Pos.y = ArenaHeight + EnemyPosOffet;
			}
		}
		EnemyToAdd.TextureIndex = GIMG_SPRITES_ENEMY;
		EnemyToAdd.Rotation = 0;
		EnemyToAdd.Height = 96;
		EnemyToAdd.Width = 96;
		EnemyToAdd.Collision.BottomRight.x = EnemyToAdd.Pos.x + EnemyToAdd.Width / 2;
		EnemyToAdd.Collision.BottomRight.y = EnemyToAdd.Pos.y + EnemyToAdd.Height / 2;
		EnemyToAdd.Collision.TopLeft.x = EnemyToAdd.Pos.x - EnemyToAdd.Width / 2;
		EnemyToAdd.Collision.TopLeft.y = EnemyToAdd.Pos.y - EnemyToAdd.Height / 2;
		if (ArithmeticMode)
		{
			char StrBuffer[10];
			int ArithmeticResult;
			int ArithmeticOperation = rand() % 4;
			double ArithmeticMovementMod = 1;
			if (Difficulty == DifficultyCode::EASY)
			{
				// Генерация первого числа
				_itoa_s(rand() % 16, StrBuffer, 10, 10);
				EnemyToAdd.Word += StrBuffer;
				ArithmeticResult = atoi(StrBuffer);
				// Сложение
				if (ArithmeticOperation == 0)
				{
					_itoa_s(rand() % 16, StrBuffer, 10, 10);
					EnemyToAdd.Word += '+';
					EnemyToAdd.Word += StrBuffer;
					ArithmeticResult += atoi(StrBuffer);
				}
				// Вычитание
				else if (ArithmeticOperation == 1)
				{
					_itoa_s(rand() % 16, StrBuffer, 10, 10);
					EnemyToAdd.Word += '-';
					EnemyToAdd.Word += StrBuffer;
					ArithmeticResult -= atoi(StrBuffer);
				}
				// Умножение
				else if (ArithmeticOperation == 2)
				{
					ArithmeticMovementMod = 0.6;
					_itoa_s(rand() % 10, StrBuffer, 10, 10);
					EnemyToAdd.Word += '*';
					EnemyToAdd.Word += StrBuffer;
					ArithmeticResult *= atoi(StrBuffer);
				}
				// Деление
				else if (ArithmeticOperation == 3)
				{
					ArithmeticMovementMod = 0.5;
					int Divider = 1;
					for (int i = 2; i <= 9; i++)
					{
						if (ArithmeticResult % i == 0)
						{
							Divider = i;
							break;
						}
					}
					_itoa_s(Divider, StrBuffer, 10, 10);
					EnemyToAdd.Word += '/';
					EnemyToAdd.Word += StrBuffer;
					ArithmeticResult /= Divider;
				}
			}
			else if (Difficulty == DifficultyCode::NORMAL)
			{
				// Генерация первого числа
				_itoa_s(rand() % 100, StrBuffer, 10, 10);
				EnemyToAdd.Word += StrBuffer;
				ArithmeticResult = atoi(StrBuffer);
				// Сложение
				if (ArithmeticOperation == 0)
				{
					_itoa_s(rand() % 100, StrBuffer, 10, 10);
					EnemyToAdd.Word += '+';
					EnemyToAdd.Word += StrBuffer;
					ArithmeticResult += atoi(StrBuffer);
				}
				// Вычитание
				else if (ArithmeticOperation == 1)
				{
					_itoa_s(rand() % 100, StrBuffer, 10, 10);
					EnemyToAdd.Word += '-';
					EnemyToAdd.Word += StrBuffer;
					ArithmeticResult -= atoi(StrBuffer);
				}
				// Умножение
				else if (ArithmeticOperation == 2)
				{
					ArithmeticMovementMod = 0.6;
					_itoa_s(rand() % 21, StrBuffer, 10, 10);
					EnemyToAdd.Word += '*';
					EnemyToAdd.Word += StrBuffer;
					ArithmeticResult *= atoi(StrBuffer);
				}
				// Деление
				else if (ArithmeticOperation == 3)
				{
					ArithmeticMovementMod = 0.5;
					int Divider = 1;
					for (int i = 2; i <= 99; i++)
					{
						if (ArithmeticResult % i == 0)
						{
							Divider = i;
							break;
						}
					}
					_itoa_s(Divider, StrBuffer, 10, 10);
					EnemyToAdd.Word += '/';
					EnemyToAdd.Word += StrBuffer;
					ArithmeticResult /= Divider;
				}
			}
			else if (Difficulty == DifficultyCode::HARD)
			{
				// Генерация первого числа
				_itoa_s(rand() % 1000, StrBuffer, 10, 10);
				EnemyToAdd.Word += StrBuffer;
				ArithmeticResult = atoi(StrBuffer);
				// Сложение
				if (ArithmeticOperation == 0)
				{
					_itoa_s(rand() % 1000, StrBuffer, 10, 10);
					EnemyToAdd.Word += '+';
					EnemyToAdd.Word += StrBuffer;
					ArithmeticResult += atoi(StrBuffer);
				}
				// Вычитание
				else if (ArithmeticOperation == 1)
				{
					_itoa_s(rand() % 1000, StrBuffer, 10, 10);
					EnemyToAdd.Word += '-';
					EnemyToAdd.Word += StrBuffer;
					ArithmeticResult -= atoi(StrBuffer);
				}
				// Умножение
				else if (ArithmeticOperation == 2)
				{
					ArithmeticMovementMod = 0.6;
					_itoa_s(rand() % 99, StrBuffer, 10, 10);
					EnemyToAdd.Word += '*';
					EnemyToAdd.Word += StrBuffer;
					ArithmeticResult *= atoi(StrBuffer);
				}
				// Деление
				else if (ArithmeticOperation == 3)
				{
					ArithmeticMovementMod = 0.5;
					int Divider = 1;
					for (int i = 2; i <= 99; i++)
					{
						if (ArithmeticResult % i == 0)
						{
							Divider = i;
							break;
						}
					}
					_itoa_s(Divider, StrBuffer, 10, 10);
					EnemyToAdd.Word += '/';
					EnemyToAdd.Word += StrBuffer;
					ArithmeticResult /= Divider;
				}
			}
			_itoa_s(ArithmeticResult, StrBuffer, 10, 10);
			EnemyToAdd.ArithmeticAnswer = StrBuffer;
			EnemyToAdd.Speed = 0.1 * DifficultySpeedModifier * ArithmeticMovementMod;
		}
		else
		{
			if (Difficulty == DifficultyCode::EASY)
			{
				EnemyToAdd.Word = WordsList[rand() % (WordsList.size() / 2)];
			}
			else if (Difficulty == DifficultyCode::NORMAL)
			{
				EnemyToAdd.Word = WordsList[rand() % WordsList.size()];
			}
			else if (Difficulty == DifficultyCode::HARD)
			{
				EnemyToAdd.Word = WordsList[rand() % (WordsList.size() - WordsList.size() / 2) + WordsList.size() / 2];
			}
			EnemyToAdd.Speed = 0.14 * sqrt((double)3 / EnemyToAdd.Word.length()) * DifficultySpeedModifier;
		}

		GameEnemies.push_back(EnemyToAdd);
	}
}
void SpawnBonus(DifficultyCode Difficulty, bool ArithmeticMode) {
	EntityBonus BonusToAdd;
	int BonusPosOffet = 100;
	while (true)
	{
		BonusToAdd.Pos.x = rand() % (ArenaWidth - BonusPosOffet * 2) + BonusPosOffet;
		BonusToAdd.Pos.y = rand() % (ArenaHeight - BonusPosOffet * 2) + BonusPosOffet;
		if (abs(BonusToAdd.Pos.x - ArenaWidth / 2) > MainPlayer.Width * 2 || abs(BonusToAdd.Pos.y - ArenaHeight / 2) > MainPlayer.Height * 2)
		{
			break;
		}
	}
	BonusToAdd.Rotation = 90;
	BonusToAdd.ID = rand() % BNS_LAST;
	BonusToAdd.TextureIndex = GIMG_SPRITES_BONUS_RANDOM + BonusToAdd.ID;
	BonusToAdd.FullSize = 96;
	BonusToAdd.Size = 1;
	if (ArithmeticMode)
	{
		char StrBuffer[10];
		int ArithmeticResult;
		int ArithmeticOperation = rand() % 4;
		double ArithmeticMovementMod = 1;
		if (Difficulty == DifficultyCode::EASY)
		{
			// Генерация первого числа
			_itoa_s(rand() % 16, StrBuffer, 10, 10);
			BonusToAdd.Word += StrBuffer;
			ArithmeticResult = atoi(StrBuffer);
			// Сложение
			if (ArithmeticOperation == 0)
			{
				_itoa_s(rand() % 16, StrBuffer, 10, 10);
				BonusToAdd.Word += '+';
				BonusToAdd.Word += StrBuffer;
				ArithmeticResult += atoi(StrBuffer);
			}
			// Вычитание
			else if (ArithmeticOperation == 1)
			{
				_itoa_s(rand() % 16, StrBuffer, 10, 10);
				BonusToAdd.Word += '-';
				BonusToAdd.Word += StrBuffer;
				ArithmeticResult -= atoi(StrBuffer);
			}
			// Умножение
			else if (ArithmeticOperation == 2)
			{
				ArithmeticMovementMod = 0.6;
				_itoa_s(rand() % 10, StrBuffer, 10, 10);
				BonusToAdd.Word += '*';
				BonusToAdd.Word += StrBuffer;
				ArithmeticResult *= atoi(StrBuffer);
			}
			// Деление
			else if (ArithmeticOperation == 3)
			{
				ArithmeticMovementMod = 0.5;
				int Divider = 1;
				for (int i = 2; i <= 9; i++)
				{
					if (ArithmeticResult % i == 0)
					{
						Divider = i;
						break;
					}
				}
				_itoa_s(Divider, StrBuffer, 10, 10);
				BonusToAdd.Word += '/';
				BonusToAdd.Word += StrBuffer;
				ArithmeticResult /= Divider;
			}
		}
		else if (Difficulty == DifficultyCode::NORMAL)
		{
			// Генерация первого числа
			_itoa_s(rand() % 100, StrBuffer, 10, 10);
			BonusToAdd.Word += StrBuffer;
			ArithmeticResult = atoi(StrBuffer);
			// Сложение
			if (ArithmeticOperation == 0)
			{
				_itoa_s(rand() % 100, StrBuffer, 10, 10);
				BonusToAdd.Word += '+';
				BonusToAdd.Word += StrBuffer;
				ArithmeticResult += atoi(StrBuffer);
			}
			// Вычитание
			else if (ArithmeticOperation == 1)
			{
				_itoa_s(rand() % 100, StrBuffer, 10, 10);
				BonusToAdd.Word += '-';
				BonusToAdd.Word += StrBuffer;
				ArithmeticResult -= atoi(StrBuffer);
			}
			// Умножение
			else if (ArithmeticOperation == 2)
			{
				ArithmeticMovementMod = 0.6;
				_itoa_s(rand() % 21, StrBuffer, 10, 10);
				BonusToAdd.Word += '*';
				BonusToAdd.Word += StrBuffer;
				ArithmeticResult *= atoi(StrBuffer);
			}
			// Деление
			else if (ArithmeticOperation == 3)
			{
				ArithmeticMovementMod = 0.5;
				int Divider = 1;
				for (int i = 2; i <= 99; i++)
				{
					if (ArithmeticResult % i == 0)
					{
						Divider = i;
						break;
					}
				}
				_itoa_s(Divider, StrBuffer, 10, 10);
				BonusToAdd.Word += '/';
				BonusToAdd.Word += StrBuffer;
				ArithmeticResult /= Divider;
			}
		}
		else if (Difficulty == DifficultyCode::EASY)
		{
			// Генерация первого числа
			_itoa_s(rand() % 1000, StrBuffer, 10, 10);
			BonusToAdd.Word += StrBuffer;
			ArithmeticResult = atoi(StrBuffer);
			// Сложение
			if (ArithmeticOperation == 0)
			{
				_itoa_s(rand() % 1000, StrBuffer, 10, 10);
				BonusToAdd.Word += '+';
				BonusToAdd.Word += StrBuffer;
				ArithmeticResult += atoi(StrBuffer);
			}
			// Вычитание
			else if (ArithmeticOperation == 1)
			{
				_itoa_s(rand() % 1000, StrBuffer, 10, 10);
				BonusToAdd.Word += '-';
				BonusToAdd.Word += StrBuffer;
				ArithmeticResult -= atoi(StrBuffer);
			}
			// Умножение
			else if (ArithmeticOperation == 2)
			{
				ArithmeticMovementMod = 0.6;
				_itoa_s(rand() % 99, StrBuffer, 10, 10);
				BonusToAdd.Word += '*';
				BonusToAdd.Word += StrBuffer;
				ArithmeticResult *= atoi(StrBuffer);
			}
			// Деление
			else if (ArithmeticOperation == 3)
			{
				ArithmeticMovementMod = 0.5;
				int Divider = 1;
				for (int i = 2; i <= 99; i++)
				{
					if (ArithmeticResult % i == 0)
					{
						Divider = i;
						break;
					}
				}
				_itoa_s(Divider, StrBuffer, 10, 10);
				BonusToAdd.Word += '/';
				BonusToAdd.Word += StrBuffer;
				ArithmeticResult /= Divider;
			}
		}
		_itoa_s(ArithmeticResult, StrBuffer, 10, 10);
		BonusToAdd.ArithmeticAnswer = StrBuffer;
	}
	else
	{
		if (Difficulty == DifficultyCode::EASY)
		{
			BonusToAdd.Word = WordsList[rand() % (WordsList.size() / 2)];
		}
		else if (Difficulty == DifficultyCode::NORMAL)
		{
			BonusToAdd.Word = WordsList[rand() % WordsList.size()];
		}
		else if (Difficulty == DifficultyCode::HARD)
		{
			BonusToAdd.Word = WordsList[rand() % (WordsList.size() - WordsList.size() / 2) + WordsList.size() / 2];
		}
	}
	BonusToAdd.Lifetime = 200;
	GameBonuses.push_back(BonusToAdd);
}
void UpdateHearts(double RotateStep) {
	if (GamePlayerHearts.size() > 0)
	{
		double RotateAngle = 360 / GamePlayerHearts.size();
		point HeartPos = MainPlayer.Pos;
		point Rotate = { MainPlayer.Width,0 };

		for (int i = 0; i < GamePlayerHearts.size(); i++)
		{
			if (i == 0)
			{
				Rotate = RotateVector(Rotate, RotateAngle + RotateStep);
			}
			Rotate = RotateVector(Rotate, RotateAngle);
			GamePlayerHearts[i] = SumVectors(HeartPos, Rotate);
		}
	}
}
void UpdateEntities() {
	// Враги
	for (int i = 0; i < GameEnemies.size(); i++)
	{
		// Изменение скорости в соответствии с замедлением
		point MovDir;
		MovDir.x = MainPlayer.Pos.x - GameEnemies[i].Pos.x;
		MovDir.y = MainPlayer.Pos.y - GameEnemies[i].Pos.y;
		GameEnemies[i].MovementDir = NormalizeVector(MovDir);
		GameEnemies[i].Rotation = EnemyRotateStep;

		double SlowdownSpeedMod = 10 / (10 + SlowdownTimerMod);
		GameEnemies[i].Pos.x += abs(GameEnemies[i].Speed * TickDifference) * GameEnemies[i].MovementDir.x * SlowdownSpeedMod;
		GameEnemies[i].Pos.y += abs(GameEnemies[i].Speed * TickDifference) * GameEnemies[i].MovementDir.y * SlowdownSpeedMod;
		GameEnemies[i].Collision = UpdateCollision(GameEnemies[i].Pos, GameEnemies[i].Height, GameEnemies[i].Width);
		if (IsColliding(GameEnemies[i].Collision, MainPlayer.Collision))
		{
			//GameEnemies[i].Pos = { 0,0 };			
			GameEnemies.erase(GameEnemies.begin() + i);
			RemoveHearts(1);
			MainPlayer.IsDamaged = true;
			TimerHeartDamaged = 0;
			i--;
		}
	}
	// Изменение скорости в соответствии с замедлением
	double SlowdownSpeedMod = 10 / (10 + SlowdownTimerMod);
	// изменение скорости дабы избежать перекрытия имен
	for (int i = 0; i < GameEnemies.size(); i++)
	{
		for (int j = i; j < GameEnemies.size(); j++)
		{
			if (abs(GameEnemies[i].Pos.y - GameEnemies[j].Pos.y) < 60 && abs(GameEnemies[i].Pos.x - GameEnemies[j].Pos.x) < 100)
			{
				GameEnemies[i].Pos.x -= abs(GameEnemies[i].Speed * TickDifference) * GameEnemies[i].MovementDir.x * SlowdownSpeedMod * 0.5;
				GameEnemies[i].Pos.y -= abs(GameEnemies[i].Speed * TickDifference) * GameEnemies[i].MovementDir.y * SlowdownSpeedMod * 0.5;
			}
		}
	}
	// Сердца
	if (TimerHeartRotate > 1)
	{
		TimerHeartRotate = 0;
		UpdateHearts(HeartRotateStep);
		HeartRotateStep += 1;
		if (HeartRotateStep > 360)
		{
			HeartRotateStep = 0;
		}
	}
	// Бонусы
	if (TimerBonusUpdate > 2)
	{
		TimerBonusUpdate = 0;
		for (int i = 0, SizeDecrease = 7; i < GameBonuses.size(); i++)
		{
			if (GameBonuses[i].RotationClockwise)
			{
				GameBonuses[i].Rotation += 5;
				if (GameBonuses[i].Rotation > 225)
				{
					GameBonuses[i].RotationClockwise = false;
				}
			}
			else
			{
				GameBonuses[i].Rotation -= 5;
				if (GameBonuses[i].Rotation < 135)
				{
					GameBonuses[i].RotationClockwise = true;
				}
			}
			if (GameBonuses[i].Size < GameBonuses[i].FullSize && GameBonuses[i].Lifetime > 0)
			{
				GameBonuses[i].Size += SizeDecrease;
				if (GameBonuses[i].Size > GameBonuses[i].FullSize)
				{
					GameBonuses[i].Size = GameBonuses[i].FullSize;
				}
			}
			else if (GameBonuses[i].Size == GameBonuses[i].FullSize && GameBonuses[i].Lifetime > 0)
			{
				GameBonuses[i].Lifetime--;
			}
			else if (GameBonuses[i].Size <= GameBonuses[i].FullSize && GameBonuses[i].Lifetime <= 0)
			{
				GameBonuses[i].Size -= SizeDecrease;
			}
			if (GameBonuses[i].Size <= 1 && GameBonuses[i].Lifetime <= 0)
			{
				GameBonuses.erase(GameBonuses.begin() + i);
				i--;
			}
		}
	}
}
void UpdateEnemyRotation(double SlowdownTimerMod, double& EnemyRotateStep)
{
	if (SlowdownTimerMod)
	{
		EnemyRotateStep += 25 * (1.0 / SlowdownTimerMod + 0.1);
	}
	else
	{
		EnemyRotateStep += 25;
	}
	if (EnemyRotateStep >= 360)
	{
		EnemyRotateStep -= 360;
	}
}