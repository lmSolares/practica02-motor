#include "engine/Scene.hpp"
#include "algorithm"
#include "engine/GameObject.hpp"
#include "engine/components/SpriteComponent.hpp"
#include <utility>
#include <vector>

Scene::Scene(SceneManager *manager, std::string name)
    : m_manager(manager), m_name(std::move(name)) {}

GameObject *Scene::CreateGameObject(std::string tag) {
  auto entity = std::make_unique<GameObject>(std::move(tag));
  GameObject *ptr = entity.get();
  m_entities.push_back(std::move(entity));
  return ptr;
}

std::vector<std::unique_ptr<GameObject>> &Scene::GetEntities() {
  return m_entities;
}

void Scene::Update(float dt) {
  for (auto &entity : m_entities) {
    entity->Update(dt);
  }
}

void Scene::FixedUpdate(float fixed_dt) {
  for (auto &entity : m_entities) {
    entity->FixedUpdate(fixed_dt);
  }
}

void Scene::Render(SDL_Renderer *renderer) {

  std::vector<GameObject *> renderQueue;
  renderQueue.reserve(m_entities.size());

  for (auto &entity : m_entities) {
    if (entity->IsActive()) {
      renderQueue.push_back(entity.get());
    }
  }

  std::stable_sort(renderQueue.begin(), renderQueue.end(),
                   [](const GameObject *a, const GameObject *b) {
                     int layerA = 0;
                     int layerB = 0;
                     if (auto *spriteA = a->GetComponent<SpriteComponent>())
                       layerA = spriteA->GetLayer();
                     if (auto *spriteB = b->GetComponent<SpriteComponent>())
                       layerB = spriteB->GetLayer();
                     return layerA < layerB;
                   });

  for (auto &entity : renderQueue) {
    entity->Render(renderer);
  }
}
