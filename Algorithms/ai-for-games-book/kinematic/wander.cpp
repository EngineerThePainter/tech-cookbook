#include "wander.hpp"

#include <cmath>

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>

#include "kinematic_common.hpp"

#include <loguru.hpp>

namespace aifg
{
Wander::Wander() : character_(400, 300, 0, 0, 0.0f, 0.0f), distribution_(-1, 1) {}

void Wander::Update(ALLEGRO_DISPLAY* display, ALLEGRO_FONT* font)
{
  UpdateBody();
  al_clear_to_color(al_map_rgb(0, 0, 0));
  // LOG_F(INFO, "%f %f", character_.position_x_, character_.position_y_);
  drawMovingBody(character_, al_map_rgb(255, 255, 0), font);
  al_flip_display();
}

void Wander::UpdateBody()
{
  KinematicSteeringOutput steering;
  if (character_.position_x_ < 0 || character_.position_x_ > 800 || character_.position_y_ < 0 ||
      character_.position_y_ > 600) {
    character_.ResetToCenter();
  } else {
    steering.velocity_x_ = kMaxSpeed * sin(character_.orientation_);
    steering.velocity_y_ = kMaxSpeed * cos(character_.orientation_);

    steering.rotation_ = kMaxRotation * distribution_(generator_);
  }

  character_.Update(steering, 1.0f / 60.0f);
}

} // namespace aifg