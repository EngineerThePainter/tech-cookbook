#ifndef ACCUM5_HPP
#define ACCUM5_HPP

#include "accumtraits3.hpp"

namespace traits {

template <typename T, typename AT = AccumulationTraits3<T>>
auto accum5(T const* beg, T const* end) {
  typename AT::AccT total = AT::zero; // init by trait value
  while (beg != end) {
    total += *beg;
    ++beg;
  }
  return total;
}

} // namespace traits

#endif // ACCUM5_HPP