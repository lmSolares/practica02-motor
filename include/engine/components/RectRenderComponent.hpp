#pragma once

#include "engine/Component.hpp"
#include "math/Vector2.hpp"

class RectRenderComponent : public Component {
public:
  Vector2 size{60.0f, 60.0f};
  SDL_Color color{60, 180, 100, 255};

  RectRenderComponent() = default;
  RectRenderComponent(Vector2 sz, SDL_Color col);

  void Render(SDL_Renderer *renderer) override;
};
