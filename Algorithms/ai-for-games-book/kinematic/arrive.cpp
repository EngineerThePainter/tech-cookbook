#include "arrive.hpp"

#include <cmath>

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>

#include "kinematic_common.hpp"

namespace aifg
{

Arrive::Arrive() : character_({600, 500}, {}, 0, 0), target_({200, 100}, {}, 0, 0) {}

void Arrive::UpdateBodies()
{
  // Reset positions
  float distance = Vector2D::distance(character_.position_, target_.position_);
  if (distance < kSatisfactionRadius) {
    character_.velocity_ = Vector2D();
  }

  // Base velocity is set to the target position
  KinematicSteering steering;
  steering.linear_velocity_ = target_.position_ - character_.position_;

  steering.linear_velocity_ = Vector2D::divideByScalar(steering.linear_velocity_, kTimeToTarget);

  if (steering.linear_velocity_.Length() > kMaxSpeed) {
    // Normalize the velocity to the maximum speed if going too fast
    steering.linear_velocity_.NormalizeTo(kMaxSpeed);
  }

  // Update the orientation
  character_.orientation_ = character_.NewOrientation(character_.orientation_, steering.linear_velocity_);
  steering.angular_velocity_ = 0;

  // Update the kinematic
  character_.Update(steering, 1.0f / 60.0f);
}

void Arrive::Update(ALLEGRO_DISPLAY* display, ALLEGRO_FONT* font)
{
  UpdateBodies();
  al_clear_to_color(al_map_rgb(0, 0, 0));
  drawMovingBody(character_, al_map_rgb(255, 0, 0), font);
  drawMovingBody(target_, al_map_rgb(0, 255, 0), font);
  al_flip_display();
}
} // namespace aifg