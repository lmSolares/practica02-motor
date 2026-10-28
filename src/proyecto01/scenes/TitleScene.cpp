#include "proyecto01/scenes/TitleScene.hpp"
#include "engine/GameObject.hpp"
#include "engine/components/TransformComponent.hpp"
#include "proyecto01/components/TextRenderComponent.hpp"
#include "proyecto01/scenes/GameplayScene.hpp"

void TitleScene::Init() {
  m_entities.clear();

  GameObject *title = CreateGameObject("Title");
  title->AddComponent<TransformComponent>(Vector2{260.0f, 180.0f});
  title->AddComponent<TextRenderComponent>("BUG KNIGHT", 10.0f,
                                           SDL_Color{0, 255, 190, 255});

  GameObject *subtitle = CreateGameObject("Subtitle");
  subtitle->AddComponent<TransformComponent>(Vector2{178.0f, 380.0f});
  subtitle->AddComponent<TextRenderComponent>("PRESIONA ESPACIO O ENTER", 6.0f,
                                              SDL_Color{250, 254, 255, 255});
}

void TitleScene::Render(SDL_Renderer *renderer) {
  SDL_SetRenderDrawColor(renderer, 20, 25, 45, 255);
  SDL_RenderClear(renderer);

  for (auto &entity : m_entities) {
    entity->Render(renderer);
  }
}

void TitleScene::HandleEvent(const SDL_Event &event) {
  if (event.type == SDL_EVENT_KEY_DOWN) {
    if (event.key.scancode == SDL_SCANCODE_SPACE ||
        event.key.scancode == SDL_SCANCODE_RETURN) {
      m_manager->ChangeScene(std::make_unique<GameplayScene>(m_manager));
    }
  }
}
