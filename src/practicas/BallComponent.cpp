#include "../../include/practicas/BallComponent.hpp"
#include "../../include/motor/ColliderComponent.hpp"
#include "../../include/motor/RectRenderComponent.hpp"
#include "../../include/motor/TransformComponent.hpp"

void BallComponent::FixedUpdate(float dt) {
  if (!owner)
    return;
  auto *transform = owner->GetComponent<TransformComponent>();
  auto *rect = owner->GetComponent<RectRenderComponent>();
  if (!transform || !rect)
    return;

  transform->Translate(velocity * dt);

  if (transform->position.x <= 0.0f) {
    transform->position.x = 0.0f;
    velocity.x = std::abs(velocity.x);
  } else if (transform->position.x >= 960.0f - rect->size.x) {
    transform->position.x = 960.0f - rect->size.x;
    velocity.x = -std::abs(velocity.x);
  }

  if (transform->position.y <= 0.0f) {
    transform->position.y = 0.0f;
    velocity.y = std::abs(velocity.y);
  } else if (transform->position.y >= 540.0f - rect->size.y) {
    transform->position.y = 540.0f - rect->size.y;
    velocity.y = -std::abs(velocity.y);
  }
}

void BallComponent::OnCollision(GameObject *other) {
  if (!owner || !other)
    return;

  auto *my_transform = owner->GetComponent<TransformComponent>();
  auto *my_col = owner->GetComponent<ColliderComponent>();
  auto *other_transform = other->GetComponent<TransformComponent>();
  auto *other_col = other->GetComponent<ColliderComponent>();

  if (!my_transform || !my_col || !other_transform || !other_col)
    return;

  Vector2 my_center = my_transform->position + (my_col->size * 0.5f);
  Vector2 other_center = other_transform->position + (other_col->size * 0.5f);

  Vector2 d = my_center - other_center;

  if (std::abs(d.x) > std::abs(d.y)) {
    velocity.x = (d.x > 0) ? std::abs(velocity.x) : -std::abs(velocity.x);
  } else {
    velocity.y = (d.y > 0) ? std::abs(velocity.y) : -std::abs(velocity.y);
  }

  SDL_Log("Colisión: %s con %s", owner->GetTag().c_str(),
          other->GetTag().c_str());
}
