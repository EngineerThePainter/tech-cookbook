#include "arrive_dynamic.hpp"

#include <cmath>

#include "allegro.hpp"
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>

#include "kinematic_common.hpp"

namespace aifg
{

ArriveDynamic::ArriveDynamic()
    : character_({SCREEN_WIDTH * 0.5, SCREEN_HEIGHT * 0.5}, {}, 0, 0),
      target_({SCREEN_WIDTH * 0.2, SCREEN_WIDTH * 0.1}, {}, 0, 0)
{
}

void ArriveDynamic::Update(ALLEGRO_DISPLAY* display, ALLEGRO_FONT* font)
{
  UpdateBodies();
  al_clear_to_color(al_map_rgb(0, 0, 0));
  drawMovingBody(character_, al_map_rgb(255, 0, 0), font);
  drawMovingBody(target_, al_map_rgb(0, 255, 0), font);
  al_flip_display();
}

void ArriveDynamic::UpdateBodies()
{
  KinematicSteering steering;

  // Get direction to target
  Vector2D direction = target_.position_ - character_.position_;
  float distance = direction.Length();
  float target_speed = 0.0f;
  if (distance >= kSatisfactionRadius) {
    if (distance > kSlowRadius) {
      // Go full speed
      target_speed = kMaxSpeed;
    } else {
      target_speed = kMaxSpeed * distance / kSlowRadius;
    }

    // Target velocity combines speed and direction
    Vector2D target_velocity = direction;
    target_velocity.NormalizeTo(target_speed);
    // Acceleration tries to get to the target velocity
    steering.linear_velocity_ = target_velocity - character_.velocity_;
    steering.linear_velocity_ = Vector2D::divideByScalar(steering.linear_velocity_, kTimeToTargetSpeed);

    // Clip too fast acceleration
    if (steering.linear_velocity_.Length() > kMaxAcceleration) {
      steering.linear_velocity_.NormalizeTo(kMaxAcceleration);
    }

    // Update the orientation
    character_.NewOrientation(steering.linear_velocity_);
    steering.angular_velocity_ = 0;
  }
  character_.UpdateDynamic(steering, kTime);
}
} // namespace aifg