#include "seek_dynamic.hpp"

#include <cmath>

#include "allegro.hpp"
#include "kinematic_common.hpp"

#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>

namespace aifg
{

SeekDynamic::SeekDynamic()
    : character_(SCREEN_WIDTH * 0.25, SCREEN_HEIGHT * 0.75, 0, 0, 0, 0),
      target_(SCREEN_WIDTH * 0.85, SCREEN_HEIGHT * 0.1, 0, 0, 0, 0)
{
}

void SeekDynamic::Update(ALLEGRO_DISPLAY* display, ALLEGRO_FONT* font)
{
  UpdateBodies();
  al_clear_to_color(al_map_rgb(0, 0, 0));
  drawMovingBody(target_, al_map_rgb(255, 0, 0), font);
  drawMovingBody(character_, al_map_rgb(0, 255, 0), font);
  al_flip_display();
}

void SeekDynamic::UpdateBodies()
{
  // Reset positions
  if (character_.position_x_ == target_.position_x_ && character_.position_y_ == target_.position_y_) {
    character_.ResetToCenter();
  }
  KinematicSteering steering;
  // Direction to target
  steering.linear_velocity_x_ = target_.position_x_ - character_.position_x_;
  steering.linear_velocity_y_ = target_.position_y_ - character_.position_y_;

  // Set full acceleration along this direction
  float steering_vector_length = sqrt(steering.linear_velocity_x_ * steering.linear_velocity_x_ +
                                      steering.linear_velocity_y_ * steering.linear_velocity_y_);
  steering.linear_velocity_x_ = (steering.linear_velocity_x_ / steering_vector_length) * kMaxAcceleration;
  steering.linear_velocity_y_ = (steering.linear_velocity_y_ / steering_vector_length) * kMaxAcceleration;

  character_.Update(steering, 1.0f / 60.f);

  KinematicSteering target_steering;
  target_steering.linear_velocity_x_ = 0.0f;
  target_steering.linear_velocity_y_ = 1.0f * (kMaxSpeed / 4);
  target_.Update(target_steering, 1.0f / 60.0f);
}

} // namespace aifg
