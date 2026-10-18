#pragma once

#include "../motor/Scene.hpp"
#include "../motor/SceneManager.hpp"
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_scancode.h>
#include <string>

class GameScene;
class TitleScene;

class TitleScene : public Scene {

public:
  TitleScene(SceneManager *m_manager) : Scene(m_manager, "Title Scene") {}

  void Render(SDL_Renderer *renderer) override;

  void HandleEvent(const SDL_Event &event) override;
};
