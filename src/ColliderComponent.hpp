#pragma once

#include "Component.hpp"
#include "GameObject.hpp"
#include "TransformComponent.hpp"
#include "Vector2.hpp"
#include <SDL3/SDL.h>

class ColliderComponent : public Component {
public:
  Vector2 offset{0.0f, 0.0f};
  Vector2 size{60.0f, 60.0f};
  bool is_trigger{false};
  bool is_colliding{false};

  ColliderComponent() = default;

  SDL_FRect GetWorldBounds() const {
    if (!owner) {
      return SDL_FRect{offset.x, offset.y, size.x, size.y};
    }

    TransformComponent *transform = owner->GetComponent<TransformComponent>();
    if (!transform) {
      return SDL_FRect{offset.x, offset.y, size.x, size.y};
    }

    float X = transform->position.x + offset.x;
    float Y = transform->position.y + offset.y;
    float W = size.x * transform->scale.x;
    float H = size.y * transform->scale.y;

    return SDL_FRect{X, Y, W, H};
  }

  void RenderDebug(SDL_Renderer *renderer) {
    SDL_FRect bounds = GetWorldBounds();

    if (is_colliding) {
      SDL_SetRenderDrawColor(renderer, 255, 50, 50, 255);
    } else {
      SDL_SetRenderDrawColor(renderer, 50, 255, 50, 255);
    }

    SDL_RenderRect(renderer, &bounds);
  }
};
