#include "lesson28/dot.hpp"

#include <iostream>

namespace sdl_lazyfoo
{
namespace lesson28
{
Dot::Dot(int x, int y, Texture& texture) : x_(x), y_(y), vel_x_(0), vel_y_(0), dot_texture(texture)
{
  colliders_.resize(11);
  colliders_[0].w = 6;
  colliders_[0].h = 1;
  colliders_[1].w = 10;
  colliders_[1].h = 1;
  colliders_[2].w = 14;
  colliders_[2].h = 1;
  colliders_[3].w = 16;
  colliders_[3].h = 2;
  colliders_[4].w = 18;
  colliders_[4].h = 2;
  colliders_[5].w = 20;
  colliders_[5].h = 6;
  colliders_[6].w = 18;
  colliders_[6].h = 2;
  colliders_[7].w = 16;
  colliders_[7].h = 2;
  colliders_[8].w = 14;
  colliders_[8].h = 1;
  colliders_[9].w = 10;
  colliders_[9].h = 1;
  colliders_[10].w = 6;
  colliders_[10].h = 1;

  shiftColliders();
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

void Dot::move(const std::vector<SDL_Rect>& otherColliders)
{
  x_ += vel_x_;
  shiftColliders();

  if ((x_ < 0) || (x_ + DOT_WIDTH > SCREEN_WIDTH) || checkCollision(colliders_, otherColliders)) {
    x_ -= vel_x_;
    shiftColliders();
  }

  y_ += vel_y_;
  shiftColliders();

  if ((y_ < 0) || (y_ + DOT_HEIGHT > SCREEN_HEIGHT) || checkCollision(colliders_, otherColliders)) {
    y_ -= vel_y_;
    shiftColliders();
  }
}

const std::vector<SDL_Rect>& Dot::getColliders() const { return colliders_; }

void Dot::render() { dot_texture.Render(x_, y_); }

void Dot::shiftColliders()
{
  int r = 0;
  for (auto& collider : colliders_) {
    collider.x = x_ + (DOT_WIDTH - collider.w) / 2;
    collider.y = y_ + r;
    r += collider.h;
  }
}

bool Dot::checkCollision(const std::vector<SDL_Rect>& a, const std::vector<SDL_Rect>& b)
{

  int leftA, leftB;
  int rightA, rightB;
  int topA, topB;
  int bottomA, bottomB;

  for (const auto& aBox : a) {
    leftA = aBox.x;
    rightA = aBox.x + aBox.w;
    topA = aBox.y;
    bottomA = aBox.y + aBox.h;
    for (const auto& bBox : b) {
      leftB = bBox.x;
      rightB = bBox.x + bBox.w;
      topB = bBox.y;
      bottomB = bBox.y + bBox.h;

      if (((bottomA <= topB) || (topA >= bottomB) || (rightA <= leftB) || (leftA >= rightB)) == false) {
        return true;
      }
    }
  }

  return false;
}

} // namespace lesson28
} // namespace sdl_lazyfoo