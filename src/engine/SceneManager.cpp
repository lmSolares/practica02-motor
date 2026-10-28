#include "engine/SceneManager.hpp"
#include <utility>

void SceneManager::ChangeScene(std::unique_ptr<Scene> new_scene) {
  m_pendingAction = SceneAction::Change;
  m_pendingScene = std::move(new_scene);
}

void SceneManager::PushScene(std::unique_ptr<Scene> new_scene) {
  m_pendingAction = SceneAction::Push;
  m_pendingScene = std::move(new_scene);
}

void SceneManager::PopScene() { m_pendingAction = SceneAction::Pop; }

void SceneManager::Clear() { m_pendingAction = SceneAction::Clear; }

void SceneManager::ProcessPendingChanges() {
  switch (m_pendingAction) {
  case SceneAction::None:
    return;
  case SceneAction::Change:
    if (!m_scenes.empty()) {
      m_scenes.back()->Exit();
      m_scenes.pop_back();
    }
    if (m_pendingScene != nullptr) {
      m_scenes.push_back(std::move(m_pendingScene));
      m_scenes.back()->Init();
    }
    break;
  case SceneAction::Push:
    if (m_pendingScene != nullptr) {
      m_scenes.push_back(std::move(m_pendingScene));
      m_scenes.back()->Init();
    }
    break;
  case SceneAction::Pop:
    if (!m_scenes.empty()) {
      m_scenes.back()->Exit();
      m_scenes.pop_back();
    }
    break;
  case SceneAction::Clear:
    while (!m_scenes.empty()) {
      m_scenes.back()->Exit();
      m_scenes.pop_back();
    }
    break;
  }
  m_pendingAction = SceneAction::None;
  m_pendingScene.reset();
}

void SceneManager::HandleEvent(const SDL_Event &event) {
  if (!m_scenes.empty()) {
    m_scenes.back()->HandleEvent(event);
  }
}

void SceneManager::Update(float dt) {
  if (!m_scenes.empty()) {
    m_scenes.back()->Update(dt);
  }
}

void SceneManager::FixedUpdate(float fixed_dt) {
  if (!m_scenes.empty()) {
    m_scenes.back()->FixedUpdate(fixed_dt);
  }
}

void SceneManager::Render(SDL_Renderer *renderer) {
  for (auto &scene : m_scenes) {
    scene->Render(renderer);
  }
}

bool SceneManager::HasScenes() const { return !m_scenes.empty(); }
