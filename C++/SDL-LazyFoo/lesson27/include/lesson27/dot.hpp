#ifndef lesson27_DOT_HPP
#define lesson27_DOT_HPP

#include <SDL2/SDL.h>

#include "texture.hpp"

namespace sdl_lazyfoo
{
namespace lesson27
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
  void move(SDL_Rect& wall);
  void render();

private:
  int x_;
  int y_;

  int vel_x_;
  int vel_y_;

  SDL_Rect collider_;

  Texture& dot_texture;

  static bool checkCollision(SDL_Rect& a, SDL_Rect& b);
};
} // namespace lesson27
} // namespace sdl_lazyfoo

#endif // lesson27_TEXTURE_HPP