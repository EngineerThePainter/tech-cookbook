#ifndef lesson26_DOT_HPP
#define lesson26_DOT_HPP

#include <SDL2/SDL.h>

#include "texture.hpp"

namespace sdl_lazyfoo
{
namespace lesson26
{
class Dot
{
public:
  static const int DOT_WIDTH = 20;
  static const int DOT_HEIGHT = 20;
  static const int SCREEN_WIDTH = 640;
  static const int SCREEN_HEIGHT = 480;

  static const int DOT_VEL = 10;

  Dot(Texture& texture);
  void handleEvent(SDL_Event& e);
  void move();
  void render();

private:
  int x_;
  int y_;

  int vel_x_;
  int vel_y_;
  Texture& dot_texture;
};
} // namespace lesson26
} // namespace sdl_lazyfoo

#endif // lesson26_TEXTURE_HPP