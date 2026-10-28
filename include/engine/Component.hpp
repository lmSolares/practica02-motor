#pragma once
#include <SDL3/SDL.h>

class GameObject;

class Component {
public:
  GameObject *owner{nullptr};

  virtual ~Component() = default;
  virtual void Init() {}
  virtual void Update(float) {}
  virtual void FixedUpdate(float) {}
  virtual void Render(SDL_Renderer *) {}
  virtual void OnCollision(GameObject *) {}
};
