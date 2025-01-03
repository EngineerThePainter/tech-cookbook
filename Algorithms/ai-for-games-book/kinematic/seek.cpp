#include "seek.hpp"

#include <cmath>

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>

#include "kinematic_common.hpp"
#include "vector2d.hpp"

namespace aifg
{

Seek::Seek() : character_({600, 500}, {}, 0, 0), target_({200, 100}, {}, 0, 0) {}

void Seek::Update(ALLEGRO_DISPLAY* display, ALLEGRO_FONT* font)
{
  UpdateBodies();
  al_clear_to_color(al_map_rgb(0, 0, 0));
  drawMovingBody(target_, al_map_rgb(255, 0, 0), font);
  drawMovingBody(character_, al_map_rgb(0, 255, 0), font);
  al_flip_display();
}

void Seek::UpdateBodies()
{
  // Base velocity is set to the target position
  KinematicSteering steering;
  steering.linear_velocity_ = target_.position_ - character_.position_;

  // Normalize the velocity to the maximum speed
  steering.linear_velocity_.NormalizeTo(kMaxSpeed);

  // Update the orientation
  character_.orientation_ = character_.NewOrientation(character_.orientation_, steering.linear_velocity_);
  steering.angular_velocity_ = 0;

  // Update the kinematic
  character_.Update(steering, 1.0f / 60.0f);
}

} // namespace aifg
