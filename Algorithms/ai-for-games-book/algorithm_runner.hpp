#include <concepts>
#include <type_traits>

#include "allegro.hpp"

namespace aifg
{
template <typename T>
concept Algorithm = requires(T t) {
  { t.Name() } -> std::same_as<const std::string>;
  { t.Update(std::declval<ALLEGRO_DISPLAY*>(), std::declval<ALLEGRO_FONT*>()) } -> std::same_as<void>;
};

template <Algorithm T> class AlgorithmRunner
{
public:
  AlgorithmRunner(const T& algorithm)
      : algorithm_(algorithm), finished_(false), allegro_(SCREEN_WIDTH, SCREEN_HEIGHT, algorithm_.Name())
  {
  }
  AlgorithmRunner(const AlgorithmRunner&) = delete;
  AlgorithmRunner& operator=(const AlgorithmRunner&) = delete;
  AlgorithmRunner(AlgorithmRunner&&) = delete;
  AlgorithmRunner& operator=(AlgorithmRunner&&) = delete;

  void run()
  {
    ALLEGRO_EVENT event;
    while (!finished_) {
      al_wait_for_event(allegro_.EventQueue(), &event);
      switch (event.type) {
      case ALLEGRO_EVENT_TIMER:
        algorithm_.Update(allegro_.Display(), allegro_.Font());
        break;
      case ALLEGRO_EVENT_DISPLAY_CLOSE:
        finished_ = true;
        break;
      }
    }
  }

private:
  T algorithm_;
  bool finished_;
  Allegro allegro_;
};
} // namespace aifg