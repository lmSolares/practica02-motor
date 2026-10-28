#pragma once

#include "engine/Scene.hpp"
#include "engine/SceneManager.hpp"

class TitleScene : public Scene {
public:
  TitleScene(SceneManager *m_manager) : Scene(m_manager, "Bug Knight") {}

  void Init() override;
  void Render(SDL_Renderer *renderer) override;
  void HandleEvent(const SDL_Event &event) override;
};
