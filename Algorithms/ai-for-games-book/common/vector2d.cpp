#include "vector2d.hpp"

#include <cmath>

namespace aifg
{
static Vector2D multiplyByScalar(const Vector2D& vec, const int scalar)
{
  return Vector2D(vec.X() * scalar, vec.Y() * scalar);
}

Vector2D::Vector2D() : x_(0), y_(0) {}
Vector2D::Vector2D(int x, int y) : x_(x), y_(y) {}

void Vector2D::X(int new_x) { x_ = std::move(new_x); }

const int Vector2D::X() const { return x_; }

void Vector2D::Y(int new_y) { y_ = std::move(new_y); }

const int Vector2D::Y() const { return y_; };

void Vector2D::NormalizeTo(const int& max_value)
{
  const int length = this->Length();
  this->x_ = this->x_ / length * max_value;
  this->y_ = this->y_ / length * max_value;
}

const int Vector2D::Length() const { return sqrt(this->x_ * this->x_ + this->y_ * this->y_); }
} // namespace aifg