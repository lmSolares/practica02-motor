#include "../../include/proyecto01/scenes/GameplayScene.hpp"
#include "../../include/proyecto01/scenes/GameOverScene.hpp"
#include "../../include/proyecto01/scenes/PauseScene.hpp"

void GameplayScene::Init() {
  m_entities.clear();
  m_collisionManager.SetEntities(&m_entities);
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
