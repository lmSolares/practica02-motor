#include "engine/Camera2D.hpp"
#include "math/Vector2.hpp"
#include <algorithm>

Camera2D::Camera2D(float viewportW, float viewportH) {
  m_viewportSize = Vector2{viewportW, viewportH};
  if (s_mainCamera == nullptr)
    s_mainCamera = this;
}

Camera2D::Camera2D() {
  if (s_mainCamera == nullptr)
    s_mainCamera = this;
}

Camera2D::~Camera2D() {
  if (s_mainCamera == this)
    s_mainCamera = nullptr;
}

void Camera2D::SetPosition(const Vector2 &pos) {
  m_position = pos;

  if (m_useBounds) {
    m_position.x = std::clamp(m_position.x, m_minBounds.x,
                              m_maxBounds.x - m_viewportSize.x);
    m_position.y = std::clamp(m_position.y, m_minBounds.y,
                              m_maxBounds.y - m_viewportSize.y);
  }
}

void Camera2D::CenterOn(const Vector2 &targetPos) {
  Vector2 result = targetPos - m_viewportSize * 0.5f;
  SetPosition(result);
}

void Camera2D::Follow(const Vector2 &targetPos, float smoothSpeed, float dt) {
  Vector2 targetPosCentrada = targetPos - (m_viewportSize * 0.5f);
  Vector2 nuevaPos =
      Vector2::Lerp(m_position, targetPosCentrada, smoothSpeed * dt);
  SetPosition(nuevaPos);
}

SDL_FRect Camera2D::ApplyToRect(const SDL_FRect &worldRect,
                                const Vector2 &parallaxFactor) const {

  SDL_FRect newRect;
  newRect.x = worldRect.x - (m_position.x * parallaxFactor.x);
  newRect.y = worldRect.y - (m_position.y * parallaxFactor.y);
  newRect.w = worldRect.w;
  newRect.h = worldRect.h;

  return newRect;
}

bool Camera2D::IsVisible(const SDL_FRect &worldRect) const {
  SDL_FRect camRect;
  camRect.x = m_position.x;
  camRect.y = m_position.y;
  camRect.w = m_viewportSize.x;
  camRect.h = m_viewportSize.y;

  return (worldRect.x + worldRect.w >= camRect.x &&
          worldRect.x <= camRect.x + camRect.w &&
          worldRect.y + worldRect.h >= camRect.y &&
          worldRect.y <= camRect.y + camRect.h);
}

void Camera2D::SetBounds(const Vector2 &minBounds, const Vector2 &maxBounds) {
  this->m_minBounds = minBounds;
  this->m_maxBounds = maxBounds;
  this->m_useBounds = true;
}

Vector2 Camera2D::WorldToScreen(const Vector2 &worldPos) const {
  return worldPos - m_position;
}

Vector2 Camera2D::ScreenToWorld(const Vector2 &screenPos) const {
  return screenPos + m_position;
}
