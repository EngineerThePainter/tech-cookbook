#ifndef lesson29_DOT_HPP
#define lesson29_DOT_HPP

#include <vector>

#include <SDL2/SDL.h>

#include "circle.hpp"
#include "texture.hpp"

namespace sdl_lazyfoo
{
namespace lesson29
{
class Dot
{
public:
  static const int DOT_WIDTH = 20;
  static const int DOT_HEIGHT = 20;
  static const int SCREEN_WIDTH = 640;
  static const int SCREEN_HEIGHT = 480;

  static const int DOT_VEL = 1;

  Dot(int x, int y, Texture& texture);
  void handleEvent(SDL_Event& e);
  void move(const SDL_Rect& square, const Circle& circle);
  void render();
  const Circle& getCollider() const;

private:
  int x_;
  int y_;

  int vel_x_;
  int vel_y_;

  Circle collider_;

  Texture& dot_texture;

  void shiftColliders();

  static bool checkCollision(const Circle& a, const Circle& b);
  static bool checkCollision(const Circle& a, const SDL_Rect& b);
  static double distanceSquared(const int x1, const int y1, const int x2, const int y2);
};
} // namespace lesson29
} // namespace sdl_lazyfoo

#endif // lesson29_TEXTURE_HPP