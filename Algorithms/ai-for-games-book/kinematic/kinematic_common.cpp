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
  al_draw_filled_circle(body.position_.X(), body.position_.Y(), 10, color);
  float x = body.position_.X() + sin(body.orientation_) * 20;
  float y = body.position_.Y() + cos(body.orientation_) * 20;

  float velocity_length = body.velocity_.Length();
  float velocity_x = (body.velocity_.X() / velocity_length) * 30;
  float velocity_y = (body.velocity_.Y() / velocity_length) * 30;

  al_draw_line(body.position_.X(), body.position_.Y(), body.position_.X() + velocity_x, body.position_.Y() + velocity_y,
               al_map_rgb(255, 0, 255), 2);
  al_draw_line(body.position_.X(), body.position_.Y(), x, y, al_map_rgb(255, 255, 255), 2);

  al_draw_text(font, al_map_rgb(255, 255, 255), 0, 550, 0, "white - orientation");
  al_draw_text(font, al_map_rgb(255, 255, 255), 0, 570, 0, "purple - velocity direction");

  al_set_blender(ALLEGRO_ADD, ALLEGRO_ONE, ALLEGRO_INVERSE_ALPHA);
}
} // namespace aifg