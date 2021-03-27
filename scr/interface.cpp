#include "main.h"

PauseMenuCode PauseMenu()
{
    Uint32 TicksToNextFrame = SDL_GetTicks();
    Uint32 TickCurrent = SDL_GetTicks();

    while (true)
    {
        // ����� ���� ������� ����� �� �����������
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