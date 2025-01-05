#ifndef KINEMATIC_DATA_HPP_
#define KINEMATIC_DATA_HPP_

#include "vector2d.hpp"

namespace aifg
{

struct KinematicSteering {
  Vector2D linear_velocity_;
  float angular_velocity_ = 0.0f;
};

struct KinematicBody {
  Vector2D position_;
  Vector2D velocity_;
  float orientation_;
  float rotation_;

  KinematicBody(Vector2D position, Vector2D velocity, float orientation, float rotation)
      : position_(position), velocity_(velocity), orientation_(orientation), rotation_(rotation)
  {
  }
  KinematicBody(KinematicBody&) = default;
  KinematicBody& operator=(KinematicBody&) = default;
  KinematicBody(KinematicBody&&) = default;
  KinematicBody& operator=(KinematicBody&&) = default;
  void ResetToCenter();
  void Update(const KinematicSteering& steering, float time);
  float NewOrientation(const float& current_orientation, const Vector2D& velocity);
};

} // namespace aifg

#endif // KINEMATIC_DATA_HPP_
