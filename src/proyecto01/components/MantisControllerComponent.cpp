#include "proyecto01/components/MantisControllerComponent.hpp"
#include "motor/TransformComponent.hpp"
#include "motor/Vector2.hpp"
#include <cstdlib>

void MantisControllerComponent::SetKnight(GameObject *knight) {
  this->knight = knight;
}

void MantisControllerComponent::AttackPosition() {
  float knight_pos_x = knight->GetComponent<TransformComponent>()->position.x;
  Vector2 new_pos{0.0f, 0.0f};
  switch (attack) {
  case Attack::Suelo:
    if (knight_pos_x < 480) {
      facing_dir = -1;
      new_pos.x = 748.0f;
      new_pos.y = 462.0f;
    } else {
      facing_dir = 1;
      new_pos.x = 180.0f;
      new_pos.y = 462.0f;
    }
    break;
  case Attack::AtaqueCaida:
    new_pos.x = knight_pos_x;
    new_pos.y = 250.0f;
    break;
  case Attack::Proyectil:
    if (knight_pos_x < 480) {
      facing_dir = -1;
      new_pos.x = 888.0f;
      new_pos.y = 300.0f;
    } else {
      facing_dir = 1;
      new_pos.x = 40.0f;
      new_pos.y = 300.0f;
    }
    break;
  }

  owner->GetComponent<TransformComponent>()->position = new_pos;
}

void MantisControllerComponent::ExecuteAttack(float fixed_dt) {
  TransformComponent *transform = owner->GetComponent<TransformComponent>();
  if (!transform)
    return;

  Vector2 velocity{0.0f, 0.0f};

  switch (attack) {
  case Attack::Suelo:
    velocity.x = 900.0f * facing_dir;
    break;
  case Attack::AtaqueCaida:
    velocity.y = 700.0f;
    break;
  case Attack::Proyectil:
    state = AttackState::Recuperacion;
    state_timer = 0.5f;
    return;
  }

  Vector2 displacement = velocity * fixed_dt;
  transform->Translate(displacement);

  float x = transform->position.x;
  float y = transform->position.y;

  if (attack == Attack::Suelo) {
    if (facing_dir == -1 && x <= 180.0f) {
      transform->position.x = 180.0f;
      state = AttackState::Recuperacion;
      state_timer = 0.5f;
    } else if (facing_dir == 1 && x >= 748.0f) {
      transform->position.x = 748.0f;
      state = AttackState::Recuperacion;
      state_timer = 0.5f;
    }
  } else if (attack == Attack::AtaqueCaida) {
    if (y >= 462.0f) {
      transform->position.y = 462.0f;
      state = AttackState::Recuperacion;
      state_timer = 0.5f;
    }
  }
}

void MantisControllerComponent::FixedUpdate(float dt) {
  switch (state) {
  case AttackState::Inactiva:
    state_timer -= dt;
    if (state_timer <= 0) {
      attack = static_cast<Attack>(rand() % 3);
      state = AttackState::Anticipacion;
      state_timer = 0.5f;
      AttackPosition();
    }
    break;
  case AttackState::Anticipacion:
    state_timer -= dt;
    if (state_timer <= 0)
      state = AttackState::Ejecucion;
    break;
  case AttackState::Ejecucion:
    ExecuteAttack(dt);
    break;
  case AttackState::Recuperacion:
    state_timer -= dt;
    if (state_timer <= 0) {
      state = AttackState::Inactiva;
      state_timer = 0.5f;
    }
    break;
  }
}
