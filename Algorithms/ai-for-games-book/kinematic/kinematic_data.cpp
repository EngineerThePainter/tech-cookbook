#include "kinematic_data.hpp"

#include <cmath>
#include <loguru/loguru.hpp>

#include "allegro.hpp"
#include "kinematic_common.hpp"

namespace aifg
{
void KinematicBody::ResetToCenter()
{
  position_.X(SCREEN_WIDTH / 2);
  position_.Y(SCREEN_HEIGHT / 2);
  velocity_.X(0);
  velocity_.Y(0);
  rotation_ = 0.0f;
  orientation_ = 0.0f;
  LOG_F(INFO, "Reset to center");
}

void KinematicBody::Update(const KinematicSteering& steering, float time)
{
  position_ += Vector2D::multiplyByScalar(steering.linear_velocity_, time);
  orientation_ += steering.angular_velocity_ * time;

  velocity_ += Vector2D::multiplyByScalar(steering.linear_velocity_, time);
  rotation_ += steering.angular_velocity_ * time;
}

void KinematicBody::UpdateDynamic(const KinematicSteering& steering, float time)
{
  position_ += Vector2D::multiplyByScalar(steering.linear_velocity_, time);
  orientation_ += rotation_ * time;

  velocity_ += Vector2D::multiplyByScalar(steering.linear_velocity_, time);
  rotation_ += steering.angular_velocity_ * time;

  if (velocity_.Length() > kMaxSpeed) {
    velocity_.NormalizeTo(kMaxSpeed);
  }
}

void KinematicBody::NewOrientation(const Vector2D& velocity)
{
  if (velocity.X() != 0 && velocity.Y() != 0) {
    orientation_ = atan2(-velocity.Y(), velocity.X());
  }
}

} // namespace aifg