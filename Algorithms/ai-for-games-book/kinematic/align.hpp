#pragma once

#include <string>

#include "kinematic_data.hpp"

struct ALLEGRO_DISPLAY;
struct ALLEGRO_FONT;

namespace aifg
{
class Align
{
public:
  Align();
  Align(const Align&) = default;
  Align& operator=(const Align&) = default;
  Align(Align&&) = default;
  Align& operator=(Align&&) = default;

  const inline std::string Name() const { return "Align"; }

  void Update(ALLEGRO_DISPLAY* display, ALLEGRO_FONT* font);

private:
  void UpdateBodies();

  KinematicBody character_;
  KinematicBody target_;
};
} // namespace aifg
