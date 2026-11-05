#pragma once
#include "engine/Component.hpp"
#include "math/Vector2.hpp"
#include <SDL3/SDL.h>

class SpriteComponent : public Component {
private:
  int m_layer{0};
  // Capa de ordenamiento (Z-Order)
  Vector2 m_parallaxFactor{1.0f, 1.0f};
  // Sensibilidad al movimiento de la cámara
  bool m_affectedByCamera{true};
  // Falso para elementos estáticos de UI
public:
  SDL_Texture *m_texture{nullptr};
  float m_width{0.0f};
  float m_height{0.0f};
  bool m_useSrcRect{false};
  SDL_FRect m_srcRect{0.0f, 0.0f, 0.0f, 0.0f};
  SDL_FColor m_colorMod{1.0f, 1.0f, 1.0f, 1.0f};
  SDL_FlipMode m_flip{SDL_FLIP_NONE};

  void SetLayer(int layer) { m_layer = layer; }
  int GetLayer() const { return m_layer; }
  void SetParallaxFactor(const Vector2 &factor) { m_parallaxFactor = factor; }
  const Vector2 &GetParallaxFactor() const { return m_parallaxFactor; }
  void SetAffectedByCamera(bool affected) { m_affectedByCamera = affected; }
  bool IsAffectedByCamera() const { return m_affectedByCamera; }

  SpriteComponent() = default;
  explicit SpriteComponent(SDL_Texture *texture);

  void Render(SDL_Renderer *renderer);
};
