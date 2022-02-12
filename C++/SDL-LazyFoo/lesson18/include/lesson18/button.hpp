#ifndef LESSON18_BUTTON_HPP
#define LESSON18_BUTTON_HPP

#include <memory>

#include <SDL2/SDL.h>

#include "lesson18/texture.hpp"

namespace sdl_lazyfoo
{
namespace lesson18
{

const int BUTTON_WIDTH = 300;
const int BUTTON_HEIGHT = 200;
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
  void SetTexture(Texture* texture);
  void SetPosition(int x, int y);
  void HandleEvent(SDL_Event* event);
  void Render();

private:
  SDL_Point position_;
  ButtonSprite current_sprite_;
  SDL_Rect sprite_clips_[ButtonSprite::BUTTON_SPRITE_TOTAL];
  Texture* current_texture_ = nullptr;
};

} // namespace lesson18
} // namespace sdl_lazyfoo

#endif