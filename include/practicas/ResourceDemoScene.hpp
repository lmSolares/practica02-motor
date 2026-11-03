#pragma once
#include "engine/ResourceManager.hpp"
#include "engine/Scene.hpp"

class ResourceDemoScene : public Scene {
private:
  ResourceManager m_resourceManager;
  bool m_initialized{false};
  void LoadEntities();
  void SpawnEnemyRow();

public:
  ResourceDemoScene(SceneManager *manager) : Scene(manager, "Resource Demo") {}

  void Render(SDL_Renderer *renderer) override;
  void Update(float dt) override;
  void HandleEvent(const SDL_Event &event) override;
  void Exit() override;
  void TriggerDeliberateLeak();
};
