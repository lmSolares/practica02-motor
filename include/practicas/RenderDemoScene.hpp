#pragma once

#include "engine/Camera2D.hpp"
#include "engine/ResourceManager.hpp"
#include "engine/Scene.hpp"
#include "engine/components/AnimationComponent.hpp"
#include "engine/components/SpriteComponent.hpp"
#include "engine/components/TransformComponent.hpp"

class RenderDemoScene : public Scene {
private:
  ResourceManager m_resourceManager;
  Camera2D m_camera;
  bool m_initialized{false};
  TransformComponent *m_playerTransform{nullptr};
  SpriteComponent *m_playerSprite{nullptr};
  AnimationComponent *m_playerAnim{nullptr};

  void LoadEntities();

public:
  RenderDemoScene(SceneManager *manager) : Scene(manager, "Render Demo") {}
  void Update(float dt) override;
  void Render(SDL_Renderer *renderer) override;
  void Exit() override;
};
