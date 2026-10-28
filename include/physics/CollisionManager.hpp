#pragma once
#include <SDL3/SDL.h>
#include <memory>
#include <vector>

class GameObject;
class ColliderComponent;

class CollisionManager {
private:
  std::vector<std::unique_ptr<GameObject>> *m_entities{nullptr};

public:
  explicit CollisionManager(std::vector<std::unique_ptr<GameObject>> *entities);

  bool CheckAABB(const SDL_FRect &a, const SDL_FRect &b) const;
  bool CheckCollision(const ColliderComponent &a,
                      const ColliderComponent &b) const;
  void SetEntities(std::vector<std::unique_ptr<GameObject>> *entities);
  void CheckCollisions();
};
