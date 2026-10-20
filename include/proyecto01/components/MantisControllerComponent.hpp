#pragma once

#include "motor/Component.hpp"
#include "motor/GameObject.hpp"

enum class Attack { Suelo, Proyectil, AtaqueCaida };
enum class AttackState { Inactiva, Anticipacion, Ejecucion, Recuperacion };

class MantisControllerComponent : public Component {

public:
  float state_timer{0.5f};
  Attack attack;
  int facing_dir{1};
  AttackState state = AttackState::Inactiva;
  GameObject *knight;

  void ExecuteAttack(float);
  void AttackPosition();
  void SetKnight(GameObject *knight);
  void FixedUpdate(float) override;
};
