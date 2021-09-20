#ifndef PLUS2_HPP
#define PLUS2_HPP

#include <utility>

/**
 * declval produces a value of type T without requiring a default constructor (or any other operation)
 */
namespace traits {
  template<typename T1, typename T2>
  struct PlusResultT {
    using Type = decltype(std::declval<T1>() + std::declval<T2>());
  };

  template<typename T1, typename T2>
  using PlusResult2 = typename PlusResultT<T1, T2>::Type;
}

#endif //  PLUS2_HPP