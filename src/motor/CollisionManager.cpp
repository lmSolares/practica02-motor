#include "../../include/motor/CollisionManager.hpp"
#include "../../include/motor/ColliderComponent.hpp"
#include "../../include/motor/GameObject.hpp"

CollisionManager::CollisionManager(
    std::vector<std::unique_ptr<GameObject>> *entities)
    : m_entities{entities} {}

bool CollisionManager::CheckAABB(const SDL_FRect &a, const SDL_FRect &b) const {
  return (a.x < b.x + b.w) && (a.x + a.w > b.x) && (a.y < b.y + b.h) &&
         (a.y + a.h > b.y);
}

bool CollisionManager::CheckCollision(const ColliderComponent &a,
                                      const ColliderComponent &b) const {
  return CheckAABB(a.GetWorldBounds(), b.GetWorldBounds());
}

void CollisionManager::SetEntities(
    std::vector<std::unique_ptr<GameObject>> *entities) {
  m_entities = entities;
}

void CollisionManager::CheckCollisions() {
  if (!m_entities)
    return;

  for (auto &entity : *m_entities) {
    if (auto *collider = entity->GetComponent<ColliderComponent>()) {
      collider->is_colliding = false;
    }
  }

  size_t n = m_entities->size();
  for (size_t i = 0; i < n; ++i) {
    if (!(*m_entities)[i]->IsActive())
      continue;
    auto *colA = (*m_entities)[i]->GetComponent<ColliderComponent>();
    if (!colA)
      continue;

    for (size_t j = i + 1; j < n; ++j) {
      if (!(*m_entities)[j]->IsActive())
        continue;
      auto *colB = (*m_entities)[j]->GetComponent<ColliderComponent>();
      if (!colB)
        continue;

      if (CheckCollision(*colA, *colB)) {
        colA->is_colliding = true;
        colB->is_colliding = true;

        (*m_entities)[i]->OnCollision((*m_entities)[j].get());
        (*m_entities)[j]->OnCollision((*m_entities)[i].get());
      }
    }
  }
}
