#include "seek.hpp"

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

namespace aifg
{
void Seek::Update(ALLEGRO_DISPLAY* display)
{
  al_clear_to_color(al_map_rgb(0, 0, 0));
  al_draw_filled_circle(400, 300, 10, al_map_rgb(255, 255, 255));
  al_flip_display();
}
} // namespace aifg
