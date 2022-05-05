#ifndef lesson28_DOT_HPP
#define lesson28_DOT_HPP

#include <vector>

#include <SDL2/SDL.h>

#include "texture.hpp"

namespace sdl_lazyfoo
{
namespace lesson28
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
  void move(const std::vector<SDL_Rect>& otherColliders);
  void render();
  const std::vector<SDL_Rect>& getColliders() const;

private:
  int x_;
  int y_;

  int vel_x_;
  int vel_y_;

  std::vector<SDL_Rect> colliders_;

  Texture& dot_texture;

  void shiftColliders();

  static bool checkCollision(const std::vector<SDL_Rect>& a, const std::vector<SDL_Rect>& b);
};
} // namespace lesson28
} // namespace sdl_lazyfoo

#endif // lesson28_TEXTURE_HPP