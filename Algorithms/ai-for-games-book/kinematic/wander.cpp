#include "wander.hpp"

#include <cmath>

#include "allegro.hpp"
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>

#include "kinematic_common.hpp"

#include <loguru/loguru.hpp>

namespace aifg
{
Wander::Wander() : character_({SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2}, {}, 0.0f, 0.0f), distribution_(-1, 1)
{
  character_.orientation_ = distribution_(generator_);
}

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
  KinematicSteering steering;
  if (character_.position_.X() < 0 || character_.position_.X() > SCREEN_WIDTH || character_.position_.Y() < 0 ||
      character_.position_.Y() > SCREEN_HEIGHT) {
    character_.ResetToCenter();
  } else {
    steering.linear_velocity_.X(kMaxSpeed * sin(character_.orientation_));
    steering.linear_velocity_.Y(kMaxSpeed * cos(character_.orientation_));

    steering.angular_velocity_ = kMaxRotation * distribution_(generator_);
  }

  character_.Update(steering, kTime);
}

} // namespace aifg