#pragma once
#include "main.h"
//------------------------------------------------------
// game_resouces.h
//------------------------------------------------------
// Файл, отвечающий за хранение и работу ресурсов игры
//------------------------------------------------------

enum GameImages
{
	GIMG_MISSING,
	GIMG_MAP,
	GIMG_INTERFACE_CURSOR,
	GIMG_SPRITES_PLAYER,
	GIMG_SPRITES_HEART,
	GIMG_SPRITES_COSMETIC_HEART,
	GIMG_SPRITES_COSMETIC_STAR,
	GIMG_SPRITES_ENEMY,
	GIMG_SPRITES_PLAYER_DAMAGED,
	GIMG_SPRITES_BONUS_RANDOM,
	GIMG_SPRITES_BONUS_HEART,
	GIMG_SPRITES_BONUS_X2,
	GIMG_SPRITES_BONUS_SLOWDOWN,
};

enum GameSounds
{
	GSND_BOOP,
	GSND_BLOOP,
	GSND_CLICK,
	GSND_CLICK2,
	GSND_LAST

};

void LoadSavedData(highscore GameHighscores[], Sliders& GameSliders);
TTF_Font* LoadFont(const char* FilePath, int FontSize);
SDL_Texture* GetTextTexture(const char* Text, TTF_Font* Font, SDL_Color Color);
SDL_Texture* CreateMissingTexture();
SDL_Texture* LoadTexture(const char* FilePath, SDL_Renderer* Renderer);
void InitResources();

//------------------------------------------------------
// Шрифты
//------------------------------------------------------
extern TTF_Font* NormalFont;
extern TTF_Font* MenuFont;
extern TTF_Font* ScoresFont;
//------------------------------------------------------
// Текстуры
//------------------------------------------------------
extern SDL_Texture* img_missing_texture;
extern std::vector<SDL_Texture*> Textures;
//------------------------------------------------------
// Аудио
//------------------------------------------------------
extern std::vector<Mix_Chunk*> Sounds;
extern Mix_Music* GameMusic;

