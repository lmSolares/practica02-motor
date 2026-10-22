#pragma once

#include "motor/Component.hpp"
#include "motor/GameObject.hpp"

enum class Attack { Suelo, Proyectil, AtaqueCaida };
enum class AttackState { Inactiva, Anticipacion, Ejecucion, Recuperacion };
enum class AttackProyectilPos { Low, High };

class MantisControllerComponent : public Component {

public:
  float state_timer{0.5f};
  Attack attack;
  int facing_dir{1};
  AttackState state = AttackState::Inactiva;
  GameObject *knight;
  GameObject *boomerang;
  const float LOW_ATTACK{452.0f};
  const float HIGH_ATTACK{366.0f};

  void ExecuteAttack(float);
  void AttackPosition();
  void SetBoomerang(GameObject *boomerang);
  void SetKnight(GameObject *knight);
  void FixedUpdate(float) override;
};
