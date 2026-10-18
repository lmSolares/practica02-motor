#pragma once

#include "motor/Scene.hpp"
#include "motor/SceneManager.hpp"

class GameOverScene : public Scene {

public:
  GameOverScene(SceneManager *m_manager)
      : Scene(m_manager, "Game Over Scene") {}

  void Render(SDL_Renderer *renderer) override;

  void HandleEvent(const SDL_Event &event) override;
};
