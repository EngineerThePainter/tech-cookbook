#pragma once

#include <string>

#include "kinematic_data.hpp"

struct ALLEGRO_DISPLAY;
struct ALLEGRO_FONT;

namespace aifg
{
class SeekDynamic
{
public:
  SeekDynamic();
  SeekDynamic(SeekDynamic&) = default;
  SeekDynamic& operator=(const SeekDynamic&) = default;
  SeekDynamic(SeekDynamic&&) = default;
  SeekDynamic& operator=(SeekDynamic&&) = default;

  const inline std::string Name() const { return "Seek Dynamic"; }

  void Update(ALLEGRO_DISPLAY* display, ALLEGRO_FONT* font);

private:
  void UpdateBodies();

  KinematicBody character_;
  KinematicBody target_;
};
} // namespace aifg
