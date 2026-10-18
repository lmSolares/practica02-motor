#pragma once

#include "motor/Component.hpp"
#include "motor/Vector2.hpp"

class KnightControllerComponent : public Component {
public:
  const float gravity = 1400.0f;
  const float jump_force = -580.0f;
  const float dash_speed = 700.0f;
  int facing_dir{1};
  int health{5};
  bool is_grounded{false};
  float speed{300.0f};
  Vector2 velocity{0.0f, 0.0f};
  float dash_cooldown{0.0f};
  float invulnerability_timer{0.0f};
  float attack_cooldown{0.0f};
  float dash_timer{0.0f};

  KnightControllerComponent() = default;
  explicit KnightControllerComponent(float spd) : speed(spd) {}

  void Update(float dt) override;
  void FixedUpdate(float dt) override;
  void OnCollision(GameObject *other) override;
};
