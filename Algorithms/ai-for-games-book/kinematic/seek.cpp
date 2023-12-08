#include "seek.hpp"

#include <cmath>

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>

namespace aifg
{
namespace
{
const float kMaxSpeed = 300.0f;

void drawBody(const KinematicBody& body, const ALLEGRO_COLOR& color)
{
  al_draw_filled_circle(body.position_x_, body.position_y_, 10, color);
  float x = body.position_x_ + sin(body.orientation_) * 20;
  float y = body.position_y_ + cos(body.orientation_) * 20;

  float velocity_length = sqrt(body.velocity_x_ * body.velocity_x_ + body.velocity_y_ * body.velocity_y_);
  float velocity_x = (body.velocity_x_ / velocity_length) * 30;
  float velocity_y = (body.velocity_y_ / velocity_length) * 30;

  al_draw_line(body.position_x_, body.position_y_, body.position_x_ + velocity_x, body.position_y_ + velocity_y,
               al_map_rgb(255, 0, 255), 2);
  al_draw_line(body.position_x_, body.position_y_, x, y, al_map_rgb(255, 255, 255), 2);
}
} // namespace

Seek::Seek() : character(600, 500, 0, 0, 0, 0), target(200, 100, 0, 0, 0, 0) {}

void Seek::UpdateBodies()
{
  // Reset positions
  if (character.position_x_ == target.position_x_ && character.position_y_ == target.position_y_) {
    character.velocity_x_ = 0;
    character.velocity_y_ = 0;
    character.rotation_ = 0;
    character.position_x_ = 600;
    character.position_y_ = 500;
  }

  // Base velocity is set to the target position
  KinematicSteeringOutput steering;
  steering.velocity_x_ = target.position_x_ - character.position_x_;
  steering.velocity_y_ = target.position_y_ - character.position_y_;

  // Normalize the velocity to the maximum speed
  float steering_vector_length =
      sqrt(steering.velocity_x_ * steering.velocity_x_ + steering.velocity_y_ * steering.velocity_y_);
  steering.velocity_x_ = (steering.velocity_x_ / steering_vector_length) * kMaxSpeed;
  steering.velocity_y_ = (steering.velocity_y_ / steering_vector_length) * kMaxSpeed;

  // Update the orientation
  character.orientation_ = character.NewOrientation(character.orientation_, steering.velocity_x_, steering.velocity_y_);
  steering.rotation_ = 0;

  // Update the kinematic
  character.Update(steering, 1.0f / 60.0f);
}

void Seek::Update(ALLEGRO_DISPLAY* display, ALLEGRO_FONT* font)
{
  UpdateBodies();
  al_clear_to_color(al_map_rgb(0, 0, 0));
  al_set_blender(ALLEGRO_ADD, ALLEGRO_ALPHA, ALLEGRO_INVERSE_ALPHA);
  al_draw_text(font, al_map_rgb(255, 255, 255), 0, 550, 0, "white - orientation");
  al_draw_text(font, al_map_rgb(255, 255, 255), 0, 570, 0, "purple - velocity direction");
  drawBody(target, al_map_rgb(255, 0, 0));
  drawBody(character, al_map_rgb(0, 255, 0));
  al_set_blender(ALLEGRO_ADD, ALLEGRO_ONE, ALLEGRO_INVERSE_ALPHA);
  al_flip_display();
}
} // namespace aifg
