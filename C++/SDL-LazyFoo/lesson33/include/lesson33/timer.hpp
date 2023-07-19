#ifndef lesson33_timer_HPP
#define lesson33_timer_HPP

#include <SDL2/SDL.h>

namespace sdl_lazyfoo
{
namespace lesson33
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
} // namespace lesson33
} // namespace sdl_lazyfoo

#endif // lesson33_HPP