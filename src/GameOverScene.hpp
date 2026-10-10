#pragma once

#include <SDL3/SDL_events.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_scancode.h>
#include "Scene.hpp"
#include "SceneManager.hpp"

class GameOverScene : public Scene {

    public:
        GameOverScene(SceneManager *m_manager) : Scene(m_manager, "Game Over Scene") {}

        void Render(SDL_Renderer *renderer) override
        {
            SDL_SetRenderDrawColor(renderer, 255, 27, 0, 255);
            SDL_RenderClear(renderer);

            int width, height;
            SDL_GetWindowSize(SDL_GetRenderWindow(renderer), &width, &height);
            float cx = width / 2.0f;

            SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
            SDL_FRect rectTitle;
            rectTitle.w = 400.0f;
            rectTitle.h = 100.0f;
            rectTitle.x = cx - (rectTitle.w / 2.0f);
            rectTitle.y = 120.0f;
            SDL_RenderFillRect(renderer, &rectTitle);

            SDL_SetRenderDrawColor(renderer, 240, 210, 60, 255);
            SDL_FRect rectRestart;
            rectRestart.w = 200.0f;
            rectRestart.h = 50.0f;
            rectRestart.x = cx - (rectRestart.w / 2.0f);
            rectRestart.y = 280.0f;
            SDL_RenderFillRect(renderer, &rectRestart);

            SDL_SetRenderDrawColor(renderer, 60, 120, 240, 255);
            SDL_FRect rectMenu;
            rectMenu.w = 200.0f;
            rectMenu.h = 50.0f;
            rectMenu.x = cx - (rectMenu.w / 2.0f);
            rectMenu.y = 360.0f;

            SDL_RenderFillRect(renderer, &rectMenu);
        }

        void HandleEvent(const SDL_Event &event) override;

};
