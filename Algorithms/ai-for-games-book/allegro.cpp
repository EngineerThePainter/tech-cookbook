#include "allegro.hpp"

#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <loguru.hpp>

namespace aifg
{
namespace
{

void must_init_or_throw(bool to_init, const std::string& component)
{
  LOG_F(INFO, "Initializing: %s", component.c_str());
  if (to_init) {
    return;
  }
  LOG_F(ERROR, "Could not initialize: %s", component.c_str());
  throw AllegroInitializationException("Could not initialize: " + component);
}

} // namespace

AllegroInitializationException::AllegroInitializationException(const std::string& what) : what_(what.c_str()) {}
const char* AllegroInitializationException::what() const noexcept { return what_; }

Allegro::Allegro(const std::string& window_title)
{

  baseInit();

  initializeTimer();

  initializeEventQueue();

  initializeDisplay(window_title);

  LOG_F(INFO, "Starting timer");
  al_start_timer(timer_);

  LOG_F(INFO, "Initialization completed");
}

Allegro::Allegro(const int screen_width, const int screen_height, const std::string& window_title)
{

  if (screen_width <= 0 || screen_height <= 0) {
    throw AllegroInitializationException("Screen size must be positive");
  }

  baseInit();

  initializeTimer();

  initializeEventQueue();

  initializeDisplay(window_title, screen_width, screen_height);

  initializeFont();

  LOG_F(INFO, "Starting timer");
  al_start_timer(timer_);

  LOG_F(INFO, "Initialization completed");
}

Allegro::~Allegro()
{

  LOG_F(INFO, "Destroying display");
  al_destroy_display(display_);
  LOG_F(INFO, "Destroying event queue");
  al_destroy_event_queue(event_queue_);
  LOG_F(INFO, "Destroying timer");
  al_destroy_timer(timer_);
  LOG_F(INFO, "Destroying font");
  al_destroy_font(font_);
}

ALLEGRO_TIMER* Allegro::Timer() const { return timer_; }
ALLEGRO_EVENT_QUEUE* Allegro::EventQueue() const { return event_queue_; }
ALLEGRO_DISPLAY* Allegro::Display() const { return display_; }
ALLEGRO_FONT* Allegro::Font() const { return font_; }

const int Allegro::ScreenWidth() const { return al_get_display_width(display_); }
const int Allegro::ScreenHeight() const { return al_get_display_height(display_); }

void Allegro::baseInit()
{
  LOG_F(INFO, "Initialization started");
  must_init_or_throw(al_init(), "allegro core");
  must_init_or_throw(al_install_keyboard(), "keyboard");
  must_init_or_throw(al_install_mouse(), "mouse");
  must_init_or_throw(al_init_image_addon(), "images");
  must_init_or_throw(al_init_primitives_addon(), "primitives");
  must_init_or_throw(al_init_font_addon(), "fonts");
}

void Allegro::initializeTimer()
{
  timer_ = al_create_timer(1.0 / 30.0);
  must_init_or_throw(timer_ != nullptr, "timer");
}

void Allegro::initializeEventQueue()
{
  event_queue_ = al_create_event_queue();
  must_init_or_throw(event_queue_ != nullptr, "event_queue");
}

void Allegro::initializeDisplay(const std::string& window_title, int screen_width, int screen_height)
{
  bool should_be_fullscreen = screen_width <= 0 || screen_height <= 0;

  LOG_F(INFO, "Setting display options");
  al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
  al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST);
  al_set_new_bitmap_flags(ALLEGRO_MIN_LINEAR | ALLEGRO_MAG_LINEAR);

  ALLEGRO_MONITOR_INFO monitor_info;
  al_get_monitor_info(0, &monitor_info);

  if (should_be_fullscreen) {
    LOG_F(INFO, "Creating display based on the monitor size");
    display_ = al_create_display(monitor_info.x2 - monitor_info.x1, monitor_info.y2 - monitor_info.y1);
  } else {
    display_ = al_create_display(screen_width, screen_height);
  }

  must_init_or_throw(display_ != nullptr, "display");
  al_set_window_title(display_, window_title.c_str());

  if (should_be_fullscreen) {
    al_set_display_flag(display_, ALLEGRO_FULLSCREEN_WINDOW, true);
  }

  LOG_F(INFO, "Registering events on queue");
  al_register_event_source(event_queue_, al_get_keyboard_event_source());
  al_register_event_source(event_queue_, al_get_mouse_event_source());
  al_register_event_source(event_queue_, al_get_display_event_source(display_));
  al_register_event_source(event_queue_, al_get_timer_event_source(timer_));

  LOG_F(INFO, "Setting additive blending");
  al_set_blender(ALLEGRO_ADD, ALLEGRO_ONE, ALLEGRO_ONE);
}

void Allegro::initializeFont()
{
  font_ = al_create_builtin_font();
  must_init_or_throw(font_ != nullptr, "font");
}

} // namespace aifg
