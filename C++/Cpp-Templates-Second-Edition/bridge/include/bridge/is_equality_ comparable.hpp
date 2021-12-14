#ifndef BRIDGE_ISEQUALITYCOMPARABLE_HPP
#define BRIDGE_ISEQUALITYCOMPARABLE_HPP

#include <utility>
#include <type_traits>

namespace bridge {

template<typename T>
class IsEqualityComparable {
  private:
  // Test convertability of == and !== to bool
  static void* conv(bool);
  template<typename U>
  static std::true_type test(decltype(conv(std::declval<U const&>() == std::declval<U const&>())),
  decltype(conv(!(std::declval<U const&>() == std::declval<U const&>()))));

  // Fallback scenario
  template<typename U>
  static std::false_type test(...);

  public:
  static constexpr bool value = decltype(test<T>(nullptr, nullptr))::value;
};

} // namespace bridge

#endif // BRIDGE_ISEQUALITYCOMPARABLE_HPP