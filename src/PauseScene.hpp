#pragma once

#include "Scene.hpp"
#include "SceneManager.hpp"
#include <SDL3/SDL_blendmode.h>
#include <SDL3/SDL_render.h>

class PauseScene : public Scene
{
    public:
        PauseScene(SceneManager *m_manager) : Scene(m_manager, "Pause Scene") {}

        void HandleEvent(const SDL_Event &event) override
        {
            if(event.type == SDL_EVENT_KEY_DOWN)
            {
                if(event.key.scancode == SDL_SCANCODE_P || event.key.scancode == SDL_SCANCODE_ESCAPE)
                {
                    m_manager->PopScene();
                }
            }
        }

        void Render(SDL_Renderer *renderer) override
        {
            // Opacar el GameScene
            SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 175);
            SDL_FRect screen_overlay{0.0f, 0.0f, 960.0f, 540.0f};
            SDL_RenderFillRect(renderer, &screen_overlay);

            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

            // Icono pausa
            float bar_width = 30.0f;
            float bar_height = 100.0f;
            float spacing = 30.0f;

            SDL_FRect bar_left;
            bar_left.w = bar_width;
            bar_left.h = bar_height;
            bar_left.x = 480.0f - (spacing / 2.0f) - bar_width;
            bar_left.y = 270.0f - (bar_height / 2.0f);

            SDL_FRect bar_right;
            bar_right.w = bar_width;
            bar_right.h = bar_height;
            bar_right.x = 480.0f + (spacing / 2.0f);
            bar_right.y = 270.0f - (bar_height / 2.0f);

            SDL_RenderFillRect(renderer, &bar_left);
            SDL_RenderFillRect(renderer, &bar_right);

            SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
        }

};
