#ifndef ACCUM2_HPP
#define ACCUM2_HPP

#include "accumtraits2.hpp"

namespace traits {

template <typename T>
auto accum2(T const* beg, T const* end) {
  using AccT = typename AccumulationTraits<T>::AccT;
  AccT total{}; // assume this actually creates a zero value
  while (beg != end) {
    total += *beg;
    ++beg;
  }
  return total;
}

} // namespace traits

#endif // ACCUM2_HPP