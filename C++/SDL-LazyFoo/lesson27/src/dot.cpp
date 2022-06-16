#include "lesson27/dot.hpp"

#include <iostream>

namespace sdl_lazyfoo
{
namespace lesson27
{
Dot::Dot(Texture& texture) : x_(0), y_(0), vel_x_(0), vel_y_(0), dot_texture(texture)
{
  collider_.x = x_;
  collider_.y = y_;
  collider_.w = DOT_WIDTH;
  collider_.h = DOT_HEIGHT;
}

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

void Dot::move(SDL_Rect& wall)
{
  x_ += vel_x_;
  collider_.x = x_;

  if ((x_ < 0) || (x_ + DOT_WIDTH > SCREEN_WIDTH) || checkCollision(collider_, wall)) {
    x_ -= vel_x_;
    collider_.x -= x_;
  }

  y_ += vel_y_;
  collider_.y = y_;
  if ((y_ < 0) || (y_ + DOT_HEIGHT > SCREEN_HEIGHT) || checkCollision(collider_, wall)) {
    y_ -= vel_y_;
    collider_.y = y_;
  }
}

void Dot::render() { dot_texture.Render(x_, y_); }

bool Dot::checkCollision(SDL_Rect& a, SDL_Rect& b)
{
  int leftA, leftB;
  int rightA, rightB;
  int topA, topB;
  int bottomA, bottomB;

  leftA = a.x;
  rightA = a.x + a.w;
  topA = a.y;
  bottomA = a.y + a.h;

  leftB = b.x;
  rightB = b.x + b.w;
  topB = b.y;
  bottomB = b.y + b.h;

  if (bottomA <= topB) {
    return false;
  }

  if (topA >= bottomB) {
    return false;
  }

  if (rightA <= leftB) {
    return false;
  }

  if (leftA >= rightB) {
    return false;
  }
  std::cerr << "Collision\n";
  return true;
}

} // namespace lesson27
} // namespace sdl_lazyfoo