#define SDL_MAIN_USE_CALLBACKS 1
#include "GameObject.hpp"
#include "PlayerControllerComponent.hpp"
#include "RectRenderComponent.hpp"
#include "TransformComponent.hpp"
#include "Vector2.hpp"
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <memory>
#include <vector>

void SDL_LogPlatformInfo();
struct AppState {
  SDL_Renderer *renderer{nullptr};
  SDL_Window *window{nullptr};
  Uint64 last_ticks{0};
  float physics_accumulator{0.0f};
  // Colección de todas las entidades activas en el mundo
  std::vector<std::unique_ptr<GameObject>> entities;
} appstate;

SDL_AppResult SDL_AppInit(void **appstate, int argc, char **argv) {
  if (!SDL_Init(SDL_INIT_VIDEO)) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Error al inicializar SDL: %s",
                 SDL_GetError());
    return SDL_APP_FAILURE;
  }

  // Sugerir a la plataforma una tasa objetivo de 60 FPS
  SDL_SetHint(SDL_HINT_MAIN_CALLBACK_RATE, "60");

  SDL_LogPlatformInfo();

  SDL_Window *window = nullptr;
  SDL_Renderer *renderer = nullptr;

  if (!SDL_CreateWindowAndRenderer(
          "Práctica 03 - Arquitectura de motores: GameObject y componentes",
          960, 540, SDL_WINDOW_RESIZABLE, &window, &renderer)) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
                 "Error al crear ventana o renderer: %s", SDL_GetError());
    return SDL_APP_FAILURE;
  }

  // Armamos del Jugador
  auto player = std::make_unique<GameObject>("Player");
  player->AddComponent<TransformComponent>(Vector2{440.0f, 240.0f},
                                           Vector2{1.0f, 1.0f});
  player->AddComponent<RectRenderComponent>(Vector2{60.0f, 60.0f},
                                            SDL_Color{60, 180, 100, 255});
  player->AddComponent<PlayerControllerComponent>(300.0f, true);
  ::appstate.entities.push_back(std::move(player));

  SDL_Log("Renderer Driver activo: %s", SDL_GetRendererName(renderer));

  ::appstate.window = window;
  ::appstate.renderer = renderer;
  ::appstate.last_ticks = SDL_GetTicks();

  *appstate = &::appstate;
  return SDL_APP_CONTINUE;
}

void PhysicsUpdate(Character &character, const Vector2 &direction,
                   float fixed_dt) {
  Vector2 displacement = direction * (character.speed * fixed_dt);
  Vector2 position = character.position + displacement;

  if (position.x < 0)
    position.x = 0;
  if (position.x > 960 - character.size.x)
    position.x = 960 - character.size.x;
  if (position.y < 0)
    position.y = 0;
  if (position.y > 540 - character.size.y)
    position.y = 540 - character.size.y;

  character.position = position;
}

SDL_AppResult SDL_AppIterate(void *appstate) {
  AppState *app = static_cast<AppState *>(appstate);

  // 1. Medición de Delta Time en segundos
  Uint64 current_ticks = SDL_GetTicks();
  float delta_time =
      static_cast<float>(current_ticks - app->last_ticks) / 1000.0f;
  app->last_ticks = current_ticks;

  // Evitar saltos de tiempo excesivos si el sistema operativo pausa el proceso
  if (delta_time > 0.05f) {
    delta_time = 0.05f;
  }

  const bool *keys = SDL_GetKeyboardState(nullptr);
  Vector2 input_dir{0.0f, 0.0f};
  if (keys[SDL_SCANCODE_W] || keys[SDL_SCANCODE_UP])
    input_dir.y -= 1.0f;
  if (keys[SDL_SCANCODE_S] || keys[SDL_SCANCODE_DOWN])
    input_dir.y += 1.0f;
  if (keys[SDL_SCANCODE_A] || keys[SDL_SCANCODE_LEFT])
    input_dir.x -= 1.0f;
  if (keys[SDL_SCANCODE_D] || keys[SDL_SCANCODE_RIGHT])
    input_dir.x += 1.0f;

  if (input_dir.length_squared() > 0.0f) {
    input_dir = input_dir.normalized();
  }

  // Fase de Actualización
  constexpr float FIXED_TIMESTEP = 1.0f / 60.0f;
  app->physics_accumulator += delta_time;
  while (app->physics_accumulator >= FIXED_TIMESTEP) {
    for (auto &entity : app->entities) {
      entity->Update(FIXED_TIMESTEP);
    }
    app->physics_accumulator -= FIXED_TIMESTEP;
  }
  // Fase de Renderizado
  SDL_SetRenderDrawColor(app->renderer, 25, 25, 30, 255);
  SDL_RenderClear(app->renderer);
  for (auto &entity : app->entities) {
    entity->Render(app->renderer);
  }
  SDL_RenderPresent(app->renderer);

  return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event) {
  if (event->type == SDL_EVENT_QUIT) {
    return SDL_APP_SUCCESS;
  }
  return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appstate, SDL_AppResult result) {
  AppState *app = static_cast<AppState *>(appstate);
  if (app) {
    app->entities.clear();
    SDL_DestroyRenderer(app->renderer);
    SDL_DestroyWindow(app->window);
  }
  SDL_Quit();
}

void SDL_LogPlatformInfo() {
  SDL_Log("Plataforma: %s", SDL_GetPlatform());
  SDL_Log("Cores lógicos de CPU: %d", SDL_GetNumLogicalCPUCores());
  SDL_Log("RAM total: %d MB", SDL_GetSystemRAM());
  SDL_Log("Driver de video: %s", SDL_GetCurrentVideoDriver());
}
