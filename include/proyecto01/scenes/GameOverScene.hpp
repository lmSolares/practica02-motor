#pragma once

#include "engine/Scene.hpp"
#include "engine/SceneManager.hpp"

class GameOverScene : public Scene {

public:
  GameOverScene(SceneManager *m_manager)
      : Scene(m_manager, "Game Over Scene") {}

  void Init() override;
  void Render(SDL_Renderer *renderer) override;

  void HandleEvent(const SDL_Event &event) override;
};
