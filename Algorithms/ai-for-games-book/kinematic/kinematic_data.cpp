#include "kinematic_data.hpp"

#include <cmath>

namespace aifg
{
void KinematicBody::Update(const KinematicSteeringOutput& steering, float time)
{
  position_x_ += velocity_x_ * time + 0.5f * steering.velocity_x_ * time * time;
  position_y_ += velocity_y_ * time + 0.5f * steering.velocity_y_ * time * time;

  orientation_ += rotation_ * time + 0.5f * steering.rotation_ * time * time;

  velocity_x_ += steering.velocity_x_ * time;
  velocity_y_ += steering.velocity_y_ * time;
}

float KinematicBody::NewOrientation(const float& current_orientation, const int& velocity_x, const int& velocity_y)
{
  if (velocity_x == 0 && velocity_y == 0) {
    return current_orientation;
  }
  return atan2(velocity_y, velocity_x);
}

} // namespace aifg