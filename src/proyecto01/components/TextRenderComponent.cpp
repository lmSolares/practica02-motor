#include "proyecto01/components/TextRenderComponent.hpp"
#include "motor/GameObject.hpp"
#include "motor/TransformComponent.hpp"

TextRenderComponent::TextRenderComponent(std::string t, float size, SDL_Color c)
    : text(t), pixel_size(size), color(c) {

  font['A'] = {" W ", "W W", "WWW", "W W", "W W"};
  font['B'] = {"WW ", "W W", "WW ", "W W", "WW "};
  font['C'] = {" WW", "W  ", "W  ", "W  ", " WW"};
  font['D'] = {"WW ", "W W", "W W", "W W", "WW "};
  font['E'] = {"WWW", "W  ", "WW ", "W  ", "WWW"};
  font['G'] = {" WW", "W  ", "W W", "W W", " WW"};
  font['H'] = {"W W", "W W", "WWW", "W W", "W W"};
  font['I'] = {"WWW", " W ", " W ", " W ", "WWW"};
  font['K'] = {"W W", "W W", "WW ", "W W", "W W"};
  font['M'] = {"W W", "WWW", "W W", "W W", "W W"};
  font['N'] = {"W W", "WWW", "WWW", "W W", "W W"};
  font['O'] = {" W ", "W W", "W W", "W W", " W "};
  font['P'] = {"WW ", "W W", "WW ", "W  ", "W  "};
  font['R'] = {"WW ", "W W", "WW ", "W W", "W W"};
  font['S'] = {" WW", "W  ", " W ", "  W", "WW "};
  font['T'] = {"WWW", " W ", " W ", " W ", " W "};
  font['U'] = {"W W", "W W", "W W", "W W", " WW"};
  font['V'] = {"W W", "W W", "W W", " W ", " W "};
  font['L'] = {"W  ", "W  ", "W  ", "W  ", "WWW"};
  font[' '] = {"   ", "   ", "   ", "   ", "   "};
}

void TextRenderComponent::Render(SDL_Renderer *renderer) {
  if (!owner)
    return;
  TransformComponent *transform = owner->GetComponent<TransformComponent>();
  if (!transform)
    return;

  SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

  float start_x = transform->position.x;
  float start_y = transform->position.y;
  float current_x = start_x;

  for (char c : text) {
    if (font.find(c) != font.end()) {
      const auto &letter = font[c];
      for (size_t row = 0; row < letter.size(); ++row) {
        for (size_t col = 0; col < letter[row].size(); ++col) {
          if (letter[row][col] == 'W') {
            SDL_FRect rect{current_x + (col * pixel_size * transform->scale.x),
                           start_y + (row * pixel_size * transform->scale.y),
                           pixel_size * transform->scale.x,
                           pixel_size * transform->scale.y};
            SDL_RenderFillRect(renderer, &rect);
          }
        }
      }
      current_x += (4.0f * pixel_size * transform->scale.x);
    }
  }
}
