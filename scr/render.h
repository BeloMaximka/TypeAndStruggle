#pragma once
#include "main.h"
void RenderTexture(SDL_Texture* Texture, int PosX, int PosY, int Width, int Height);
void RenderTexture(SDL_Texture* Texture, int PosX, int PosY);
void RenderText(const char* Text, TTF_Font* Font, int x, int y, SDL_Color Color, bool Centered);
void RenderText(const char* Text, TTF_Font* Font, int x, int y, Uint8 ColorRed, Uint8 ColorGreen, Uint8 ColorBlue, Uint8 ColorAlpha, bool Centered);
void RenderTextureCentered(SDL_Texture* Texture, int PosX, int PosY, double Angle);
void DrawPauseMenuFrame();
void DrawDifficultyFrame();
void DrawMainMenuFrame();
void DrawHighscoresFrame();
void DrawHighscoreEnterFrame(const std::string& WordInput);
void DrawDeadFrame();
void DrawGameSessionFrame(const std::string& WordInput);