#define SDL_MAIN_USE_CALLBACKS 1

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include "Vector2.hpp"

void SDL_LogPlatformInfo();

struct AppState
{
    SDL_Renderer *renderer{nullptr};
    SDL_Window *window{nullptr};

    // Temporizador para Delta Time
    Uint64 last_ticks{0};

    // Dimensiones y posición inicial del objeto (a manipular a mano inicialmente)
    float rect_x{440.0f};
    float rect_y{240.0f};
    float rect_width{60.0f};
    float rect_height{60.0f};
    float speed{300.0f}; // Píxeles por segundo
} appstate;

SDL_AppResult SDL_AppInit(void **appstate, int argc, char **argv)
{
    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Error al inicializar SDL: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    // Sugerir a la plataforma una tasa objetivo de 60 FPS
    SDL_SetHint(SDL_HINT_MAIN_CALLBACK_RATE, "60");

    SDL_LogPlatformInfo();

    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;

    if (!SDL_CreateWindowAndRenderer("Práctica 02 - Vectores y Movimiento", 960, 540, SDL_WINDOW_RESIZABLE, &window, &renderer))
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Error al crear ventana o renderer: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    SDL_Log("Renderer Driver activo: %s", SDL_GetRendererName(renderer));

    ::appstate.window = window;
    ::appstate.renderer = renderer;
    ::appstate.last_ticks = SDL_GetTicks();

    *appstate = &::appstate;
    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void *appstate)
{
    AppState *app = static_cast<AppState *>(appstate);

    // 1. Medición de Delta Time en segundos
    Uint64 current_ticks = SDL_GetTicks();
    float delta_time = static_cast<float>(current_ticks - app->last_ticks) / 1000.0f;
    app->last_ticks = current_ticks;

    // Evitar saltos de tiempo excesivos si el sistema operativo pausa el proceso
    if (delta_time > 0.05f)
    {
        delta_time = 0.05f;
    }

    // 2. Fase de Actualización (Update)
    // TODO (Paso 2): Obtener el estado del teclado con SDL_GetKeyboardState y mover el rectángulo.
    const bool *keys = SDL_GetKeyboardState(nullptr);
    if (keys[SDL_SCANCODE_W] || keys[SDL_SCANCODE_UP])
    {
    app->rect_y -= app->speed * delta_time;
    }
    if (keys[SDL_SCANCODE_S] || keys[SDL_SCANCODE_DOWN])
    {
    app->rect_y += app->speed * delta_time;
    }
    if (keys[SDL_SCANCODE_A] || keys[SDL_SCANCODE_LEFT])
    {
    app->rect_x -= app->speed * delta_time;
    }
    if (keys[SDL_SCANCODE_D] || keys[SDL_SCANCODE_RIGHT]){
    app->rect_x += app->speed * delta_time;
    }
    // TODO (Paso 3): Probar el bug del movimiento en diagonal.
    // TODO (Paso 4 y 5): Reemplazar variables sueltas con Vector2 y extraer a Vector2.hpp.
    // TODO (Paso 6): Normalizar el vector de dirección para velocidad uniforme.
    // TODO (Paso 7): Encapsular en un struct Character (composición sobre herencia).

    // 3. Fase de Renderizado
    SDL_SetRenderDrawColor(app->renderer, 30, 30, 35, 255);
    SDL_RenderClear(app->renderer);

    // Dibujar el rectángulo del jugador
    SDL_SetRenderDrawColor(app->renderer, 60, 180, 100, 255);
    SDL_FRect player_rect{app->rect_x, app->rect_y, app->rect_width, app->rect_height};
    SDL_RenderFillRect(app->renderer, &player_rect);

    SDL_RenderPresent(app->renderer);

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event)
{
    if (event->type == SDL_EVENT_QUIT)
    {
        return SDL_APP_SUCCESS;
    }
    return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appstate, SDL_AppResult result)
{
    AppState *app = static_cast<AppState *>(appstate);
    if (app)
    {
        SDL_DestroyRenderer(app->renderer);
        SDL_DestroyWindow(app->window);
    }
    SDL_Quit();
}

void SDL_LogPlatformInfo()
{
    SDL_Log("Plataforma: %s", SDL_GetPlatform());
    SDL_Log("Cores lógicos de CPU: %d", SDL_GetNumLogicalCPUCores());
    SDL_Log("RAM total: %d MB", SDL_GetSystemRAM());
    SDL_Log("Driver de video: %s", SDL_GetCurrentVideoDriver());
}
