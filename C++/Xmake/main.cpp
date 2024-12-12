#include <iostream>

#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>

#include <loguru/loguru.hpp>

int main()
{
  LOG_F(INFO, "Initializing");
  // Initialize Allegro
  if (!al_init())
  {
    std::cerr << "Failed to initialize Allegro!\n";
    return -1;
  }
  ALLEGRO_DISPLAY *display = al_create_display(800, 600);
  if (!display)
  {
    std::cerr << "Failed to create display!\n";
    return -1;
  }

  // Set the background color and clear the screen
  al_clear_to_color(al_map_rgb(0, 0, 0));

  // Draw a red triangle
  al_draw_triangle(400, 100, 300, 500, 500, 500, al_map_rgb(255, 0, 0), 5.0);

  // Display the output
  al_flip_display();

  // Wait for 5 seconds
  al_rest(5.0);

  // Cleanup
  al_destroy_display(display);

  return 0;
}