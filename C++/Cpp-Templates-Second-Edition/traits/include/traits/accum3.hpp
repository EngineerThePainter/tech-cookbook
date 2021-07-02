#ifndef ACCUM3_HPP
#define ACCUM3_HPP

#include "accumtraits3.hpp"

namespace traits {

template <typename T>
auto accum3(T const* beg, T const* end) {
  using AccT = typename AccumulationTraits3<T>::AccT;
  AccT total = AccumulationTraits3<T>::zero; // init by trait value
  while (beg != end) {
    total += *beg;
    ++beg;
  }
  return total;
}

} // namespace traits

#endif // ACCUM3_HPP