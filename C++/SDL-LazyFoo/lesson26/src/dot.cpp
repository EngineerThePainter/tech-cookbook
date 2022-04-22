#include "lesson26/dot.hpp"

namespace sdl_lazyfoo
{
namespace lesson26
{
Dot::Dot(Texture& texture) : x_(0), y_(0), vel_x_(0), vel_y_(0), dot_texture(texture) {}

void Dot::handleEvent(SDL_Event& e)
{
  if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
    switch (e.key.keysym.sym) {
    case SDLK_UP:
      vel_y_ -= DOT_VEL;
      break;
    case SDLK_DOWN:
      vel_y_ += DOT_VEL;
      break;
    case SDLK_LEFT:
      vel_x_ -= DOT_VEL;
      break;
    case SDLK_RIGHT:
      vel_x_ += DOT_VEL;
      break;
    };
  } else if (e.type == SDL_KEYUP && e.key.repeat == 0) {
    switch (e.key.keysym.sym) {
    case SDLK_UP:
      vel_y_ += DOT_VEL;
      break;
    case SDLK_DOWN:
      vel_y_ -= DOT_VEL;
      break;
    case SDLK_LEFT:
      vel_x_ += DOT_VEL;
      break;
    case SDLK_RIGHT:
      vel_x_ -= DOT_VEL;
      break;
    };
  }
}

void Dot::move()
{
  x_ += vel_x_;
  if ((x_ < 0) || (x_ + DOT_WIDTH > SCREEN_WIDTH)) {
    x_ -= vel_x_;
  }

  y_ += vel_y_;
  if ((y_ < 0) || (y_ + DOT_HEIGHT > SCREEN_HEIGHT)) {
    y_ -= vel_y_;
  }
}

void Dot::render() { dot_texture.Render(x_, y_); }

} // namespace lesson26
} // namespace sdl_lazyfoo