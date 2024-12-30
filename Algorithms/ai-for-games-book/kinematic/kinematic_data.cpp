#include "kinematic_data.hpp"

#include <cmath>
#include <loguru/loguru.hpp>

namespace aifg
{
void KinematicBody::ResetToCenter()
{
  position_x_ = 400.0f;
  position_y_ = 300.0f;
  velocity_x_ = 0.0f;
  velocity_y_ = 0.0f;
  rotation_ = 0.0f;
  orientation_ = 0.0f;
  LOG_F(INFO, "Reset to center %f %f", position_x_, position_y_);
}

void KinematicBody::Update(const KinematicSteering& steering, float time)
{
  position_x_ += steering.linear_velocity_x_ * time;
  position_y_ += steering.linear_velocity_y_ * time;
  LOG_F(INFO, "Velocity %f %f", steering.linear_velocity_x_, steering.linear_velocity_y_);
  LOG_F(INFO, "Position update to %f %f", position_x_, position_y_);
  orientation_ += steering.angular_velocity_ * time;

  velocity_x_ += steering.linear_velocity_x_ * time;
  velocity_y_ += steering.linear_velocity_y_ * time;
  rotation_ += steering.angular_velocity_ * time;
}

float KinematicBody::NewOrientation(const float& current_orientation, const int& velocity_x, const int& velocity_y)
{
  if (velocity_x == 0 && velocity_y == 0) {
    return current_orientation;
  }
  return atan2(velocity_y, velocity_x);
}

} // namespace aifg