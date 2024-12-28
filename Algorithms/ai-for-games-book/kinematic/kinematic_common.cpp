#include <cmath>

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>

#include "kinematic_data.hpp"

namespace aifg
{
void drawMovingBody(const KinematicBody& body, const ALLEGRO_COLOR& color, const ALLEGRO_FONT* font)
{
  al_set_blender(ALLEGRO_ADD, ALLEGRO_ALPHA, ALLEGRO_INVERSE_ALPHA);
  al_draw_filled_circle(body.position_x_, body.position_y_, 10, color);
  float x = body.position_x_ + sin(body.orientation_) * 20;
  float y = body.position_y_ + cos(body.orientation_) * 20;

  float velocity_length = sqrt(body.velocity_x_ * body.velocity_x_ + body.velocity_y_ * body.velocity_y_);
  float velocity_x = (body.velocity_x_ / velocity_length) * 30;
  float velocity_y = (body.velocity_y_ / velocity_length) * 30;

  al_draw_line(body.position_x_, body.position_y_, body.position_x_ + velocity_x, body.position_y_ + velocity_y,
               al_map_rgb(255, 0, 255), 2);
  al_draw_line(body.position_x_, body.position_y_, x, y, al_map_rgb(255, 255, 255), 2);

  al_draw_text(font, al_map_rgb(255, 255, 255), 0, 550, 0, "white - orientation");
  al_draw_text(font, al_map_rgb(255, 255, 255), 0, 570, 0, "purple - velocity direction");

  al_set_blender(ALLEGRO_ADD, ALLEGRO_ONE, ALLEGRO_INVERSE_ALPHA);
}
} // namespace aifg