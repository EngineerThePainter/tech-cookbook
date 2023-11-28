#include "allegro.hpp"

int main(int argc, char** argv)
{
  aifg::Allegro allegro(800, 600, "AI for Games");

  bool finished = false;
  while (!finished) {
    ALLEGRO_EVENT event;
    al_wait_for_event(allegro.EventQueue(), &event);

    switch (event.type) {
    case ALLEGRO_EVENT_TIMER:
      al_clear_to_color(al_map_rgb(0, 0, 0));
      al_flip_display();
      break;
    case ALLEGRO_EVENT_DISPLAY_CLOSE:
      finished = true;
      break;
    }
  }

  return 0;
}