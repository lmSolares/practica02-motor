#include "proyecto01/scenes/GameplayScene.hpp"
#include "motor/ColliderComponent.hpp"
#include "motor/GameObject.hpp"
#include "motor/RectRenderComponent.hpp"
#include "motor/TransformComponent.hpp"
#include "motor/Vector2.hpp"
#include "proyecto01/scenes/GameOverScene.hpp"
#include "proyecto01/scenes/PauseScene.hpp"
#include <SDL3/SDL_pixels.h>

void GameplayScene::Init() {
  m_entities.clear();
  m_collisionManager.SetEntities(&m_entities);

  /* Entorno */

  // Paredes
  GameObject *wallLeft = CreateGameObject("Wall");
  wallLeft->AddComponent<TransformComponent>(Vector2{0.0f, 0.0f});
  wallLeft->AddComponent<RectRenderComponent>(Vector2{40.0f, 540.0f},
                                              SDL_Color{26, 31, 34, 255});
  auto *obsCol = wallLeft->AddComponent<ColliderComponent>();
  obsCol->size = Vector2{40.0f, 540.0f};

  GameObject *wallRight = CreateGameObject("Wall");
  wallRight->AddComponent<TransformComponent>(Vector2{920.0f, 0.0f});
  wallRight->AddComponent<RectRenderComponent>(Vector2{40.0f, 540.0f},
                                               SDL_Color{26, 31, 34, 255});
  auto *obsCol2 = wallRight->AddComponent<ColliderComponent>();
  obsCol2->size = Vector2{40.0f, 540.0f};

  // Suelo
  GameObject *floor = CreateGameObject("Floor");
  floor->AddComponent<TransformComponent>(Vector2{180.0f, 510.0f});
  floor->AddComponent<RectRenderComponent>(Vector2{600.0f, 30.0f},
                                           SDL_Color{26, 31, 34, 255});
  auto *obsCol3 = floor->AddComponent<ColliderComponent>();
  obsCol3->size = Vector2{600.0f, 30.0f};

  // Pinchos
  GameObject *spikeLeft = CreateGameObject("Spike");
  spikeLeft->AddComponent<TransformComponent>(Vector2{40.0f, 520.0f});
  spikeLeft->AddComponent<RectRenderComponent>(Vector2{140.0f, 20.0f},
                                               SDL_Color{183, 200, 189, 255});
  auto *trigCol = spikeLeft->AddComponent<ColliderComponent>();
  trigCol->size = Vector2{140.0f, 20.0f};
  trigCol->is_trigger = true;

  GameObject *spikeRight = CreateGameObject("Spike");
  spikeRight->AddComponent<TransformComponent>(Vector2{780.0f, 520.0f});
  spikeRight->AddComponent<RectRenderComponent>(Vector2{140.0f, 20.0f},
                                                SDL_Color{183, 200, 189, 255});
  auto *trigCol1 = spikeRight->AddComponent<ColliderComponent>();
  trigCol1->size = Vector2{140.0f, 20.0f};
  trigCol1->is_trigger = true;
}

void GameplayScene::FixedUpdate(float fixed_dt) {
  for (auto &entity : m_entities) {
    entity->FixedUpdate(fixed_dt);
  }
  m_collisionManager.CheckCollisions();
}

void GameplayScene::HandleEvent(const SDL_Event &event) {
  if (event.type == SDL_EVENT_KEY_DOWN) {
    if (event.key.scancode == SDL_SCANCODE_F1)
      m_debugDraw = !m_debugDraw;
    if (event.key.scancode == SDL_SCANCODE_P ||
        event.key.scancode == SDL_SCANCODE_ESCAPE) {
      m_manager->PushScene(std::make_unique<PauseScene>(m_manager));
    }
    if (event.key.scancode == SDL_SCANCODE_G) {
      m_manager->ChangeScene(std::make_unique<GameOverScene>(m_manager));
    }
  }
}

void GameplayScene::Render(SDL_Renderer *renderer) {
  SDL_SetRenderDrawColor(renderer, 20, 50, 76, 255);
  SDL_RenderClear(renderer);

  for (auto &entity : m_entities)
    entity->Render(renderer);

  if (m_debugDraw) {
    for (auto &entity : m_entities) {
      if (auto *col = entity->GetComponent<ColliderComponent>())
        col->RenderDebug(renderer);
    }
  }
}
