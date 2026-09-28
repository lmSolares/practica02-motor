#pragma once
#include "ColliderComponent.hpp"
#include "GameObject.hpp"
#include <SDL3/SDL.h>
#include <memory>
#include <vector>

class CollisionManager {
private:
  std::vector<std::unique_ptr<GameObject>> *m_entities;

public:
  explicit CollisionManager(std::vector<std::unique_ptr<GameObject>> *entities)
      : m_entities{entities} {}

  bool CheckAABB(const SDL_FRect &a, const SDL_FRect &b) {
    return (a.x < b.x + b.w) && (a.x + a.w > b.x) && (a.y < b.y + b.h) &&
           (a.y + a.h > b.y);
  }

  bool CheckCollision(const ColliderComponent &a, const ColliderComponent &b) {
    return CheckAABB(a.GetWorldBounds(), b.GetWorldBounds());
  }

  void CheckCollisions() {
    for (auto &entity : *m_entities) {
      if (auto *collider = entity->GetComponent<ColliderComponent>()) {
        collider->is_colliding = false;
      }
    }

    size_t n = m_entities->size();
    for (size_t i = 0; i < n; ++i) {
      auto *colA = (*m_entities)[i]->GetComponent<ColliderComponent>();
      if (!colA)
        continue;

      for (size_t j = i + 1; j < n; ++j) {
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
};
