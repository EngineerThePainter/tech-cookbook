#include "arrive.hpp"

#include <cmath>

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>

#include "kinematic_common.hpp"

namespace aifg
{

Arrive::Arrive() : character_(600, 500, 0, 0, 0, 0), target_(200, 100, 0, 0, 0, 0) {}

void Arrive::UpdateBodies()
{
  // Reset positions
  float distance =
      sqrt(pow(character_.position_x_ - target_.position_x_, 2) + pow(character_.position_y_ - target_.position_y_, 2));
  if (distance < kSatisfactionRadius) {
    character_.velocity_x_ = 0;
    character_.velocity_y_ = 0;
  }

  // Base velocity is set to the target position
  KinematicSteeringOutput steering;
  steering.velocity_x_ = target_.position_x_ - character_.position_x_;
  steering.velocity_y_ = target_.position_y_ - character_.position_y_;

  steering.velocity_x_ = steering.velocity_x_ / kTimeToTarget;
  steering.velocity_y_ = steering.velocity_y_ / kTimeToTarget;

  if (sqrt(steering.velocity_x_ * steering.velocity_x_ + steering.velocity_y_ * steering.velocity_y_) > kMaxSpeed) {
    // Normalize the velocity to the maximum speed if going too fast
    float steering_vector_length =
        sqrt(steering.velocity_x_ * steering.velocity_x_ + steering.velocity_y_ * steering.velocity_y_);
    steering.velocity_x_ = (steering.velocity_x_ / steering_vector_length) * kMaxSpeed;
    steering.velocity_y_ = (steering.velocity_y_ / steering_vector_length) * kMaxSpeed;
  }

  // Update the orientation
  character_.orientation_ =
      character_.NewOrientation(character_.orientation_, steering.velocity_x_, steering.velocity_y_);
  steering.rotation_ = 0;

  // Update the kinematic
  character_.Update(steering, 1.0f / 60.0f);
}

void Arrive::Update(ALLEGRO_DISPLAY* display, ALLEGRO_FONT* font)
{
  UpdateBodies();
  al_clear_to_color(al_map_rgb(0, 0, 0));
  drawBody(character_, al_map_rgb(255, 0, 0), font);
  drawBody(target_, al_map_rgb(0, 255, 0), font);
  al_flip_display();
}
} // namespace aifg