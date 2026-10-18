#pragma once

#include "../motor/Scene.hpp"
#include "../motor/SceneManager.hpp"
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_scancode.h>

class GameOverScene : public Scene {

public:
  GameOverScene(SceneManager *m_manager)
      : Scene(m_manager, "Game Over Scene") {}

  void Render(SDL_Renderer *renderer) override;

  void HandleEvent(const SDL_Event &event) override;
};
