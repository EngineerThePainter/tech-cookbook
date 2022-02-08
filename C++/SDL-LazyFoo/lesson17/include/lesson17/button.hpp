#ifndef LESSON17_BUTTON_HPP
#define LESSON17_BUTTON_HPP

#include <memory>

#include <SDL2/SDL.h>

#include "lesson17/texture.hpp"

namespace sdl_lazyfoo
{
namespace lesson17
{

const int BUTTON_WIDTH = 300;
const int BUTTON_HEIGHT = 400;
const int TOTAL_BUTTONS = 4;

enum ButtonSprite {
  BUTTON_SPRITE_MOUSE_OUT = 0,
  BUTTON_SPRITE_MOUSE_OVER_MOTION = 1,
  BUTTON_SPRITE_MOUSE_DOWN = 2,
  BUTTON_SPRITE_MOUSE_UP = 3,
  BUTTON_SPRITE_TOTAL = 4
};

class Button
{
public:
  Button();
  ~Button() = default;
  void SetTexture(const Texture& texture);
  void SetPosition(int x, int y);
  void HandleEvent(SDL_Event* event);
  void Render();

private:
  SDL_Point position_;
  ButtonSprite current_sprite_;
  SDL_Rect sprite_clips_[ButtonSprite::BUTTON_SPRITE_TOTAL];
  std::unique_ptr<Texture> current_texture_;
};

} // namespace lesson17
} // namespace sdl_lazyfoo

#endif