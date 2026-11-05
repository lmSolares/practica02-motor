#include "engine/components/SpriteComponent.hpp"
#include "engine/Camera2D.hpp"
#include "engine/GameObject.hpp"
#include "engine/components/TransformComponent.hpp"

SpriteComponent::SpriteComponent(SDL_Texture *texture) : m_texture(texture) {
  if (m_texture) {
    SDL_GetTextureSize(m_texture, &m_width, &m_height);
  }
}

void SpriteComponent::Render(SDL_Renderer *renderer) {
  if (!renderer || !m_texture) {
    return;
  }

  SDL_FRect dstRect{0.0f, 0.0f, m_width, m_height};
  double rotation = 0.0;

  if (owner) {
    auto *transform = owner->GetComponent<TransformComponent>();
    if (transform) {
      dstRect.x = transform->position.x;
      dstRect.y = transform->position.y;
      dstRect.w = (m_useSrcRect ? m_srcRect.w : m_width) * transform->scale.x;
      dstRect.h = (m_useSrcRect ? m_srcRect.h : m_height) * transform->scale.y;
    }
  }

  if (m_affectedByCamera) {
    Camera2D *camera = Camera2D::GetMain();
    if (camera != nullptr) {

      if (m_parallaxFactor.x > 0.0f || m_parallaxFactor.y > 0.0f) {
        if (!camera->IsVisible(dstRect)) {
          return;
        }
      }
      dstRect = camera->ApplyToRect(dstRect, m_parallaxFactor);
    }
  }

  SDL_SetTextureColorModFloat(m_texture, m_colorMod.r, m_colorMod.g,
                              m_colorMod.b);
  SDL_SetTextureAlphaModFloat(m_texture, m_colorMod.a);

  const SDL_FRect *src = m_useSrcRect ? &m_srcRect : nullptr;

  SDL_RenderTextureRotated(renderer, m_texture, src, &dstRect, rotation,
                           nullptr, m_flip);

  SDL_SetTextureColorModFloat(m_texture, 1.0f, 1.0f, 1.0f);
  SDL_SetTextureAlphaModFloat(m_texture, 1.0f);
}
