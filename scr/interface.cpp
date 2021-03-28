#include "main.h"

PauseMenuCode PauseMenu()
{
    Uint32 TicksToNextFrame = SDL_GetTicks();
    Uint32 TickCurrent = SDL_GetTicks();

    while (true)
    {
        // „тобы игра слишком часто не обновл€лась
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
            else if (KeyCode == InputCode::PAUSE_RESTART || MouseCode == InputCode::PAUSE_RESTART)
            {
                return PauseMenuCode::RESTART;
            }
            else if (KeyCode == InputCode::PAUSE_TO_DESKTOP || MouseCode == InputCode::PAUSE_TO_DESKTOP)
            {
                return PauseMenuCode::TO_DESKTOP;
            }
            else if (KeyCode == InputCode::PAUSE_TO_MAIN_MENU || MouseCode == InputCode::PAUSE_TO_MAIN_MENU)
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
        // „тобы игра слишком часто не обновл€лась
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
        // „тобы игра слишком часто не обновл€лась
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

void MainMenu()
{
    Uint32 TicksToNextFrame = SDL_GetTicks();
    Uint32 TickCurrent = SDL_GetTicks();

    while (true)
    {
        // „тобы игра слишком часто не обновл€лась
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
        }
    }
}