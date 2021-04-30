#include "main.h"
using namespace std;

const char* WINDOW_NAME = "Type&Struggle";
int TRUE_RESOLUTION_X = 1080; // 640
int TRUE_RESOLUTION_Y = 1080; // 480
int WINDOW_RESOLUTION_X = 720; // 1280
int WINDOW_RESOLUTION_Y = 720; // 720
SDL_Renderer* RendererPrimary;
SDL_Window* WindowPrimary;
ipoint MousePosWindow;

bool FPSCounter = 0;
Uint32 TickTimer;
Uint32 SlowdownDecreaseTimer;
Uint32 TickCurrent = SDL_GetTicks();
Uint32 TicksToSecond_FPS = SDL_GetTicks();
int TickDifference = SDL_GetTicks();
int FramesPerSecondPresent = 0;

EntityPlayer MainPlayer;
int ArenaWidth = TRUE_RESOLUTION_X;
int ArenaHeight = TRUE_RESOLUTION_Y;
const int GameHighscoresSize = 10;
highscore GameHighscores[GameHighscoresSize];

std::vector<std::string> WordsList;
buttons GameButtons;
std::string WordInput = "";

bool PlayerDead = false;

double DifficultySpeedModifier = 1;
double SlowdownTimerMod = 0;
int FramesPerSecondTarget = 60;
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
	ButtonToAdd.Pos = { (double)TRUE_RESOLUTION_X / 2, (double)3*TRUE_RESOLUTION_Y / 8 + (double)TRUE_RESOLUTION_Y / 2 };
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
// Иницализация игры
void GameInit() {
	// Пересоздание лога
	SDL_RWclose(SDL_RWFromFile("log.txt", "w"));
	WriteInLog("[INFO] Starting game initialization...");

	WriteInLog("[INFO] SDL initialization...");
	// Сначала подсистемы SDL нужно инициализировать
	// Тут мы указываем все системы
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		// При успехе функция вернёт 0, если нет - отправляем в лог сообщение об ошибке
		WriteInLog("[ERROR] SDL_Init error: %s", SDL_GetError());
		return;
	}
	//Иницализациия SDL_image
	if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG)
	{
		WriteInLog("[ERROR] IMG_Init error: %s", SDL_GetError());
		SDL_Quit();
		return;
	}
	//Иницализациия SDL_ttf
	if (TTF_Init() == -1) {
		WriteInLog("[ERROR] TTF_Init error: %s", TTF_GetError());
		return;
	}
	// Создаем окно программы
	WindowPrimary = SDL_CreateWindow(WINDOW_NAME, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_RESOLUTION_X, WINDOW_RESOLUTION_Y, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);//| SDL_WINDOW_BORDERLESS
	// Опять же, проверка на возможные ошибки
	if (WindowPrimary == nullptr) {
		WriteInLog("[ERROR] SDL_CreateWindow error: %s", SDL_GetError());
		return;
	}
	// Создаём рендер
	RendererPrimary = SDL_CreateRenderer(WindowPrimary, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (RendererPrimary == nullptr) {
		WriteInLog("[ERROR] SDL_CreateRenderer error: %s", SDL_GetError());
		return;
	}
	// Создаём независимое разрешение реднеринга, которое масштабируется под размеры окна
	if (SDL_RenderSetLogicalSize(RendererPrimary, TRUE_RESOLUTION_X, TRUE_RESOLUTION_Y) != 0)
	{
		WriteInLog("[ERROR] SDL_RenderSetLogicalSize error: %s", SDL_GetError());
		return;
	}
	SDL_SetRenderDrawBlendMode(RendererPrimary, SDL_BLENDMODE_BLEND);
	// Загружаем ресурсы игры в память
	WriteInLog("[INFO] Loading game resources...");
	InitResources();

	// Загружаем слова с текстового файла
	string TempWord = "";
	char Buffer;
	SDL_RWops* File = SDL_RWFromFile("classic.txt", "r");
	if (File != nullptr)
	{
		unsigned int FileSize = SDL_RWsize(File);
		for (int i = 0; i < FileSize; i++)
		{
			SDL_RWread(File, &Buffer, sizeof(char), 1);
			if (Buffer == '\r')
			{
				SDL_RWread(File, &Buffer, sizeof(char), 1);
				WordsList.push_back(TempWord);
				TempWord = "";
			}
			else
			{
				TempWord += Buffer;
			}
		}
		SDL_RWclose(File);
	}
	else
	{
		WriteInLog("[ERROR] Cannot open file \"classic.txt\"!");
		return;
	}
	// Загружаем рекорды с бинарника     
	File = SDL_RWFromFile("data.bin", "r");
	if (File != nullptr)
	{
		unsigned int FileSize = SDL_RWsize(File);
		if (FileSize < sizeof(highscore) * GameHighscoresSize)
		{
			WriteInLog("[ERROR] \"data.bin\" is corrupted!");
			WriteInLog("[INFO] Creating new \"data.bin\"...");
			SDL_RWclose(File);
			File = SDL_RWFromFile("data.bin", "w");
			highscore HighscoreToWrite;
			for (int i = 0; i < 16; i++)
			{
				HighscoreToWrite.Name[i] = '_';
			}
			HighscoreToWrite.Name[15] = '\0';
			HighscoreToWrite.Score = -1;
			HighscoreToWrite.Difficulty = -1;
			HighscoreToWrite.Mode = -1;
			for (int j = 0; j < GameHighscoresSize; j++)
			{
				GameHighscores[j] = HighscoreToWrite;
				SDL_RWwrite(File, &HighscoreToWrite, sizeof(highscore), 1);
			}
			SDL_RWclose(File);
		}
		for (int i = 0; i < GameHighscoresSize; i++)
		{
			SDL_RWread(File, &GameHighscores[i].Name, sizeof(char), 16);
			SDL_RWread(File, &GameHighscores[i].Score, sizeof(int), 1);
			SDL_RWread(File, &GameHighscores[i].Difficulty, sizeof(int), 1);
			SDL_RWread(File, &GameHighscores[i].Mode, sizeof(int), 1);
		}
		SDL_RWclose(File);
	}
	else
	{
		WriteInLog("[ERROR] Cannot find file \"data.bin\"!");
		WriteInLog("[INFO] Creating new \"data.bin\"...");
		File = SDL_RWFromFile("data.bin", "w");
		highscore HighscoreToWrite;
		for (int i = 0; i < 16; i++)
		{
			HighscoreToWrite.Name[i] = '_';
		}
		HighscoreToWrite.Name[15] = '\0';
		HighscoreToWrite.Score = -1;
		HighscoreToWrite.Difficulty = -1;
		HighscoreToWrite.Mode = -1;
		for (int j = 0; j < GameHighscoresSize; j++)
		{
			GameHighscores[j] = HighscoreToWrite;
			SDL_RWwrite(File, &HighscoreToWrite, sizeof(highscore), 1);
		}
		SDL_RWclose(File);
	}

	// Создаем кнопочки
	InitButtons();
	// Скрываем курсор
	SDL_ShowCursor(0);
}
// Выход из игры
inline void QuitGame() {
	SDL_DestroyRenderer(RendererPrimary);
	SDL_DestroyWindow(WindowPrimary);
	SDL_Quit();
	exit(0);
}
inline void SetupGame(double& EnemySpawnDelay, DifficultyCode Difficulty, bool ArithmeticMode) {
	GamePlayerHearts.clear();
	if (Difficulty == DifficultyCode::EASY)
	{
		DifficultySpeedModifier = ArithmeticMode ? 0.7 : 0.6;
		AddHearts(2);
	}
	else if (Difficulty == DifficultyCode::NORMAL)
	{
		DifficultySpeedModifier = ArithmeticMode ? 0.7 : 0.8;
	}
	else if (Difficulty == DifficultyCode::HARD)
	{
		DifficultySpeedModifier = ArithmeticMode ? 0.5 : 0.8;
	}
	AddHearts(3);
	GameBonuses.clear();
	GameEnemies.clear();
	WordInput = "";
	MainPlayer.Score = 0;
	MainPlayer.IsDamaged = false;
	PlayerDead = false;
	if (ArithmeticMode && Difficulty == DifficultyCode::HARD)
	{
		EnemySpawnDelay = 300;
	}
	else
	{
		EnemySpawnDelay = 200;
	}

}
void EnterWord(std::string& WordInput, bool ArithmeticMode, DifficultyCode Difficulty)
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
			if (Difficulty == DifficultyCode::EASY)
			{
				ScoreModifier = 0.5;
			}
			else if (Difficulty == DifficultyCode::NORMAL)
			{
				ScoreModifier = 1;
			}
			else if (Difficulty == DifficultyCode::HARD)
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
void GameSession(bool ArithmeticMode, DifficultyCode Difficulty)
{
	Uint32 TicksToNextFrame = SDL_GetTicks();
	std::string WordInput;
	double EnemySpawnDelay = 200;
	SetupGame(EnemySpawnDelay, Difficulty, ArithmeticMode);
	while (true)
	{
		// Чтобы игра слишком часто не обновлялась
		if (TickCurrent - SDL_GetTicks() < 1)
		{
			SDL_Delay(1);
		}

		UpdateEntities();
		if (PlayerDead)
		{
			SDL_RestoreWindow(WindowPrimary);
			DrawGameSessionFrame(WordInput);
			// Сохраняем кадр и размываем его
			int Width;
			int Height;
			SDL_GetRendererOutputSize(RendererPrimary, &Width, &Height);

			SDL_Surface* SourceSurface = SDL_CreateRGBSurfaceWithFormat(0, Width, Height, 32, SDL_PIXELFORMAT_ARGB8888);
			*(Uint32*)SourceSurface->pixels = 0;
			SDL_RenderReadPixels(RendererPrimary, NULL, SDL_PIXELFORMAT_ARGB8888, SourceSurface->pixels, SourceSurface->pitch);

			int SmallerSize = 300;
			SDL_Surface* SmallerSurface = SDL_CreateRGBSurfaceWithFormat(0, SmallerSize, SmallerSize, 32, SDL_PIXELFORMAT_ARGB8888);			
			SDL_Rect SmallerImageSize{ 0,0,SmallerSize,SmallerSize };
			SDL_BlitScaled(SourceSurface, NULL, SmallerSurface, &SmallerImageSize);

			Blur((Uint32*)SmallerSurface->pixels, SmallerSurface->w, SmallerSurface->h, 2);
			SDL_Texture* BlurredTexture = SDL_CreateTextureFromSurface(RendererPrimary, SmallerSurface);
			DeadMenuCode DeadCode = DeadMenu(BlurredTexture, Difficulty, ArithmeticMode);

			// Удаляем изображение из памяти
			SDL_FreeSurface(SourceSurface);
			SDL_FreeSurface(SmallerSurface);
			SDL_DestroyTexture(BlurredTexture);
			if (DeadCode == DeadMenuCode::RETRY)
			{
				SetupGame(EnemySpawnDelay, Difficulty, ArithmeticMode);
				continue;
			}
			else if (DeadCode == DeadMenuCode::TO_MAIN_MENU)
			{
				return;
			}
		}

		TickDifference = TickCurrent;
		TickCurrent = SDL_GetTicks();
		TickDifference -= TickCurrent;
		if (TickCurrent - SlowdownDecreaseTimer > 100 && SlowdownTimerMod > 0)
		{
			SlowdownDecreaseTimer = TickCurrent;
			SlowdownTimerMod -= 1;
			if (SlowdownTimerMod < 0)
			{
				SlowdownTimerMod = 0;
			}
		}
		if (TickCurrent - TickTimer >= 10 + SlowdownTimerMod)
		{
			TickTimer = TickCurrent;
			UpdateTimers();
		}
		if (TickCurrent - TicksToNextFrame > (1.0 / FramesPerSecondTarget) * 1000)
		{
			TicksToNextFrame = TickCurrent;
			UpdateEnemyRotation(SlowdownTimerMod, EnemyRotateStep);
			DrawGameSessionFrame(WordInput);
			SDL_RenderPresent(RendererPrimary);
			SDL_RenderClear(RendererPrimary);
		}

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
			InputCode KeyCode = ReadGameSessionKeys(Event, WordInput);
			ReadMouse(Event);
			if (KeyCode == InputCode::GAMESESSION_ENTER)
			{
				EnterWord(WordInput, ArithmeticMode, Difficulty);
			}
			else if (KeyCode == InputCode::GAMESESSION_PAUSE)
			{
				PauseMenuCode PauseCode = PauseMenu();
				if (PauseCode == PauseMenuCode::RESTART)
				{
					SetupGame(EnemySpawnDelay, Difficulty, ArithmeticMode);
					continue;
				}
				else if (PauseCode == PauseMenuCode::TO_MAIN_MENU)
				{
					SetupGame(EnemySpawnDelay, Difficulty, ArithmeticMode);
					return;
				}
				else if (PauseCode == PauseMenuCode::TO_DESKTOP)
				{
					QuitGame();
				}
			}
		}
		if (TimerSpawnRateIncrease > 100)
		{
			TimerSpawnRateIncrease = 0;
			EnemySpawnDelay -= 0.25;
		}
		if (TimerEnemySpawn > EnemySpawnDelay)
		{
			TimerEnemySpawn = 0;
			SpawnEnemy(Difficulty, ArithmeticMode);
		}
		if (TimerBonusSpawn > 3000)
		{
			TimerBonusSpawn = 0;
			if (rand() % 3 > 1)
			{
				SpawnBonus(Difficulty, ArithmeticMode);
			}
		}
	}
}

int main(int argc, char* argv[])
{
	// Переменные
	MousePosWindow.x = WINDOW_RESOLUTION_X;
	MousePosWindow.y = WINDOW_RESOLUTION_Y;
	//
	MainPlayer.Pos.x = TRUE_RESOLUTION_X / 2;
	MainPlayer.Pos.y = TRUE_RESOLUTION_Y / 2;
	MainPlayer.Height = 96;
	MainPlayer.Width = 96;
	MainPlayer.Collision = UpdateCollision(MainPlayer.Pos, MainPlayer.Height, MainPlayer.Width);
	MainPlayer.Rotation = 90;
	MainPlayer.Speed = 1;
	MainPlayer.MovementDir.x = 0;
	MainPlayer.MovementDir.y = 0;
	//
	WriteInLog("[INFO] Starting the game...");
	GameInit();
	srand(time(0));
	SDL_SetRenderDrawColor(RendererPrimary, 0, 0, 0, 255);
	SDL_StartTextInput();
	TickTimer = SDL_GetTicks();
	SlowdownDecreaseTimer = SDL_GetTicks();
	MainMenu();

	//Выходим из приложения
	QuitGame();
	return 0;
}