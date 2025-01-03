#ifndef AIFG_KINEMATIC_WANDER_HPP
#define AIFG_KINEMATIC_WANDER_HPP

#include <random>
#include <string>

#include "kinematic_data.hpp"

struct ALLEGRO_DISPLAY;
struct ALLEGRO_FONT;

namespace aifg
{
class Wander
{
public:
  Wander();
  Wander(const Wander&) = default;
  Wander& operator=(const Wander&) = default;
  Wander(Wander&&) = default;
  Wander& operator=(Wander&&) = default;

  const inline std::string Name() const { return "Wander"; }
  x_ void Update(ALLEGRO_DISPLAY* display, ALLEGRO_FONT* font);

private:
  void UpdateBody();
  KinematicBody character_;
  std::uniform_real_distribution<float> distribution_;
  std::default_random_engine generator_;
};
} // namespace aifg

#endif // AIFG_KINEMATIC_WANDER_HPP