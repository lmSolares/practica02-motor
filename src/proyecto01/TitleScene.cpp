#include "../../include/proyecto01/scenes/TitleScene.hpp"
#include "../../include/proyecto01/scenes/GameplayScene.hpp"

void TitleScene::Render(SDL_Renderer *renderer) {
  // Fondo
  SDL_SetRenderDrawColor(renderer, 20, 25, 45, 255);
  SDL_RenderClear(renderer);

  int width, height;
  SDL_GetWindowSize(SDL_GetRenderWindow(renderer), &width, &height);

  // Título
  SDL_SetRenderDrawColor(renderer, 0, 255, 190, 255);
  SDL_FRect rectCenter;
  rectCenter.w = 400.0f;
  rectCenter.h = 110.0f;
  rectCenter.x = (width - rectCenter.w) / 2.0f;
  rectCenter.y = (height - rectCenter.h) / 2.0f;
  SDL_RenderFillRect(renderer, &rectCenter);

  // Botón
  SDL_SetRenderDrawColor(renderer, 50, 200, 120, 255);
  SDL_FRect rectButton;
  rectButton.w = 200.0f;
  rectButton.h = 50.0f;
  rectButton.x = (width - rectButton.w) / 2.0f;
  rectButton.y = height - 100.0f;
  SDL_RenderFillRect(renderer, &rectButton);
}

void TitleScene::HandleEvent(const SDL_Event &event) {
  if (event.type == SDL_EVENT_KEY_DOWN) {
    if (event.key.scancode == SDL_SCANCODE_SPACE ||
        event.key.scancode == SDL_SCANCODE_RETURN) {
      m_manager->ChangeScene(std::make_unique<GameplayScene>(m_manager));
    }
  }
}
