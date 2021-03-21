#include "main.h"
#define SCREENPOS_X_CENTERED TRUE_RESOLUTION_X / 2
#define SCREENPOS_Y_CENTERED TRUE_RESOLUTION_Y / 2
// ��������� ����� ��� ����
char FPSString[10] = { '0','\0' };
// ���������� �������� ����� ������
int HeartbeatRate = 100;
//SDL_Color ColorDefaultBlue = { 44, 85, 107, 255 };
SDL_Color ColorDefaultBlue = { 54, 88, 163, 255 };

// �������� ��������
void RenderTexture(SDL_Texture* Texture, int PosX, int PosY, int Width, int Height)
{
    SDL_Rect DestinationRectangle;
    DestinationRectangle.x = PosX;
    DestinationRectangle.y = PosY;
    DestinationRectangle.w = Width;
    DestinationRectangle.h = Height;
    SDL_RenderCopy(RendererPrimary, Texture, NULL, &DestinationRectangle);
}
// �������� �������� ��� ����n����������
void RenderTexture(SDL_Texture* Texture, int PosX, int PosY)
{
    int Width, Height;
    SDL_QueryTexture(Texture, NULL, NULL, &Width, &Height);
    SDL_Rect DestinationRectangle;
    DestinationRectangle.x = PosX;
    DestinationRectangle.y = PosY;
    DestinationRectangle.w = Width;
    DestinationRectangle.h = Height;
    SDL_RenderCopy(RendererPrimary, Texture, NULL, &DestinationRectangle);
}
// ������ ������
void RenderText(const char* Text, TTF_Font* Font, int x, int y, Uint8 ColorRed, Uint8 ColorGreen, Uint8 ColorBlue, Uint8 ColorAlpha, bool Centered) {
    SDL_Color Color;
    Color.r = ColorRed;
    Color.g = ColorGreen;
    Color.b = ColorBlue;
    Color.a = ColorAlpha;
    SDL_Texture* TextTexture = GetTextTexture(Text, Font, Color);
    if (Centered)
    {
        RenderTextureCentered(TextTexture, x, y, 180);
    }
    else
    {
        RenderTexture(TextTexture, x, y);
    }    
    SDL_DestroyTexture(TextTexture);
}
// ������ ������ � �������������� ������ �����
inline void RenderText(const char* Text, TTF_Font* Font, int x, int y, SDL_Color Color, bool Centered) {
    RenderText(Text, Font, x, y, Color.r, Color.g, Color.b, Color.a, Centered);
}
void RenderTextureCentered(SDL_Texture* Texture, int PosX, int PosY, double Angle = 0) {
    int Width, Height;
    SDL_QueryTexture(Texture, NULL, NULL, &Width, &Height);

    SDL_Rect DestinationRectangle;
    DestinationRectangle.x = PosX - Width / 2;
    DestinationRectangle.y = PosY - Height / 2;
    DestinationRectangle.w = Width;
    DestinationRectangle.h = Height;

    SDL_RendererFlip RendererFlip = (SDL_RendererFlip)(SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL);
    SDL_RenderCopyEx(RendererPrimary, Texture, NULL, &DestinationRectangle, Angle, NULL, RendererFlip);
}
void RenderTextureCentered(SDL_Texture* Texture, int PosX, int PosY, int Width, int Height, double Angle = 0) {
    SDL_Rect DestinationRectangle;
    DestinationRectangle.x = PosX - Width / 2;
    DestinationRectangle.y = PosY - Height / 2;
    DestinationRectangle.w = Width;
    DestinationRectangle.h = Height;

    SDL_RendererFlip RendererFlip = (SDL_RendererFlip)(SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL);
    SDL_RenderCopyEx(RendererPrimary, Texture, NULL, &DestinationRectangle, Angle, NULL, RendererFlip);
}
void DrawButton(int ButtonId, int LineThickness) {
    SDL_Rect Line;
    SDL_SetRenderDrawColor(RendererPrimary, ColorDefaultBlue.r, ColorDefaultBlue.g, ColorDefaultBlue.b, ColorDefaultBlue.a);
    // �������
    Line = { (int)Buttons[ButtonId].Pos.x - Buttons[ButtonId].Width / 2,(int)Buttons[ButtonId].Pos.y - Buttons[ButtonId].Heigth / 2, Buttons[ButtonId].Width,  LineThickness };
    SDL_RenderFillRect(RendererPrimary, &Line);
    // ������
    Line = { (int)Buttons[ButtonId].Pos.x - Buttons[ButtonId].Width / 2,(int)Buttons[ButtonId].Pos.y + Buttons[ButtonId].Heigth / 2, Buttons[ButtonId].Width,  LineThickness };
    SDL_RenderFillRect(RendererPrimary, &Line);
    // �����
    Line = { (int)Buttons[ButtonId].Pos.x - Buttons[ButtonId].Width / 2,(int)Buttons[ButtonId].Pos.y - Buttons[ButtonId].Heigth / 2, LineThickness,   Buttons[ButtonId].Heigth };
    SDL_RenderFillRect(RendererPrimary, &Line);
    // ������
    Line = { (int)Buttons[ButtonId].Pos.x + Buttons[ButtonId].Width / 2,(int)Buttons[ButtonId].Pos.y - Buttons[ButtonId].Heigth / 2, LineThickness,   Buttons[ButtonId].Heigth + LineThickness };
    SDL_RenderFillRect(RendererPrimary, &Line);
    RenderText(Buttons[ButtonId].Text.c_str(), MenuFont, Buttons[ButtonId].Pos.x, Buttons[ButtonId].Pos.y, ColorDefaultBlue, true);
}
void DrawFrame() {
    if (FramesPerSecondPresent > 10000) FramesPerSecondPresent = 0;
    FramesPerSecondPresent++;   
    // �������
    // ���� � ����
    if (IngameMenuShow)
    {
        RenderTexture(Textures[GIMG_MAP], 0, 0, ArenaWidth, ArenaHeight);        
        SDL_Rect Line = { SCREENPOS_X_CENTERED - 275,SCREENPOS_Y_CENTERED / 4 + 55 + SCREENPOS_Y_CENTERED / 8, 550, 5 };
        SDL_SetRenderDrawColor(RendererPrimary, ColorDefaultBlue.r, ColorDefaultBlue.g, ColorDefaultBlue.b, ColorDefaultBlue.a);
        SDL_RenderFillRect(RendererPrimary, &Line);        
        SDL_SetRenderDrawColor(RendererPrimary, 255, 255, 255, 255);        
        RenderText("Game Paused", MenuFont, SCREENPOS_X_CENTERED, SCREENPOS_Y_CENTERED/4 + SCREENPOS_Y_CENTERED / 8, ColorDefaultBlue, true);
        // Continue
        DrawButton(BTN_INGAME_CONTINUE, 5);
        // Quit to Main Menu
        DrawButton(BTN_INGAME_QUIT_MAINMENU, 5);
        // Quit to Desktop
        DrawButton(BTN_INGAME_QUIT_DESKTOP, 5);
        // Restart
        DrawButton(BTN_INGAME_RESTART, 5);
    }
    else if (MainMenuShow)
    {
        // ���
        RenderTexture(Textures[GIMG_MAP], 0, 0, ArenaWidth, ArenaHeight);
        // �����
        SDL_Rect Line = { SCREENPOS_X_CENTERED - 250,SCREENPOS_Y_CENTERED / 4 + 55 + SCREENPOS_Y_CENTERED / 8, 500, 5 };
        SDL_SetRenderDrawColor(RendererPrimary, ColorDefaultBlue.r, ColorDefaultBlue.g, ColorDefaultBlue.b, ColorDefaultBlue.a);
        SDL_RenderFillRect(RendererPrimary, &Line);
        SDL_SetRenderDrawColor(RendererPrimary, 255, 255, 255, 255);
        RenderText("Main Menu", MenuFont, SCREENPOS_X_CENTERED, SCREENPOS_Y_CENTERED / 4 + SCREENPOS_Y_CENTERED / 8, ColorDefaultBlue, true);
        // Play classic        
        DrawButton(BTN_MENU_CLASSIC, 5);
        // Play arithmeitc
        DrawButton(BTN_MENU_ARITHMETIC, 5);
        // Scores        
        DrawButton(BTN_MENU_SCORES, 5);
        // Quit        
        DrawButton(BTN_MENU_QUIT_DESKTOP, 5);
    }
    else if (ChoosingDifficultyShow)
    {
        // ���
        RenderTexture(Textures[GIMG_MAP], 0, 0, ArenaWidth, ArenaHeight);
        // �����
        SDL_Rect Line = { SCREENPOS_X_CENTERED - 370,SCREENPOS_Y_CENTERED / 4 + 55 + SCREENPOS_Y_CENTERED / 8, 740, 5 };
        SDL_SetRenderDrawColor(RendererPrimary, ColorDefaultBlue.r, ColorDefaultBlue.g, ColorDefaultBlue.b, ColorDefaultBlue.a);
        SDL_RenderFillRect(RendererPrimary, &Line);
        SDL_SetRenderDrawColor(RendererPrimary, 255, 255, 255, 255);
        RenderText("Choose difficulty:", MenuFont, SCREENPOS_X_CENTERED, SCREENPOS_Y_CENTERED / 4 + SCREENPOS_Y_CENTERED / 8, ColorDefaultBlue, true);
        // Easy
        DrawButton(BTN_DIFFICULTY_EASY, 5);
        // Normal
        DrawButton(BTN_DIFFICULTY_NORMAL, 5);
        // Hard        
        DrawButton(BTN_DIFFICULTY_HARD, 5);
        // Back        
        DrawButton(BTN_DIFFICULTY_BACK, 5);
    }
    else if (HighscoresShow)
    {
        // ���
        RenderTexture(Textures[GIMG_MAP], 0, 0, ArenaWidth, ArenaHeight);
        // ������ Back
        DrawButton(BTN_SCORES_BACK, 5);
        // ������
        RenderText("Highscores", MenuFont, SCREENPOS_X_CENTERED, SCREENPOS_Y_CENTERED / 4 - SCREENPOS_Y_CENTERED / 8, ColorDefaultBlue, true);
        RenderText("  #    Names          Mode   Difficulty   Score    ", ScoresFont, SCREENPOS_X_CENTERED, SCREENPOS_Y_CENTERED / 4 + SCREENPOS_Y_CENTERED / 16, ColorDefaultBlue, true);
        char StrBuffer[13];
        for (int i = 0; i < GameHighscoresSize; i++)
        {
            _itoa_s(i + 1, StrBuffer, 13, 10);
            RenderText(StrBuffer, NormalFont, SCREENPOS_X_CENTERED / 8, SCREENPOS_Y_CENTERED / 4 + SCREENPOS_Y_CENTERED / 8 * (i+1), ColorDefaultBlue, false);
            // �����
            if (GameHighscores[i].Mode == 0)
            {
                RenderText("Classic", NormalFont, SCREENPOS_X_CENTERED / 8 + 460, SCREENPOS_Y_CENTERED / 4 + SCREENPOS_Y_CENTERED / 8 * (i + 1) + 27, ColorDefaultBlue, true);
            }
            else if (GameHighscores[i].Mode == 1)
            {
                RenderText("Arithmetic", NormalFont, SCREENPOS_X_CENTERED / 8 + 460, SCREENPOS_Y_CENTERED / 4 + SCREENPOS_Y_CENTERED / 8 * (i + 1) + 27, ColorDefaultBlue, true);
            }
            else
            {
                RenderText("_____", NormalFont, SCREENPOS_X_CENTERED / 8 + 460, SCREENPOS_Y_CENTERED / 4 + SCREENPOS_Y_CENTERED / 8 * (i + 1) + 27, ColorDefaultBlue, true);
            }
            // ���������
            if (GameHighscores[i].Difficulty == DIFFICULTY_EASY)
            {
                RenderText("Easy", NormalFont, SCREENPOS_X_CENTERED / 8 + 670, SCREENPOS_Y_CENTERED / 4 + SCREENPOS_Y_CENTERED / 8 * (i + 1) + 27, ColorDefaultBlue, true);
            }
            else if (GameHighscores[i].Difficulty == DIFFICULTY_NORMAL)
            {
                RenderText("Normal", NormalFont, SCREENPOS_X_CENTERED / 8 + 670, SCREENPOS_Y_CENTERED / 4 + SCREENPOS_Y_CENTERED / 8 * (i + 1) + 27, ColorDefaultBlue, true);
            }
            else if (GameHighscores[i].Difficulty == DIFFICULTY_HARD)
            {
                RenderText("Hard", NormalFont, SCREENPOS_X_CENTERED / 8 + 670, SCREENPOS_Y_CENTERED / 4 + SCREENPOS_Y_CENTERED / 8 * (i + 1) + 27, ColorDefaultBlue, true);
            }
            else
            {
                RenderText("____", NormalFont, SCREENPOS_X_CENTERED / 8 + 670, SCREENPOS_Y_CENTERED / 4 + SCREENPOS_Y_CENTERED / 8 * (i + 1) + 27, ColorDefaultBlue, true);
            }
            // ����
            if (GameHighscores[i].Score >= 0)
            {
                _itoa_s(GameHighscores[i].Score, StrBuffer, 13, 10);
                RenderText(StrBuffer, NormalFont, SCREENPOS_X_CENTERED / 8 + 870, SCREENPOS_Y_CENTERED / 4 + SCREENPOS_Y_CENTERED / 8 * (i + 1) + 27, ColorDefaultBlue, true);
            }
            else
            {
                RenderText("____", NormalFont, SCREENPOS_X_CENTERED / 8 + 870, SCREENPOS_Y_CENTERED / 4 + SCREENPOS_Y_CENTERED / 8 * (i + 1) + 27, ColorDefaultBlue, true);
            }
            // ���
            RenderText(GameHighscores[i].Name, NormalFont, SCREENPOS_X_CENTERED / 8 + 100, SCREENPOS_Y_CENTERED / 4 + SCREENPOS_Y_CENTERED / 8 * (i + 1), ColorDefaultBlue, false);
        }
    }
    else if (HighscoresEnterShow)
    {
    // ���
    RenderTexture(Textures[GIMG_MAP], 0, 0, ArenaWidth, ArenaHeight);
    // ������
    RenderText("You entered the top 10!", ScoresFont, SCREENPOS_X_CENTERED, SCREENPOS_Y_CENTERED - SCREENPOS_Y_CENTERED / 4, ColorDefaultBlue, true);
    RenderText("Enter the name ( <15 or leave empty to skip):", ScoresFont, SCREENPOS_X_CENTERED, SCREENPOS_Y_CENTERED - SCREENPOS_Y_CENTERED / 8, ColorDefaultBlue, true);
    // �������� �����
    RenderText(WordInput.c_str(), NormalFont, SCREENPOS_X_CENTERED, SCREENPOS_Y_CENTERED, ColorDefaultBlue, true);
    }
    // ������� ����
    else
    {
        // ���
        RenderTexture(Textures[GIMG_MAP], 0, 0, ArenaWidth, ArenaHeight);
        // ������������� �������
        for (int i = 0; i < GameCosmetics.size(); i++)
        {
            if (TimerCosmeticHeartDecrease > 5)
            {
                GameCosmetics[i].Size -= 3;
                if (GameCosmetics[i].Size < 1)
                {
                    GameCosmetics.erase(GameCosmetics.begin() + i);
                    i--;
                    continue;
                }
            }
            if (GameCosmetics[i].Type == PRTCL_HEART)
            {
                RenderTextureCentered(Textures[GIMG_SPRITES_COSMETIC_HEART], GameCosmetics[i].Pos.x, GameCosmetics[i].Pos.y, GameCosmetics[i].Size, GameCosmetics[i].Size, 90);
            }
            else
            {
                RenderTextureCentered(Textures[GIMG_SPRITES_COSMETIC_STAR], GameCosmetics[i].Pos.x, GameCosmetics[i].Pos.y, GameCosmetics[i].Size, GameCosmetics[i].Size, 90);
            }

            
        }
        if (TimerCosmeticHeartDecrease > 10)
        {
            TimerCosmeticHeartDecrease = 0;
        }
        // ������
        for (int i = 0; i < GameBonuses.size(); i++)
        {
            RenderTextureCentered(Textures[GameBonuses[i].TextureIndex], GameBonuses[i].Pos.x, GameBonuses[i].Pos.y, GameBonuses[i].Size, GameBonuses[i].Size, GameBonuses[i].Rotation);
            if (GameBonuses[i].Size == GameBonuses[i].FullSize)
            {
                RenderText(GameBonuses[i].Word.c_str(), NormalFont, GameBonuses[i].Pos.x, GameBonuses[i].Pos.y - GameBonuses[i].Size / 2 - 10, ColorDefaultBlue, true);
            }            
        }
        // ����������
        for (int i = 0; i < GameEnemies.size(); i++)
        {
            RenderTextureCentered(Textures[GameEnemies[i].TextureIndex], GameEnemies[i].Pos.x, GameEnemies[i].Pos.y, GameEnemies[i].Width, GameEnemies[i].Height, GameEnemies[i].Rotation);
            RenderText(GameEnemies[i].Word.c_str(), NormalFont, GameEnemies[i].Pos.x, GameEnemies[i].Pos.y - GameEnemies[i].Height / 2, ColorDefaultBlue, true);
        }
        // ��������
        if (GamePlayerHearts.size() == 0)
        {
            HeartbeatRate = 25;
        }
        else if (GamePlayerHearts.size() == 1)
        {
            HeartbeatRate = 50;
        }
        else
        {
            HeartbeatRate = 100;
        }
        if (MainPlayer.IsDamaged == true)
        {
            RenderTextureCentered(Textures[GIMG_SPRITES_PLAYER_DAMAGED], MainPlayer.Pos.x, MainPlayer.Pos.y, MainPlayer.Width * 0.9, MainPlayer.Height * 0.9, MainPlayer.Rotation);            
        }
        else if (TimerHeartbeat > HeartbeatRate)
        {
            if (MainPlayer.IsDamaged == true)
            {
                RenderTextureCentered(Textures[GIMG_SPRITES_PLAYER_DAMAGED], MainPlayer.Pos.x, MainPlayer.Pos.y, MainPlayer.Width * 1.2, MainPlayer.Height * 1.2, MainPlayer.Rotation);
            }
            else
            {
                RenderTextureCentered(Textures[GIMG_SPRITES_PLAYER], MainPlayer.Pos.x, MainPlayer.Pos.y, MainPlayer.Width * 1.2, MainPlayer.Height * 1.2, MainPlayer.Rotation);
            }            
        }
        else
        {
            RenderTextureCentered(Textures[GIMG_SPRITES_PLAYER], MainPlayer.Pos.x, MainPlayer.Pos.y, MainPlayer.Width, MainPlayer.Height, MainPlayer.Rotation);
        }
        if (TimerHeartDamaged > 5)
        {
            if (MainPlayer.IsDamaged == true)
            {
                TimerHeartbeat = 0;
            }            
            MainPlayer.IsDamaged = false;
            
        }
        if (TimerHeartbeat > HeartbeatRate + 10)
        {
            TimerHeartbeat = 0;            
        }        
        
        // ������
        for (int i = 0; i < GamePlayerHearts.size(); i++)
        {
            RenderTextureCentered(Textures[GIMG_SPRITES_HEART], GamePlayerHearts[i].x, GamePlayerHearts[i].y, 32, 32, 90);
        }        
        // �������� �����    
        RenderText(WordInput.c_str(), NormalFont, SCREENPOS_X_CENTERED, SCREENPOS_Y_CENTERED/4, ColorDefaultBlue, true);
        char ScoreStrTemp[12];
        _itoa_s(MainPlayer.Score, ScoreStrTemp, 12, 10);
        RenderText(ScoreStrTemp, NormalFont, SCREENPOS_X_CENTERED, TRUE_RESOLUTION_Y - 50, ColorDefaultBlue, true);
        if (PlayerDead)
        {
            std::string Temp;
            char ScoreStrTemp[12];
            _itoa_s(MainPlayer.Score, ScoreStrTemp, 12, 10);
            Temp = "Your Score: ";
            Temp += ScoreStrTemp;
            //�����
            RenderText("Maybe next time!", MenuFont, SCREENPOS_X_CENTERED, SCREENPOS_Y_CENTERED - SCREENPOS_Y_CENTERED / 2, ColorDefaultBlue, true);
            // ������
            RenderText(Temp.c_str(), MenuFont, SCREENPOS_X_CENTERED, SCREENPOS_Y_CENTERED - SCREENPOS_Y_CENTERED / 4, ColorDefaultBlue, true);            
            // ������
            DrawButton(BTN_DEAD_RETRY, 5);
            DrawButton(BTN_DEAD_QUIT_MAINMENU, 5);
        }
    }
    // ���, ���� �������
    if (FPSCounter) {
        RenderText(FPSString, NormalFont, 0, 0, 0, 0, 0, 255, false);
    } 

    // ���� ������� FPS �������, ���������� FPS
    if (FPSCounter == true && TickCurrent - TicksToSecond_FPS >= 1000)
    {
        TicksToSecond_FPS = TickCurrent;
        _itoa_s(FramesPerSecondPresent, FPSString, 10);
        FramesPerSecondPresent = 0;
    }    
    // ������
    if (GamePaused && !HighscoresEnterShow)
    {
        RenderTexture(Textures[GIMG_INTERFACE_CURSOR], MousePosWindow.x, MousePosWindow.y);
    }
    
}