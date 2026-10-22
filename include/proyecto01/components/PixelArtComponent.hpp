#pragma once

#include "motor/Component.hpp"
#include <string>
#include <vector>

class PixelArtComponent : public Component {
public:
  std::vector<std::string> pixels;
  float pixel_size{4.0f};

  PixelArtComponent() = default;
  explicit PixelArtComponent(std::vector<std::string> p, float size = 4.0f)
      : pixels(std::move(p)), pixel_size(size) {}

  void Render(SDL_Renderer *renderer) override;
};
