#pragma once
#include "../../motor/Scene.hpp"
#include "../../motor/SceneManager.hpp"

class TitleScene : public Scene {
public:
  TitleScene(SceneManager *m_manager) : Scene(m_manager, "Bug Knight") {}

  void Render(SDL_Renderer *renderer) override;
  void HandleEvent(const SDL_Event &event) override;
};
