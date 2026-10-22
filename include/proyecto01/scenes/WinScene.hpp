#pragma once

#include "motor/Scene.hpp"
#include "motor/SceneManager.hpp"

class WinScene : public Scene {
public:
  WinScene(SceneManager *m_manager) : Scene(m_manager, "Win Scene") {}

  void Init() override;
  void Render(SDL_Renderer *renderer) override;
  void HandleEvent(const SDL_Event &event) override;
};
