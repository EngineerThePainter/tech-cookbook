#ifndef ACCUM6_HPP
#define ACCUM6_HPP

#include "accumtraits4.hpp"
#include "sumpolicy1.hpp"

namespace traits {

template<typename T, typename Policy = SumPolicy, typename Traits = AccumulationTraits4<T>>
auto accum6(T const* beg, T const* end) {
  using AccT = typename Traits::AccT;
  AccT total = Traits::zero();
  while(beg != end) {
    Policy::accumulate(total, *beg);
    ++beg;
  }
  return total;
}

} // namespace traits

#endif // ACCUM6_HPP