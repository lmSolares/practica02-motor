#include "motor/ColliderComponent.hpp"
#include "motor/GameObject.hpp"
#include "motor/TransformComponent.hpp"

SDL_FRect ColliderComponent::GetWorldBounds() const {
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

void ColliderComponent::RenderDebug(SDL_Renderer *renderer) {
  SDL_FRect bounds = GetWorldBounds();

  if (is_colliding) {
    SDL_SetRenderDrawColor(renderer, 255, 50, 50, 255);
  } else {
    SDL_SetRenderDrawColor(renderer, 50, 255, 50, 255);
  }

  SDL_RenderRect(renderer, &bounds);
}
