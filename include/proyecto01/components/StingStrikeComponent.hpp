#pragma once

#include "motor/Component.hpp"

class StingStrikeComponent : public Component {
public:
  GameObject *knight{nullptr};
  float active_timer = 0.12f;
  bool is_striking_down{false};

  void VerticalSting();
  void HorizontalSting();
  void SetKnight(GameObject *knight);
  void Update(float dt) override;
  void FixedUpdate(float dt) override;
  void OnCollision(GameObject *other) override;
};
