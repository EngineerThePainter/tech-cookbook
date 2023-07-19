#include "lesson32/dot.hpp"

#include <iostream>

namespace sdl_lazyfoo
{
namespace lesson32
{
Dot::Dot(int x, int y, Texture& texture) : x_(x), y_(y), vel_x_(0), vel_y_(0), dot_texture(texture)
{
  dot_texture.SetWidth(DOT_WIDTH);
  dot_texture.SetHeight(DOT_HEIGHT);
  collider_.r = DOT_WIDTH / 2;
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

void Dot::move(const SDL_Rect& square, const Circle& circle)
{
  x_ += vel_x_;
  shiftColliders();

  if ((x_ - collider_.r < 0) || (x_ + collider_.r > SCREEN_WIDTH) || checkCollision(collider_, square) ||
      checkCollision(collider_, circle)) {
    x_ -= vel_x_;
    shiftColliders();
  }

  y_ += vel_y_;
  shiftColliders();

  if ((y_ - collider_.r < 0) || (y_ + collider_.r > SCREEN_HEIGHT) || checkCollision(collider_, square) ||
      checkCollision(collider_, circle)) {
    y_ -= vel_y_;
    shiftColliders();
  }
}

const Circle& Dot::getCollider() const { return collider_; }

void Dot::render(int camX, int camY) { dot_texture.Render(x_ - camX, y_ - camY); }

void Dot::render() { dot_texture.Render(x_, y_); }

const int Dot::getX() const { return x_; }
const int Dot::getY() const { return y_; }

void Dot::shiftColliders()
{
  collider_.x = x_;
  collider_.y = y_;
}

bool Dot::checkCollision(const Circle& a, const Circle& b)
{
  int totalRadiusSquared = a.r + b.r;
  totalRadiusSquared *= totalRadiusSquared;

  if (distanceSquared(a.x, a.y, b.x, b.y) < totalRadiusSquared) {
    return true;
  }

  return false;
}

bool Dot::checkCollision(const Circle& a, const SDL_Rect& b)
{
  int cX, cY;
  if (a.x < b.x) {
    cX = b.x;
  } else if (a.x > b.x + b.w) {
    cX = b.x + b.w;
  } else {
    cX = a.x;
  }

  if (a.y < b.y) {
    cY = b.y;
  } else if (a.y > b.y + b.h) {
    cY = b.y + b.h;
  } else {
    cY = a.y;
  }

  if (distanceSquared(a.x, a.y, cX, cY) < (a.r * a.r)) {
    return true;
  }

  return false;
}

double Dot::distanceSquared(const int x1, const int y1, const int x2, const int y2)
{
  int deltaX = x2 - x1;
  int deltaY = y2 - y1;
  return deltaX * deltaX + deltaY * deltaY;
}

} // namespace lesson32
} // namespace sdl_lazyfoo