#include "engine/components/AnimationComponent.hpp"
#include "engine/GameObject.hpp"
#include "engine/components/SpriteComponent.hpp"

void AnimationComponent::Init() {
  if (owner) {
    m_sprite = owner->GetComponent<SpriteComponent>();
  }

  if (m_sprite) {
    UpdateSrcRect();
  }
}

void AnimationComponent::AddClip(const std::string &name, int row,
                                 int totalFrames, float frameDuration,
                                 bool loop, int startFrame) {

  AnimationClip clip;
  clip.name = name;
  clip.row = row;
  clip.totalFrames = totalFrames;
  clip.frameDuration = frameDuration;
  clip.loop = loop;
  clip.startFrame = startFrame;

  m_clips[name] = clip;

  if (m_clips.size() == 1) {
    Play(name);
  }
}

bool AnimationComponent::Play(const std::string &name) {
  if (!m_clips.contains(name))
    return false;
  if (m_currentClip == name && m_isPlaying)
    return true;

  m_currentClip = name;
  m_currentFrameIndex = 0;
  m_elapsedTime = 0.0f;
  m_isPlaying = true;

  UpdateSrcRect();
  return true;
}

void AnimationComponent::Update(float dt) {
  if (!m_isPlaying || m_currentClip.empty())
    return;

  m_elapsedTime += dt;
  AnimationClip clip = m_clips[m_currentClip];

  while (m_elapsedTime >= clip.frameDuration) {
    m_elapsedTime -= clip.frameDuration;
    m_currentFrameIndex++;
    if (m_currentFrameIndex >= clip.totalFrames) {
      if (clip.loop) {
        m_currentFrameIndex %= clip.totalFrames;
      } else {
        m_currentFrameIndex = clip.totalFrames - 1;
        m_isPlaying = false;
      }
    }
    UpdateSrcRect();
  }
}

void AnimationComponent::UpdateSrcRect() {
  // Prevenir acceso a memoria nula si no hay sprite o clip
  if (!m_sprite || m_currentClip.empty() || !m_clips.contains(m_currentClip)) {
    return;
  }

  AnimationClip clip = m_clips[m_currentClip];

  int col = clip.startFrame + m_currentFrameIndex;
  int row = clip.row;

  SDL_FRect rect;
  rect.x = static_cast<float>(col * m_frameWidth);
  rect.y = static_cast<float>(row * m_frameHeight);
  rect.w = static_cast<float>(m_frameWidth);
  rect.h = static_cast<float>(m_frameHeight);

  m_sprite->m_srcRect = rect;
  m_sprite->m_useSrcRect = true;
}

AnimationComponent::AnimationComponent(int frameWidth, int frameHeight)
    : m_frameWidth(frameWidth), m_frameHeight(frameHeight) {}

void AnimationComponent::Stop() { m_isPlaying = false; }

void AnimationComponent::Resume() {
  if (!m_currentClip.empty()) {
    m_isPlaying = true;
  }
}
