#pragma once

#include "engine/Scene.hpp"
#include "engine/SceneManager.hpp"
#include "physics/CollisionManager.hpp"

class GameplayScene : public Scene {

private:
  CollisionManager m_collisionManager{nullptr};
  float m_physicsAccumulator{0.0f};
  bool m_debugDraw{false};

public:
  GameplayScene(SceneManager *m_manager) : Scene(m_manager, "Gameplay Scene") {}

  void Init() override;

  void FixedUpdate(float fixed_dt) override;

  void HandleEvent(const SDL_Event &event) override;

  void Render(SDL_Renderer *renderer) override;
};
