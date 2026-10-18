#pragma once

#include "motor/Scene.hpp"
#include "motor/SceneManager.hpp"

class GameScene;
class TitleScene;

class TitleScene : public Scene {

public:
  TitleScene(SceneManager *m_manager) : Scene(m_manager, "Title Scene") {}

  void Render(SDL_Renderer *renderer) override;

  void HandleEvent(const SDL_Event &event) override;
};
