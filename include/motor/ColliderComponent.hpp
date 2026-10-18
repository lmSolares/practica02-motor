#pragma once
#include "Component.hpp"
#include "Vector2.hpp"

class ColliderComponent : public Component {
public:
  Vector2 offset{0.0f, 0.0f};
  Vector2 size{60.0f, 60.0f};
  bool is_trigger{false};
  bool is_colliding{false};

  ColliderComponent() = default;

  SDL_FRect GetWorldBounds() const;
  void RenderDebug(SDL_Renderer *renderer);
};
