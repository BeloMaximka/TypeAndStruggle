#include "main.h"

#define IMG_MISSING_RES 16
#define IMG_MISSING_PIXEL_FIRST 0x0
#define IMG_MISSING_PIXEL_SECOND 0xFF00FFFF
#define NORMALFONT_SIZE 36
#define SCORESFONT_SIZE 54
#define MENUFONT_SIZE 108
#define FONT_FILEPATH "font.ttf"

SDL_Texture* img_missing_texture;
Mix_Chunk* snd_missing_sound{};
Mix_Music* snd_missing_music{};

std::string Text[TXT_LAST];
std::vector<SDL_Texture*> Textures;
std::vector<Mix_Chunk*> Sounds;
Mix_Music* GameMusic;

TTF_Font* NormalFont;
TTF_Font* ScoresFont;
TTF_Font* MenuFont;

const int CorrectFileSize = sizeof(highscore) * GameHighscoresSize + sizeof(double) * 2 + sizeof(int) * 3;

void LoadText(const char* lang)
{
	int BufferSize = 32;
	char* Buffer = new char[BufferSize];
	sprintf_s(Buffer, BufferSize, "lang\\%s.txt", lang);
	SDL_RWops* File = SDL_RWFromFile(Buffer, "r");
	if (!File) {
		WriteInLog("[ERROR] Unable to read %s.txt by path \"lang\": %s", lang, SDL_GetError());
		return;
	}
	delete[] Buffer;
	char CurChar;
	for (int i = 1; i < TXT_LAST; i++)
	{
		Text[i].clear();
	}
	for (int i = 1; i < TXT_LAST; i++)
	{
		while (SDL_RWread(File, &CurChar, sizeof(char), 1))
		{
			if (CurChar == '\n')
			{
				continue;
			}
			else if (CurChar != '\r')
			{
				Text[i] += CurChar;
			}
			else
			{
				break;
			}
		}
	}
	SDL_RWclose(File);
	SetButtonsSize(GameButtons, MenuFont);

	// Загружаем слова с текстового файла
	WordsList.clear();
	Buffer = new char[BufferSize];
	sprintf_s(Buffer, BufferSize, "words\\%s.txt", lang);
	std::string TempWord = "";
	File = SDL_RWFromFile(Buffer, "r");
	char Temp;
	if (File != nullptr)
	{
		unsigned int FileSize = SDL_RWsize(File);
		for (int i = 0; i < FileSize; i++)
		{
			SDL_RWread(File, &Temp, sizeof(char), 1);
			if (Temp == '\r')
			{
				SDL_RWread(File, &Temp, sizeof(char), 1);
				WordsList.push_back(TempWord);
				TempWord = "";
			}
			else
			{
				TempWord += Temp;
			}
		}
		SDL_RWclose(File);
	}
	else
	{
		WriteInLog("[ERROR] Cannot open file \"%s.txt\": %s", lang, SDL_GetError());
		return;
	}
}

void CreateNewDataFile()
{
	SDL_RWops* File = SDL_RWFromFile("data.bin", "w");
	highscore HighscoreToWrite{};
	for (int i = 0; i < HIGHSCORE_NAME_SIZE / 2; i++)
	{
		HighscoreToWrite.Name[i] = '_';
	}
	HighscoreToWrite.Score = -1;
	HighscoreToWrite.Difficulty = -1;
	HighscoreToWrite.Mode = -1;
	for (int j = 0; j < GameHighscoresSize; j++)
	{
		GameHighscores[j] = HighscoreToWrite;
		SDL_RWwrite(File, &HighscoreToWrite, sizeof(highscore), 1);
	}

	double Temp = 0; // Настройки звука в ноль
	SDL_RWwrite(File, &Temp, sizeof(double), 1);
	SDL_RWwrite(File, &Temp, sizeof(double), 1);

	int Res = 720; // разрешение
	SDL_RWwrite(File, &Res, sizeof(int), 1);
	SDL_RWwrite(File, &Res, sizeof(int), 1);
	Res = LANG_EN; // Язык
	SDL_RWwrite(File, &Res, sizeof(int), 1);
	SDL_RWclose(File);
	SetSFXVolume(0);
	SetMusicVolume(0);
}

void LoadSavedData(highscore GameHighscores[], Sliders& GameSliders, int& WinResX, int& WinResY, int& Lang)
{
	// Загружаем рекорды с бинарника     
	SDL_RWops* File = SDL_RWFromFile("data.bin", "r");
	if (File != nullptr)
	{
		unsigned int FileSize = SDL_RWsize(File);
		if (FileSize < CorrectFileSize)
		{
			WriteInLog("[ERROR] \"data.bin\" is corrupted!");
			WriteInLog("[INFO] Creating new \"data.bin\"...");
			SDL_RWclose(File);
			CreateNewDataFile();
		}
		else
		{
			for (int i = 0; i < GameHighscoresSize; i++)
			{
				SDL_RWread(File, &GameHighscores[i], sizeof(highscore), 1);
			}
		}
		SDL_RWread(File, &GameSliders[SLDR_SFX].Value, sizeof(double), 1);
		SDL_RWread(File, &GameSliders[SLDR_MUSIC].Value, sizeof(double), 1);
		SetSFXVolume(GameSliders[SLDR_SFX].Value);
		SetMusicVolume(GameSliders[SLDR_MUSIC].Value);
		SDL_RWread(File, &WinResX, sizeof(int), 1);
		SDL_RWread(File, &WinResY, sizeof(int), 1);
		SDL_RWread(File, &Lang, sizeof(int), 1);
		SDL_RWclose(File);
	}
	else
	{
		WriteInLog("[ERROR] Cannot find file \"data.bin\"!");
		WriteInLog("[INFO] Creating new \"data.bin\"...");
		CreateNewDataFile();
	}
}

