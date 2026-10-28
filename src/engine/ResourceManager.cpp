#include "engine/ResourceManager.hpp"
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_surface.h>
#include <SDL3_image/SDL_image.h>

SDL_Texture *ResourceManager::GetTexture(const std::string &filepath) {

  auto cache = m_textures.find(filepath);

  if (cache != m_textures.end())
    return cache->second.get();

  if (!m_renderer) {
    SDL_Log("Error: Renderer nulo al cargar %s", filepath.c_str());
    return nullptr;
  }

  SDL_Surface *surface = IMG_Load(filepath.c_str());

  if (!surface) {
    SDL_Log("Error de IMG_Load en %s", filepath.c_str());
    return nullptr;
  }

  SDL_Texture *texture = SDL_CreateTextureFromSurface(m_renderer, surface);

  SDL_DestroySurface(surface);

  if (!texture) {
    SDL_Log("Error de SDL_CreateTextureFromSurface en %s", filepath.c_str());
    return nullptr;
  }

  m_textures[filepath] = TexturePtr(texture);

  return texture;
}
