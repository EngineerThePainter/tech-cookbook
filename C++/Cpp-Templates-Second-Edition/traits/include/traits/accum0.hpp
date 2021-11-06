#ifndef ACCUM0_HPP
#define ACCUM0_HPP

#include <iterator>

namespace traits {

template<typename Iter>
auto accum0(Iter beg, Iter end) {
  using VT = typename std::iterator_traits<Iter>::value_type;
  VT total {};
  while(beg != end) {
    total += *beg;
    ++beg;
  }
  return total;
}

} // namespace traits

#endif // ACCUM0_HPP