Mix_Chunk* LoadSound(const char* FilePath)
{
	Mix_Chunk* Sound = Mix_LoadWAV(FilePath);
	if (!Sound) {
		WriteInLog("[ERROR] Unable to load sound by path \"%s\": %s", FilePath, Mix_GetError());
		return snd_missing_sound;
	}
	return Sound;
}

Mix_Music* LoadMusic(const char* FilePath)
{
	Mix_Music* Music = Mix_LoadMUS(FilePath);
	if (!Music) {
		WriteInLog("[ERROR] Unable to load music by path \"%s\": %s", FilePath, Mix_GetError());
		return snd_missing_music;
	}
	return Music;
}

TTF_Font* LoadFont(const char* FilePath, int FontSize) {
	TTF_Font* Font = TTF_OpenFont(FilePath, FontSize);
	if (Font == nullptr) {
		WriteInLog("[ERROR] Unable to open font file by path %s!", FilePath);
		return nullptr;
	}
	return Font;
}

SDL_Texture* GetTextTexture(const char* Text, TTF_Font* Font, SDL_Color Color)
{
	// Загружаем шрифт в поверхность
	SDL_Surface* FontSurface = TTF_RenderUTF8_Blended(Font, Text, Color);
	if (FontSurface == nullptr && strlen(Text) > 0) {
		WriteInLog("[ERROR] Unable to render the text \"%s\"! Can't create the font surface.", Text);
		return nullptr;
	}
	// Создаём текстуру текста с поверхности
	SDL_Texture* FontTexture = SDL_CreateTextureFromSurface(RendererPrimary, FontSurface);
	if (FontTexture == nullptr && strlen(Text) > 0) {
		WriteInLog("[ERROR] Unable to render the text \"%s\"! Can't create the texture.", Text);
	}
	// Очистка поверхности
	SDL_FreeSurface(FontSurface);
	return FontTexture;
}

SDL_Texture* CreateMissingTexture() {
	SDL_Texture* Texture = SDL_CreateTexture(RendererPrimary, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, IMG_MISSING_RES, IMG_MISSING_RES);
	Uint32 pixels[IMG_MISSING_RES][IMG_MISSING_RES];
	for (int y = 0; y < IMG_MISSING_RES; y++) {
		for (int x = 0; x < IMG_MISSING_RES; x++) {
			pixels[y][x] = (y + x) % 2 ? IMG_MISSING_PIXEL_FIRST : IMG_MISSING_PIXEL_SECOND;
		}
	}
	SDL_UpdateTexture(Texture, NULL, pixels, IMG_MISSING_RES * 4);
	return Texture;
}

SDL_Texture* LoadTexture(const char* FilePath, SDL_Renderer* Renderer = RendererPrimary)
{
	SDL_Texture* Texture = IMG_LoadTexture(Renderer, FilePath);
	if (Texture == nullptr)
	{
		WriteInLog("[ERROR] Unable to load texture by path \"%s\": %s", FilePath, SDL_GetError());
		WriteInLog("[ERROR] Replacing \"%s\" with the missing_texture texture..", FilePath);
		return img_missing_texture;
	}
	return Texture;
}

void InitResources() {
	WriteInLog("[INFO] Loading textures...");
	img_missing_texture = CreateMissingTexture();
	Textures.push_back(CreateMissingTexture());
	Textures.push_back(LoadTexture("images/arena.jpg"));
	Textures.push_back(LoadTexture("images/cursor.png"));
	Textures.push_back(LoadTexture("images/player.png"));
	Textures.push_back(LoadTexture("images/heart.png"));
	Textures.push_back(LoadTexture("images/cosmetic_heart.png"));
	Textures.push_back(LoadTexture("images/cosmetic_star.png"));
	Textures.push_back(LoadTexture("images/enemy.png"));
	Textures.push_back(LoadTexture("images/player_damaged.png"));
	Textures.push_back(LoadTexture("images/bonus_random.png"));
	Textures.push_back(LoadTexture("images/bonus_heart.png"));
	Textures.push_back(LoadTexture("images/bonus_x2.png"));
	Textures.push_back(LoadTexture("images/bonus_slowdown.png"));

	WriteInLog("[INFO] Loading font...");
	NormalFont = LoadFont(FONT_FILEPATH, NORMALFONT_SIZE);
	MenuFont = LoadFont(FONT_FILEPATH, MENUFONT_SIZE);
	ScoresFont = LoadFont(FONT_FILEPATH, SCORESFONT_SIZE);

	WriteInLog("[INFO] Loading audio...");
	GameMusic = LoadMusic("sounds/music.wav");

	Sounds.push_back(LoadSound("sounds/boop.wav"));
	Sounds.push_back(LoadSound("sounds/bloop.wav"));
	Sounds.push_back(LoadSound("sounds/click.wav"));
	Sounds.push_back(LoadSound("sounds/click2.wav"));
	Sounds.push_back(LoadSound("sounds/whoosh.wav"));
	Sounds.push_back(LoadSound("sounds/hurt.wav"));
	Sounds.push_back(LoadSound("sounds/death.wav"));
}