#ifndef TYPEOVERLOAD_MIN2_HPP
#define TYPEOVERLOAD_MIN2_HPP

#include <type_traits>

#include "enableif.hpp"
#include "lessresult.hpp"

namespace typeoverload {

template<typename T>
EnableIf<std::is_convertible_v<LessResult<T const&, T const&>, bool>, T const&>
min(T const& x, T const& y) {
  if (y < x) {
    return y;
  }
  return x;
};

}; // namespace typeoverload

#endif // TYPEOVERLOAD_MIN2_HPP