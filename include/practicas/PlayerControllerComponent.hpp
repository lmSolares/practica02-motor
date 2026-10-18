#pragma once
#include "motor/Component.hpp"
#include "motor/GameObject.hpp"

class PlayerControllerComponent : public Component {
public:
  float speed{300.0f};
  bool follow_mouse{true};
  PlayerControllerComponent() = default;
  explicit PlayerControllerComponent(float spd, bool mouse_follow = true)
      : speed(spd), follow_mouse(mouse_follow) {}

  void FixedUpdate(float dt) override;
  void OnCollision(GameObject *other) override;
};
