#pragma once
#include "../../include/motor/Component.hpp"
#include "../../include/motor/Vector2.hpp"
#include <SDL3/SDL.h>

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
