#include <string>

struct ALLEGRO_DISPLAY;

namespace aifg
{
class Seek
{
public:
  Seek() = default;
  Seek(const Seek&) = default;
  Seek& operator=(const Seek&) = default;
  Seek(Seek&&) = default;
  Seek& operator=(Seek&&) = default;

  const inline std::string Name() const { return "Seek"; }

  void Update(ALLEGRO_DISPLAY* display);
};
} // namespace aifg