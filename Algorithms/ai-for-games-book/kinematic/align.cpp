#include "align.hpp"

#include <cmath>

#include <loguru/loguru.hpp>

#include "allegro.hpp"
#include "kinematic_common.hpp"

namespace aifg
{
Align::Align()
    : character_({SCREEN_WIDTH * 0.8, SCREEN_HEIGHT * 0.2}, {}, M_PI / 2, 0),
      target_({SCREEN_WIDTH * 0.2, SCREEN_HEIGHT * 0.8}, {}, 3 * M_PI / 4, 0)
{
}

void Align::UpdateBodies()
{
  KinematicSteering steering;
  float rotation = target_.orientation_ - character_.orientation_;
  LOG_F(INFO, "Orientation character %f", character_.orientation_);
  LOG_F(INFO, "Orientation target %f", target_.orientation_);
  // Map the result to the (-pi, pi) interval
  rotation = mapToPiRange(std::move(rotation));
  LOG_F(INFO, "Rotation %f", rotation);
  float rotationSize = abs(rotation);

  // If we are there, then no steering
  if (rotationSize < kSatisfactionRotation) {
    LOG_F(INFO, "Reached target location");
    character_.rotation_ = 0;
  } else {
    float targetRotation = 0;
    if (rotationSize > kSlowRotation) {
      targetRotation = kMaxRotation;
    } else {
      targetRotation = kMaxRotation * rotationSize / kSlowRotation;
    }

    // Final target rotation combines speed and direction
    targetRotation *= rotation / rotationSize;
    steering.angular_velocity_ = targetRotation - character_.rotation_;
    steering.angular_velocity_ /= kTimeToTargetSpeed;

    // Check if the acceleration is not too great
    float angularAcceleration = abs(steering.angular_velocity_);
    if (angularAcceleration > kMaxAngularAcceleration) {
      steering.angular_velocity_ /= angularAcceleration;
      steering.angular_velocity_ *= kMaxAngularAcceleration;
    }
  }
  LOG_F(INFO, "Steering: %f", steering.angular_velocity_);
  // Update the orientation
  steering.linear_velocity_ = {};
  character_.UpdateDynamic(steering, kTime);
}

void Align::Update(ALLEGRO_DISPLAY* display, ALLEGRO_FONT* font)
{
  UpdateBodies();
  al_clear_to_color(al_map_rgb(0, 0, 0));
  drawMovingBody(character_, al_map_rgb(255, 0, 0), font);
  drawMovingBody(target_, al_map_rgb(0, 255, 0), font);
  al_flip_display();
}
} // namespace aifg