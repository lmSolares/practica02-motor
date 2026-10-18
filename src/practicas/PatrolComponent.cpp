#include "../../include/practicas/PatrolComponent.hpp"
#include "../../include/motor/GameObject.hpp"
#include "../../include/motor/TransformComponent.hpp"
#include "cmath"

PatrolComponent::PatrolComponent(float spd, float dist)
    : speed(spd), distance(dist) {}

void PatrolComponent::Init() {
  if (auto *t = owner->GetComponent<TransformComponent>()) {
    origin_x = t->position.x;
  }
}
void PatrolComponent::FixedUpdate(float dt) {
  if (auto *t = owner->GetComponent<TransformComponent>()) {
    timer += dt * (speed / 50.0f);
    t->position.x = origin_x + std::sin(timer) * distance;
  }
}
