#include "engine/components/RectRenderComponent.hpp"
#include "engine/GameObject.hpp"
#include "engine/components/TransformComponent.hpp"

RectRenderComponent::RectRenderComponent(Vector2 sz, SDL_Color col)
    : size(sz), color(col) {}

void RectRenderComponent::Render(SDL_Renderer *renderer) {
  if (!owner)
    return;

  TransformComponent *transform = owner->GetComponent<TransformComponent>();
  if (!transform)
    return;

  SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
  SDL_FRect rect{transform->position.x, transform->position.y,
                 size.x * transform->scale.x, size.y * transform->scale.y};
  SDL_RenderFillRect(renderer, &rect);
}
