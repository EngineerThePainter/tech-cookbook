#ifndef QFL_ALLEGRO_HPP
#define QFL_ALLEGRO_HPP

#include <exception>
#include <string>

#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>

namespace aifg
{

static constexpr int SCREEN_WIDTH = 800;
static constexpr int SCREEN_HEIGHT = 600;

class AllegroInitializationException : public std::exception
{
public:
  AllegroInitializationException(const std::string& what);
  const char* what() const noexcept override;

private:
  const char* what_;
};

class Allegro
{
public:
  explicit Allegro(const std::string& window_title);
  explicit Allegro(const int screen_width, const int screen_height, const std::string& window_title);
  ~Allegro();

  ALLEGRO_TIMER* Timer() const;
  ALLEGRO_EVENT_QUEUE* EventQueue() const;
  ALLEGRO_DISPLAY* Display() const;
  ALLEGRO_FONT* Font() const;

  const int ScreenWidth() const;
  const int ScreenHeight() const;

private:
  void baseInit();
  void initializeTimer();
  void initializeEventQueue();
  void initializeDisplay(const std::string& window_title, int screen_width = 0, int screen_height = 0);
  void initializeFont();

  ALLEGRO_TIMER* timer_;
  ALLEGRO_EVENT_QUEUE* event_queue_;
  ALLEGRO_DISPLAY* display_;
  ALLEGRO_FONT* font_;
};
} // namespace aifg

#endif
