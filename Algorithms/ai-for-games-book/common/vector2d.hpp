#pragma once

namespace aifg
{
class Vector2D
{
public:
  static Vector2D multiplyByScalar(const Vector2D& vec, const int scalar);
  static Vector2D multiplyByScalar(const Vector2D& vec, const float scalar);
  static Vector2D divideByScalar(const Vector2D& vec, const int scalar);
  static int distance(const Vector2D& a, const Vector2D& b);
  Vector2D();
  Vector2D(int x, int y);

  Vector2D(Vector2D& other);
  Vector2D& operator=(const Vector2D& other);
  Vector2D(Vector2D&& other);
  Vector2D& operator=(const Vector2D&& other);

  void NormalizeTo(const int& max_value);
  const int Length() const;

  void X(int new_x);
  const int X() const;
  void Y(int new_y);
  const int Y() const;

  Vector2D& operator+=(const Vector2D& rhs)
  {
    x_ += rhs.x_;
    y_ += rhs.y_;
    return *this;
  }

  friend Vector2D operator+(Vector2D lhs, const Vector2D& rhs)
  {
    lhs += rhs;
    return lhs;
  }

  Vector2D& operator-=(const Vector2D& rhs)
  {
    x_ -= rhs.x_;
    y_ -= rhs.y_;
    return *this;
  }

  friend Vector2D operator-(Vector2D lhs, const Vector2D& rhs)
  {
    lhs -= rhs;
    return lhs;
  }

private:
  int x_;
  int y_;
};
} // namespace aifg