#include "engine/Scene.hpp"
#include <utility>

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
  for (auto &entity : m_entities) {
    entity->Render(renderer);
  }
}
