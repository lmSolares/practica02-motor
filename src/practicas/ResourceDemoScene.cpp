#include "practicas/ResourceDemoScene.hpp"
#include "engine/components/SpriteComponent.hpp"
#include "engine/components/TransformComponent.hpp"
#include <SDL3_image/SDL_image.h>

void ResourceDemoScene::LoadEntities() {
  SDL_Texture *bgTex = m_resourceManager.GetTexture("assets/background.png");
  GameObject *bg = CreateGameObject("Background");
  bg->AddComponent<TransformComponent>(Vector2{0.0f, 0.0f});
  bg->AddComponent<SpriteComponent>(bgTex);

  SDL_Texture *playerTex = m_resourceManager.GetTexture("assets/player.png");
  GameObject *player = CreateGameObject("Player");
  player->AddComponent<TransformComponent>(Vector2{464.0f, 480.0f});
  player->AddComponent<SpriteComponent>(playerTex);

  for (int i = 0; i < 5; ++i) {
    SpawnEnemyRow();
  }

  SDL_Log("[Flyweight Metric] Entidades en escena: %zu", m_entities.size());
  SDL_Log("[Flyweight Metric] Texturas en VRAM: %zu",
          m_resourceManager.GetTextureCount());
}

void ResourceDemoScene::SpawnEnemyRow() {
  SDL_Texture *enemyTex = m_resourceManager.GetTexture("assets/enemy.png");
  float startY = 50.0f + ((float)(m_entities.size() - 2) / 10) * 40.0f;
  for (int i = 0; i < 10; ++i) {
    GameObject *enemy = CreateGameObject("Enemy");
    enemy->AddComponent<TransformComponent>(
        Vector2{180.0f + i * 60.0f, startY});
    enemy->AddComponent<SpriteComponent>(enemyTex);
  }
}

void ResourceDemoScene::Update(float dt) {
  if (!m_initialized)
    return;

  const bool *keys = SDL_GetKeyboardState(nullptr);
  for (auto &entity : m_entities) {
    if (entity->GetTag() == "Player") {
      auto *transform = entity->GetComponent<TransformComponent>();
      if (keys[SDL_SCANCODE_A] || keys[SDL_SCANCODE_LEFT])
        transform->position.x -= 300.0f * dt;
      if (keys[SDL_SCANCODE_D] || keys[SDL_SCANCODE_RIGHT])
        transform->position.x += 300.0f * dt;
      if (keys[SDL_SCANCODE_W] || keys[SDL_SCANCODE_UP])
        transform->position.y -= 300.0f * dt;
      if (keys[SDL_SCANCODE_S] || keys[SDL_SCANCODE_DOWN])
        transform->position.y += 300.0f * dt;
    }
  }
  Scene::Update(dt);
}

void ResourceDemoScene::Render(SDL_Renderer *renderer) {
  if (!m_initialized) {
    m_resourceManager.SetRenderer(renderer);
    LoadEntities();
    m_initialized = true;
  }
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);
  for (auto &entity : m_entities) {
    entity->Render(renderer);
  }
}

void ResourceDemoScene::HandleEvent(const SDL_Event &event) {
  if (event.type == SDL_EVENT_KEY_DOWN) {
    if (event.key.scancode == SDL_SCANCODE_SPACE) {
      SpawnEnemyRow();
      SDL_Log("Enemigos añadidos. Total texturas: %zu",
              m_resourceManager.GetTextureCount());
    } else if (event.key.scancode == SDL_SCANCODE_C) {
      m_resourceManager.Clear();
      SDL_Log("Caché vaciada.");
    } else if (event.key.scancode == SDL_SCANCODE_L) {
      TriggerDeliberateLeak();
    } else if (event.key.scancode == SDL_SCANCODE_ESCAPE) {
      SDL_Event quitEvent;
      quitEvent.type = SDL_EVENT_QUIT;
      SDL_PushEvent(&quitEvent);
    }
  }
}

void ResourceDemoScene::TriggerDeliberateLeak() {
  for (int i = 0; i < 50; ++i) {
    IMG_Load("assets/enemy.png");
  }
  SDL_Log("Fuga de memoria de 50 superficies activada.");
}

void ResourceDemoScene::Exit() {
  m_resourceManager.Clear();
  m_entities.clear();
}
