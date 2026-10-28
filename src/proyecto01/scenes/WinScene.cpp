#include "proyecto01/scenes/WinScene.hpp"
#include "engine/GameObject.hpp"
#include "engine/components/TransformComponent.hpp"
#include "proyecto01/components/TextRenderComponent.hpp"
#include "proyecto01/scenes/TitleScene.hpp"

void WinScene::Init() {
  m_entities.clear();

  GameObject *winText = CreateGameObject("Win Title");
  winText->AddComponent<TransformComponent>(Vector2{310.0f, 180.0f});
  winText->AddComponent<TextRenderComponent>("VICTORIA", 10.0f,
                                             SDL_Color{240, 210, 60, 255});

  GameObject *subtitle = CreateGameObject("Subtitle");
  subtitle->AddComponent<TransformComponent>(Vector2{200.0f, 380.0f});
  subtitle->AddComponent<TextRenderComponent>("PRESIONA M PARA MENU", 6.0f,
                                              SDL_Color{250, 254, 255, 255});
}

void WinScene::Render(SDL_Renderer *renderer) {
  SDL_SetRenderDrawColor(renderer, 20, 45, 25, 255);
  SDL_RenderClear(renderer);

  for (auto &entity : m_entities) {
    entity->Render(renderer);
  }
}

void WinScene::HandleEvent(const SDL_Event &event) {
  if (event.type == SDL_EVENT_KEY_DOWN) {
    if (event.key.scancode == SDL_SCANCODE_M) {
      m_manager->ChangeScene(std::make_unique<TitleScene>(m_manager));
    }
  }
}
