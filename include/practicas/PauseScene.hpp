#pragma once

#include "../motor/Scene.hpp"
#include "../motor/SceneManager.hpp"
#include <SDL3/SDL_blendmode.h>
#include <SDL3/SDL_render.h>

class PauseScene : public Scene {
public:
  PauseScene(SceneManager *m_manager) : Scene(m_manager, "Pause Scene") {}

  void HandleEvent(const SDL_Event &event) override;

  void Render(SDL_Renderer *renderer) override;
};
