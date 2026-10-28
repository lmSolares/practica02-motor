#include "proyecto01/components/StingStrikeComponent.hpp"
#include "engine/GameObject.hpp"
#include "engine/components/ColliderComponent.hpp"
#include "engine/components/RectRenderComponent.hpp"
#include "engine/components/TransformComponent.hpp"
#include "math/Vector2.hpp"
#include "proyecto01/components/KnightControllerComponent.hpp"
#include <SDL3/SDL_keyboard.h>
#include <SDL3/SDL_scancode.h>

void StingStrikeComponent::SetKnight(GameObject *knight) {
  this->knight = knight;
}

void StingStrikeComponent::VerticalSting() {
  owner->GetComponent<RectRenderComponent>()->size = Vector2{5.0f, 40.0f};
  owner->GetComponent<ColliderComponent>()->size = Vector2{5.0f, 40.0f};
}

void StingStrikeComponent::HorizontalSting() {
  owner->GetComponent<RectRenderComponent>()->size = Vector2{40.0f, 5.0f};
  owner->GetComponent<ColliderComponent>()->size = Vector2{40.0f, 5.0f};
}

void StingStrikeComponent::Update(float dt) {

  active_timer -= dt;

  if (active_timer <= 0.0f) {
    is_striking_down = false;
    active_timer = 0.12f;
    owner->SetActive(false);
  }

  const bool *keys = SDL_GetKeyboardState(nullptr);

  Vector2 stingPos = {0.0f, 0.0f};
  Vector2 knightPos = knight->GetComponent<TransformComponent>()->position;
  int dir = knight->GetComponent<KnightControllerComponent>()->facing_dir;
  Vector2 sizeKnight = knight->GetComponent<ColliderComponent>()->size;
  Vector2 sizeSting = owner->GetComponent<ColliderComponent>()->size;

  if (keys[SDL_SCANCODE_UP]) {
    VerticalSting();
    stingPos.x = knightPos.x + sizeKnight.x / 2 - sizeSting.x / 2;
    stingPos.y = knightPos.y - sizeSting.y;
  } else if (keys[SDL_SCANCODE_DOWN] &&
             !knight->GetComponent<KnightControllerComponent>()->is_grounded) {
    VerticalSting();
    stingPos.x = knightPos.x + sizeKnight.x / 2 - sizeSting.x / 2;
    stingPos.y = knightPos.y + sizeKnight.y;
    is_striking_down = true;
  } else if (dir == 1) {
    HorizontalSting();
    sizeSting = owner->GetComponent<ColliderComponent>()->size;
    stingPos.x = knightPos.x + sizeKnight.x;
    stingPos.y = knightPos.y + sizeKnight.y / 2 - sizeSting.y / 2;
  } else {
    HorizontalSting();
    sizeSting = owner->GetComponent<ColliderComponent>()->size;
    stingPos.x = knightPos.x - sizeSting.x;
    stingPos.y = knightPos.y + sizeKnight.y / 2 - sizeSting.y / 2;
  }

  owner->GetComponent<TransformComponent>()->position = stingPos;
}

void StingStrikeComponent::FixedUpdate(float) {}

void StingStrikeComponent::OnCollision(GameObject *other) {
  if (!owner || !other)
    return;
  auto *my_transform = owner->GetComponent<TransformComponent>();
  auto *my_col = owner->GetComponent<ColliderComponent>();
  auto *other_col = other->GetComponent<ColliderComponent>();

  if (!my_transform || !my_col || !other_col)
    return;

  if ((other->GetTag() == "Spike" || other->GetTag() == "Mantis") &&
      is_striking_down) {
    knight->GetComponent<KnightControllerComponent>()->velocity.y = -550.0f;
    knight->GetComponent<KnightControllerComponent>()->dash_cooldown = 0.0f;
  }
}
