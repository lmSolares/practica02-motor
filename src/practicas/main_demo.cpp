#define SDL_MAIN_USE_CALLBACKS 1
#include "engine/SceneManager.hpp"
#include "practicas/RenderDemoScene.hpp"
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <memory>

struct AppState {
  SDL_Renderer *renderer{nullptr};
  SDL_Window *window{nullptr};
  Uint64 last_ticks{0};
  float physics_accumulator{0.0f};
  static constexpr float FIXED_DT = 1.0f / 60.0f;
  SceneManager sceneManager;
} appstate;

SDL_AppResult SDL_AppInit(void **appstate, int argc, char **argv) {
  (void)argc;
  (void)argv;
  if (!SDL_Init(SDL_INIT_VIDEO))
    return SDL_APP_FAILURE;

  SDL_Window *window = nullptr;
  SDL_Renderer *renderer = nullptr;
  if (!SDL_CreateWindowAndRenderer("Practica 06 - Gestor de Recursos", 960, 540,
                                   SDL_WINDOW_RESIZABLE, &window, &renderer)) {
    return SDL_APP_FAILURE;
  }

  ::appstate.window = window;
  ::appstate.renderer = renderer;
  ::appstate.last_ticks = SDL_GetTicks();
  ::appstate.sceneManager.ChangeScene(
      std::make_unique<RenderDemoScene>(&::appstate.sceneManager));
  ::appstate.sceneManager.ProcessPendingChanges();
  *appstate = &::appstate;
  return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void *appstate) {
  AppState *app = static_cast<AppState *>(appstate);
  Uint64 current_ticks = SDL_GetTicks();
  float delta_time =
      static_cast<float>(current_ticks - app->last_ticks) / 1000.0f;
  app->last_ticks = current_ticks;
  if (delta_time > 0.05f)
    delta_time = 0.05f;

  app->sceneManager.Update(delta_time);
  app->physics_accumulator += delta_time;
  while (app->physics_accumulator >= AppState::FIXED_DT) {
    app->sceneManager.FixedUpdate(AppState::FIXED_DT);
    app->physics_accumulator -= AppState::FIXED_DT;
  }
  app->sceneManager.ProcessPendingChanges();

  SDL_SetRenderDrawColor(app->renderer, 20, 20, 20, 255);
  SDL_RenderClear(app->renderer);
  app->sceneManager.Render(app->renderer);
  SDL_RenderPresent(app->renderer);
  return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event) {
  AppState *app = static_cast<AppState *>(appstate);
  if (event->type == SDL_EVENT_QUIT)
    return SDL_APP_SUCCESS;
  if (app && app->sceneManager.HasScenes()) {
    app->sceneManager.HandleEvent(*event);
  }
  return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appstate, SDL_AppResult result) {
  (void)result;
  AppState *app = static_cast<AppState *>(appstate);
  if (app) {
    SDL_DestroyRenderer(app->renderer);
    SDL_DestroyWindow(app->window);
  }
  SDL_Quit();
}
