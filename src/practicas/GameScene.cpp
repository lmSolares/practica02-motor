#include "practicas/GameScene.hpp"
#include "engine/components/ColliderComponent.hpp"
#include "engine/components/RectRenderComponent.hpp"
#include "engine/components/TransformComponent.hpp"
#include "practicas/BallComponent.hpp"
#include "practicas/GameOverScene.hpp"
#include "practicas/PauseScene.hpp"
#include "practicas/PlayerControllerComponent.hpp"

void GameScene::Init() {
  m_entities.clear();
  m_collisionManager.SetEntities(&m_entities);

  // Jugador
  GameObject *player = CreateGameObject("Player");
  player->AddComponent<TransformComponent>(Vector2{440.0f, 240.0f});
  player->AddComponent<RectRenderComponent>(Vector2{60.0f, 60.0f},
                                            SDL_Color{60, 180, 100, 255});
  player->AddComponent<PlayerControllerComponent>(300.0f, false);
  player->AddComponent<ColliderComponent>();

  // Obstáculo
  GameObject *obstacle = CreateGameObject("Obstacle");
  obstacle->AddComponent<TransformComponent>(Vector2{180.0f, 140.0f});
  obstacle->AddComponent<RectRenderComponent>(Vector2{80.0f, 80.0f},
                                              SDL_Color{220, 70, 70, 255});
  auto *obsCol = obstacle->AddComponent<ColliderComponent>();
  obsCol->size = Vector2{80.0f, 80.0f};

  // Pelota
  GameObject *ball = CreateGameObject("Ball");
  ball->AddComponent<TransformComponent>(Vector2{468.0f, 80.0f});
  ball->AddComponent<RectRenderComponent>(Vector2{24.0f, 24.0f},
                                          SDL_Color{240, 210, 60, 255});
  auto *ballCol = ball->AddComponent<ColliderComponent>();
  ballCol->size = Vector2{24.0f, 24.0f};
  ball->AddComponent<BallComponent>();
}

void GameScene::FixedUpdate(float fixed_dt) {
  for (auto &entity : m_entities) {
    entity->FixedUpdate(fixed_dt);
  }
  m_collisionManager.CheckCollisions();
}

void GameScene::HandleEvent(const SDL_Event &event) {
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

void GameScene::Render(SDL_Renderer *renderer) {
  SDL_SetRenderDrawColor(renderer, 25, 25, 30, 255);
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
