#pragma once
#include "engine/Component.hpp"
#include "engine/GameObject.hpp"
#include "math/Vector2.hpp"

class BallComponent : public Component {
public:
  Vector2 velocity{220.0f, 180.0f};
  void FixedUpdate(float dt) override;
  void OnCollision(GameObject *other) override;
};
