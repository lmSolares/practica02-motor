#include "proyecto01/components/PixelArtComponent.hpp"
#include "engine/GameObject.hpp"
#include "engine/components/TransformComponent.hpp"

void PixelArtComponent::Render(SDL_Renderer *renderer) {
  if (!owner || pixels.empty())
    return;

  TransformComponent *transform = owner->GetComponent<TransformComponent>();
  if (!transform)
    return;

  float start_x = transform->position.x;
  float start_y = transform->position.y;

  for (size_t row = 0; row < pixels.size(); ++row) {
    for (size_t col = 0; col < pixels[row].length(); ++col) {
      char p = pixels[row][col];

      if (p == ' ' || p == '.')
        continue;

      if (p == 'K' || p == 'B') {
        SDL_SetRenderDrawColor(renderer, 26, 31, 34, 255);
      } else if (p == 'W') {
        SDL_SetRenderDrawColor(renderer, 250, 254, 255, 255);
      } else if (p == 'G') {
        SDL_SetRenderDrawColor(renderer, 176, 172, 184, 255);
      } else if (p == 'R') {
        SDL_SetRenderDrawColor(renderer, 220, 50, 50, 255);
      } else if (p == 'D') {
        SDL_SetRenderDrawColor(renderer, 80, 80, 80, 255);
      } else {
        SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
      }

      SDL_FRect rect{start_x + (col * pixel_size * transform->scale.x),
                     start_y + (row * pixel_size * transform->scale.y),
                     pixel_size * transform->scale.x,
                     pixel_size * transform->scale.y};

      SDL_RenderFillRect(renderer, &rect);
    }
  }
}
