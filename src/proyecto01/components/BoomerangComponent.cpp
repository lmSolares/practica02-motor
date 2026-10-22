#include "proyecto01/components/BoomerangComponent.hpp"
#include "motor/GameObject.hpp"
#include "motor/TransformComponent.hpp"
#include "motor/Vector2.hpp"

void BoomerangComponent::SetRoute(Vector2 start, Vector2 middle, Vector2 end) {
  this->start = start;
  this->middle = middle;
  this->end = end;
  on_the_move = true;
  start_in = MovingTo::start;
  moving_to = MovingTo::middle;
}

void BoomerangComponent::FixedUpdate(float fixed_dt) {
  if (on_the_move) {
    FollowRoute(fixed_dt);
  }
}

void BoomerangComponent::FollowRoute(float fixed_dt) {
  TransformComponent *transform = owner->GetComponent<TransformComponent>();
  if (!transform)
    return;

  Vector2 objetivo{0.0f, 0.0f};
  switch (moving_to) {
  case MovingTo::start:
    objetivo = start;
    break;
  case MovingTo::middle:
    objetivo = middle;
    break;
  case MovingTo::end:
    objetivo = end;
    break;
  }

  Vector2 actual = transform->position;
  Vector2 direccion = objetivo - actual;

  if (direccion.length_squared() < 150.0f) {
    if (moving_to == MovingTo::start) {
      moving_to = MovingTo::middle;
    } else if (moving_to == MovingTo::middle) {
      moving_to = MovingTo::end;
    } else if (moving_to == MovingTo::end) {
      owner->SetActive(false);
      on_the_move = false;
      return;
    }
  }

  Vector2 desplazamiento = direccion.normalized() * (speed * fixed_dt);
  transform->Translate(desplazamiento);
}
