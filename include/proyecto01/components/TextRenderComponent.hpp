#pragma once
#include "motor/Component.hpp"
#include <SDL3/SDL.h>
#include <string>
#include <unordered_map>
#include <vector>

class TextRenderComponent : public Component {
public:
  std::string text;
  float pixel_size;
  SDL_Color color;
  std::unordered_map<char, std::vector<std::string>> font;

  TextRenderComponent(std::string t, float size, SDL_Color c);
  void Render(SDL_Renderer *renderer) override;
};
