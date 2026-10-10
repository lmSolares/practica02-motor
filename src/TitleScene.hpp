#pragma once

#include "SceneManager.hpp"
#include "Scene.hpp"
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_scancode.h>
#include <string>

class GameScene;
class TitleScene;

class TitleScene : public Scene {

    public :

        TitleScene(SceneManager *m_manager) : Scene(m_manager, "Title Scene") {}

        void Render(SDL_Renderer *renderer) override
        {
            // Fondo
            SDL_SetRenderDrawColor(renderer, 20, 25, 45, 255);
            SDL_RenderClear(renderer);

            int width, height;
            SDL_GetWindowSize(SDL_GetRenderWindow(renderer), &width, &height);

            // Título
            SDL_SetRenderDrawColor(renderer, 0, 255, 190, 255);
            SDL_FRect rectCenter;
            rectCenter.w = 400.0f;
            rectCenter.h = 110.0f;
            rectCenter.x = (width - rectCenter.w) / 2.0f;
            rectCenter.y = (height - rectCenter.h) / 2.0f;
            SDL_RenderFillRect(renderer, &rectCenter);

            // Botón
            SDL_SetRenderDrawColor(renderer, 50, 200, 120, 255);
            SDL_FRect rectButton;
            rectButton.w = 200.0f;
            rectButton.h = 50.0f;
            rectButton.x = (width - rectButton.w) / 2.0f;
            rectButton.y = height - 100.0f;
            SDL_RenderFillRect(renderer, &rectButton);
        }

        void HandleEvent(const SDL_Event &event) override;

};
