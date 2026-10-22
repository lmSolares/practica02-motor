#include "proyecto01/scenes/GameOverScene.hpp"
#include "motor/GameObject.hpp"
#include "motor/TransformComponent.hpp"
#include "proyecto01/components/TextRenderComponent.hpp"
#include "proyecto01/scenes/GameplayScene.hpp"
#include "proyecto01/scenes/TitleScene.hpp"

void GameOverScene::Init() {
  m_entities.clear();

  GameObject *gameOver = CreateGameObject("Game Over Scene");
  gameOver->AddComponent<TransformComponent>(Vector2{310.0f, 180.0f});
  gameOver->AddComponent<TextRenderComponent>("PERDISTE", 10.0f,
                                              SDL_Color{0, 255, 190, 255});

  GameObject *subtitle = CreateGameObject("Subtitle");
  subtitle->AddComponent<TransformComponent>(Vector2{170.0f, 380.0f});
  subtitle->AddComponent<TextRenderComponent>(
      "PRESIONA R PARA REINTENTAR", 6.0f, SDL_Color{250, 254, 255, 255});
  GameObject *subtitle2 = CreateGameObject("Subtitle");
  subtitle2->AddComponent<TransformComponent>(Vector2{180.0f, 430.0f});
  subtitle2->AddComponent<TextRenderComponent>(
      "O M PARA REGRESAR AL MENU", 6.0f, SDL_Color{250, 254, 255, 255});
}

void GameOverScene::Render(SDL_Renderer *renderer) {
  SDL_SetRenderDrawColor(renderer, 20, 25, 45, 255);
  SDL_RenderClear(renderer);

  for (auto &entity : m_entities) {
    entity->Render(renderer);
  }
}

void GameOverScene::HandleEvent(const SDL_Event &event) {
  if (event.type == SDL_EVENT_KEY_DOWN) {
    if (event.key.scancode == SDL_SCANCODE_R) {
      m_manager->ChangeScene(std::make_unique<GameplayScene>(m_manager));
    }
    if (event.key.scancode == SDL_SCANCODE_M) {
      m_manager->ChangeScene(std::make_unique<TitleScene>(m_manager));
    }
  }
}
