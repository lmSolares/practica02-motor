#pragma once
#include "engine/Component.hpp"
#include <SDL3/SDL.h>

class SpriteComponent : public Component {
public:
  SDL_Texture *m_texture{nullptr};
  float m_width{0.0f};
  float m_height{0.0f};
  bool m_useSrcRect{false};
  SDL_FRect m_srcRect{0.0f, 0.0f, 0.0f, 0.0f};
  SDL_FColor m_colorMod{1.0f, 1.0f, 1.0f, 1.0f};
  SDL_FlipMode m_flip{SDL_FLIP_NONE};

  SpriteComponent() = default;
  explicit SpriteComponent(SDL_Texture *texture);

  void Render(SDL_Renderer *renderer);
};
