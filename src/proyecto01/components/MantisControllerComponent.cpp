#include "proyecto01/components/MantisControllerComponent.hpp"
#include "motor/ColliderComponent.hpp"
#include "motor/TransformComponent.hpp"
#include "motor/Vector2.hpp"
#include "proyecto01/components/BoomerangComponent.hpp"
#include "proyecto01/scenes/WinScene.hpp"
#include <cstdlib>

void MantisControllerComponent::SetKnight(GameObject *knight) {
  this->knight = knight;
}

void MantisControllerComponent::SetBoomerang(GameObject *boomerang) {
  this->boomerang = boomerang;
}

void MantisControllerComponent::SetSceneManager(SceneManager *scene_manager) {
  this->scene_manager = scene_manager;
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
  case Attack::Proyectil: {

    AttackProyectilPos pos = static_cast<AttackProyectilPos>(rand() % 2);
    TransformComponent *boom_transform =
        boomerang->GetComponent<TransformComponent>();
    BoomerangComponent *boom_comp =
        boomerang->GetComponent<BoomerangComponent>();

    float target_x_start, target_x_end;
    float target_y_start, target_y_middle;

    if (knight_pos_x < 480) {
      facing_dir = -1;
      new_pos.x = 888.0f;
      target_x_start = 40.0f;
      target_x_end = 888.0f;
    } else {
      facing_dir = 1;
      new_pos.x = 40.0f;
      target_x_start = 880.0f;
      target_x_end = 40.0f;
    }

    if (pos == AttackProyectilPos::Low) {
      new_pos.y = LOW_ATTACK;
      target_y_start = LOW_ATTACK;
      target_y_middle = HIGH_ATTACK;
    } else {
      new_pos.y = HIGH_ATTACK;
      target_y_start = HIGH_ATTACK;
      target_y_middle = LOW_ATTACK;
    }

    boom_transform->position = new_pos;

    Vector2 p1{target_x_start, target_y_start};
    Vector2 p2{target_x_start, target_y_middle};
    Vector2 p3{target_x_end, target_y_middle};

    boom_comp->SetRoute(p1, p2, p3);
    break;
  }
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
  if (invulnerability_timer > 0.0f) {
    invulnerability_timer -= dt;
  }
  switch (state) {
  case AttackState::Inactiva:
    state_timer -= dt;
    if (state_timer <= 0) {
      if (boomerang->IsActive()) {
        int choice = rand() % 2;
        attack = (choice == 0) ? Attack::Suelo : Attack::AtaqueCaida;
      } else {
        attack = static_cast<Attack>(rand() % 3);
      }
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
    if (attack == Attack::Proyectil)
      boomerang->SetActive(true);
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

void MantisControllerComponent::OnCollision(GameObject *other) {
  if (!owner || !other)
    return;
  auto *my_col = owner->GetComponent<ColliderComponent>();
  auto *other_col = other->GetComponent<ColliderComponent>();
  if (!my_col || !other_col)
    return;

  if (other_col->is_trigger) {
    if ((other->GetTag() == "Sting") && invulnerability_timer <= 0.0f) {
      health -= 1;
      invulnerability_timer = 0.3f;

      if (health <= 0) {
        scene_manager->ChangeScene(std::make_unique<WinScene>(scene_manager));
      }
    }
    return;
  }
}
