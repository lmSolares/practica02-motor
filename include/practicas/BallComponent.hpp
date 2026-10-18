#pragma once
#include "../motor/Component.hpp"
#include "../motor/GameObject.hpp"
#include "../motor/Vector2.hpp"
#include <SDL3/SDL.h>

class BallComponent : public Component {
public:
  Vector2 velocity{220.0f, 180.0f};
  void FixedUpdate(float dt) override;
  void OnCollision(GameObject *other) override;
};
