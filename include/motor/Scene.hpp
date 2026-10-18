#pragma once
#include "../../include/motor/GameObject.hpp"
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_render.h>
#include <memory>
#include <string>
#include <vector>

class SceneManager;

class Scene {
protected:
  SceneManager *m_manager{nullptr};
  std::vector<std::unique_ptr<GameObject>> m_entities;
  std::string m_name;

public:
  Scene(const Scene &) = delete;
  Scene &operator=(const Scene &) = delete;

  Scene(Scene &&) = default;
  Scene &operator=(Scene &&) = default;

  virtual ~Scene() = default;

  Scene(SceneManager *manager, std::string name);

  GameObject *CreateGameObject(std::string tag);
  virtual std::vector<std::unique_ptr<GameObject>> &GetEntities();

  virtual void Init() {}
  virtual void Exit() {}
  virtual void Update(float dt);
  virtual void FixedUpdate(float fixed_dt);
  virtual void HandleEvent(const SDL_Event &) {}
  virtual void Render(SDL_Renderer *renderer);
};
