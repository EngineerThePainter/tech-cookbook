#pragma once

namespace aifg
{
class Vector2D
{
public:
  static Vector2D multiplyByScalar(const Vector2D& vec, const float scalar);
  static Vector2D divideByScalar(const Vector2D& vec, const float scalar);
  static float distance(const Vector2D& a, const Vector2D& b);
  Vector2D();
  Vector2D(float x, float y);

  Vector2D(Vector2D& other);
  Vector2D& operator=(const Vector2D& other);
  Vector2D(Vector2D&& other);
  Vector2D& operator=(const Vector2D&& other);

  void NormalizeTo(const float& max_value);
  void Normalize();
  const float Length() const;

  void X(float new_x);
  const float X() const;
  void Y(float new_y);
  const float Y() const;

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
  float x_;
  float y_;
};
} // namespace aifg