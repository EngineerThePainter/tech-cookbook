#ifndef AIFG_KINEMATIC_ARRIVE_HPP
#define AIFG_KINEMATIC_ARRIVE_HPP

#include <string>

struct ALLEGRO_DISPLAY;
struct ALLEGRO_FONT;

namespace aifg
{
class Arrive
{
public:
  Arrive();
  Arrive(const Arrive&) = default;
  Arrive& operator=(const Arrive&) = default;
  Arrive(Arrive&&) = default;
  Arrive& operator=(Arrive&&) = default;

  const inline std::string Name() const { return "Arrive"; }

  void Update(ALLEGRO_DISPLAY* display, ALLEGRO_FONT* font);
};
} // namespace aifg

#endif // !AIFG_KINEMATIC_ARRIVE_HPP