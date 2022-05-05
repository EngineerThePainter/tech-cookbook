#include "lesson28/timer.hpp"

namespace sdl_lazyfoo
{
namespace lesson28
{
Timer::Timer() : start_ticks_(0), paused_ticks_(0), started_(false), paused_(false) {}

void Timer::Start()
{
  started_ = true;
  paused_ = false;

  start_ticks_ = SDL_GetTicks();
  paused_ticks_ = 0;
}

void Timer::Stop()
{
  started_ = false;
  paused_ = false;
  start_ticks_ = 0;
  paused_ticks_ = 0;
}

void Timer::Pause()
{
  if (started_ && !paused_) {
    paused_ = true;
    paused_ticks_ = SDL_GetTicks() - start_ticks_;
    start_ticks_ = 0;
  }
}

void Timer::Unpause()
{
  if (started_ && paused_) {
    paused_ = false;
    start_ticks_ = SDL_GetTicks() - paused_ticks_;
    paused_ticks_ = 0;
  }
}

Uint32 Timer::GetTicks()
{
  Uint32 time = 0;
  if (started_) {
    time = paused_ ? paused_ticks_ : SDL_GetTicks() - start_ticks_;
  }
  return time;
}

bool Timer::IsStarted() { return started_; }

bool Timer::IsPaused() { return paused_ && started_; }
} // namespace lesson28
} // namespace sdl_lazyfoo
