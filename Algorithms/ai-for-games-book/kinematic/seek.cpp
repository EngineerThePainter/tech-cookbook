#include "seek.hpp"

#include <cmath>

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

#include "kinematic_data.hpp"

namespace aifg
{
namespace
{
const float kMaxSpeed = 100.0f;

KinematicBody character(600, 500, 0, 0, 0, 0);
KinematicBody target(200, 100, 0, 0, 0, 0);

void drawBody(const KinematicBody& body, const ALLEGRO_COLOR& color)
{
  al_draw_filled_circle(body.position_x_, body.position_y_, 10, color);
}
} // namespace

void Seek::Update(ALLEGRO_DISPLAY* display)
{
  if (character.position_x_ == target.position_x_ && character.position_y_ == target.position_y_) {
    character.velocity_x_ = 0;
    character.velocity_y_ = 0;
    character.rotation_ = 0;
    character.position_x_ = 600;
    character.position_y_ = 500;
  }

  KinematicSteeringOutput steering;
  steering.velocity_x_ = target.position_x_ - character.position_x_;
  steering.velocity_y_ = target.position_y_ - character.position_y_;

  float steering_vector_length =
      sqrt(steering.velocity_x_ * steering.velocity_x_ + steering.velocity_y_ * steering.velocity_y_);
  steering.velocity_x_ = (steering.velocity_x_ / steering_vector_length) * kMaxSpeed;
  steering.velocity_y_ = (steering.velocity_y_ / steering_vector_length) * kMaxSpeed;

  character.orientation_ = character.NewOrientation(character.orientation_, steering.velocity_x_, steering.velocity_y_);
  steering.rotation_ = 0;

  character.Update(steering, 1.0f / 60.0f);

  al_clear_to_color(al_map_rgb(0, 0, 0));
  drawBody(character, al_map_rgb(0, 255, 0));
  drawBody(target, al_map_rgb(255, 0, 0));
  al_flip_display();
}
} // namespace aifg
