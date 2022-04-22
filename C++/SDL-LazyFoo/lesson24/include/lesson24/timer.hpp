#ifndef lesson24_timer_HPP
#define lesson24_timer_HPP

#include <SDL2/SDL.h>

namespace sdl_lazyfoo
{
namespace lesson24
{
class Timer
{
public:
  Timer();
  void Start();
  void Stop();
  void Pause();
  void Unpause();

  Uint32 GetTicks();

  bool IsStarted();
  bool IsPaused();

private:
  Uint32 start_ticks_;
  Uint32 paused_ticks_;

  bool paused_;
  bool started_;
};
} // namespace lesson24
} // namespace sdl_lazyfoo

#endif // lesson24_HPP