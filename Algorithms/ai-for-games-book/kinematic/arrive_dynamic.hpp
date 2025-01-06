#pragma once

#include <string>

#include "kinematic_data.hpp"

struct ALLEGRO_DISPLAY;
struct ALLEGRO_FONT;

namespace aifg
{
class ArriveDynamic
{
public:
  ArriveDynamic();
  ArriveDynamic(const ArriveDynamic&) = default;
  ArriveDynamic& operator=(const ArriveDynamic&) = default;
  ArriveDynamic(ArriveDynamic&&) = default;
  ArriveDynamic& operator=(ArriveDynamic&&) = default;

  const inline std::string Name() const { return "Arrive Dynamic"; }

  void Update(ALLEGRO_DISPLAY* display, ALLEGRO_FONT* font);

private:
  void UpdateBodies();

  KinematicBody character_;
  KinematicBody target_;
};
} // namespace aifg
