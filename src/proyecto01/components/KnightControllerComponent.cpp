#include "proyecto01/components/KnightControllerComponent.hpp"
#include "motor/ColliderComponent.hpp"
#include "motor/GameObject.hpp"
#include "motor/RectRenderComponent.hpp"
#include "motor/TransformComponent.hpp"
#include "motor/Vector2.hpp"
#include <SDL3/SDL_scancode.h>

void KnightControllerComponent::SetSting(GameObject *sting) {
  this->sting = sting;
}

void KnightControllerComponent::Update(float dt) {

  if (dash_cooldown > 0.0f)
    dash_cooldown -= dt;
  if (invulnerability_timer > 0.0f)
    invulnerability_timer -= dt;
  if (attack_cooldown > 0.0f)
    attack_cooldown -= dt;
  if (dash_timer > 0.0f) {
    dash_timer -= dt;
  } else if (dash_timer < 0.0f) {
    dash_timer = 0.0f;
    velocity.y = 0.0f;
  }

  if (dash_timer > 0.0f)
    return;

  const bool *keys = SDL_GetKeyboardState(nullptr);

  velocity.x = 0.0f;
  if (keys[SDL_SCANCODE_LEFT]) {
    velocity.x = -speed;
    facing_dir = -1;
  }
  if (keys[SDL_SCANCODE_RIGHT]) {
    velocity.x = speed;
    facing_dir = 1;
  }

  if ((keys[SDL_SCANCODE_Z]) && is_grounded) {
    velocity.y = jump_force;
    is_grounded = false;
  }

  if (keys[SDL_SCANCODE_X] && sting != nullptr) {
    if (attack_cooldown <= 0.0f) {
      sting->SetActive(true);
      attack_cooldown = 0.4f;
    }
  }

  if ((keys[SDL_SCANCODE_C]) && dash_cooldown <= 0.0f) {
    dash_timer = 0.15f;
    dash_cooldown = 0.6f;

    Vector2 dash_dir{0.0f, 0.0f};
    if (keys[SDL_SCANCODE_LEFT])
      dash_dir.x = -1.0f;
    if (keys[SDL_SCANCODE_RIGHT])
      dash_dir.x = 1.0f;
    if (keys[SDL_SCANCODE_UP])
      dash_dir.y = -1.0f;
    if (keys[SDL_SCANCODE_DOWN])
      dash_dir.y = 1.0f;

    if (dash_dir.length_squared() == 0.0f) {
      dash_dir.x = static_cast<float>(facing_dir);
    }

    dash_dir = dash_dir.normalized();
    velocity = dash_dir * dash_speed;
  }
}

void KnightControllerComponent::FixedUpdate(float fixed_dt) {
  if (!owner)
    return;
  TransformComponent *transform = owner->GetComponent<TransformComponent>();
  if (!transform)
    return;

  if (dash_timer <= 0.0f) {
    velocity.y += gravity * fixed_dt;
  }

  Vector2 displacement = velocity * fixed_dt;
  transform->Translate(displacement);

  is_grounded = false;

  Vector2 max_bounds{960.0f, 540.0f};
  if (auto *rect = owner->GetComponent<RectRenderComponent>()) {
    max_bounds = max_bounds - (rect->size * transform->scale.x);
  }
  transform->position =
      transform->position.clamp(Vector2{0.0f, 0.0f}, max_bounds);
}

void KnightControllerComponent::OnCollision(GameObject *other) {
  if (!owner || !other)
    return;

  auto *my_transform = owner->GetComponent<TransformComponent>();
  auto *my_col = owner->GetComponent<ColliderComponent>();
  auto *other_col = other->GetComponent<ColliderComponent>();

  if (!my_transform || !my_col || !other_col)
    return;

  if (other_col->is_trigger) {
    if ((other->GetTag() == "Spike" || other->GetTag() == "Mantis") &&
        invulnerability_timer <= 0.0f) {
      health -= 1;
      invulnerability_timer = 1.0f;
      if (other->GetTag() == "Spike") {
        my_transform->position = Vector2{460.0f, 300.0f};
        velocity = Vector2{0.0f, 0.0f};
      }
    }
    return;
  }

  SDL_FRect my_bounds = my_col->GetWorldBounds();
  SDL_FRect other_bounds = other_col->GetWorldBounds();

  float my_center_x = my_bounds.x + my_bounds.w * 0.5f;
  float my_center_y = my_bounds.y + my_bounds.h * 0.5f;
  float other_center_x = other_bounds.x + other_bounds.w * 0.5f;
  float other_center_y = other_bounds.y + other_bounds.h * 0.5f;

  float dx = my_center_x - other_center_x;
  float dy = my_center_y - other_center_y;

  float overlap_x = (my_bounds.w * 0.5f + other_bounds.w * 0.5f) - std::abs(dx);
  float overlap_y = (my_bounds.h * 0.5f + other_bounds.h * 0.5f) - std::abs(dy);

  if (overlap_x > 0.0f && overlap_y > 0.0f) {
    if (overlap_y <= overlap_x) {
      if (dy < 0) {
        my_transform->position.y -= overlap_y;
        velocity.y = 0.0f;
        is_grounded = true;
      } else {
        my_transform->position.y += overlap_y;
        if (velocity.y < 0.0f)
          velocity.y = 0.0f;
      }
    } else {
      if (dx < 0) {
        my_transform->position.x -= overlap_x;
      } else {
        my_transform->position.x += overlap_x;
      }
      velocity.x = 0.0f;
    }
  }
}
