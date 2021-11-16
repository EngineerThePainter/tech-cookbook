#ifndef ADVANCE3_HPP
#define ADVANCE3_HPP

#include "enableif.hpp"

#include "traits/iterator_traits.hpp"

namespace typeoverload {

/**
 * @brief Implementation of the same functionality like in the advance2.hpp,
 * but using constexpr if
 */

template<typename Iterator, typename Distance>
void advanceIter(Iterator& x, Distance n) {
  if constexpr(traits::IsRandomAccessIterator<Iterator>) {
    x += n;
  }
  else if constexpr(traits::IsBidirectionalIterator<Iterator>) {
    if (n > 0) {
      for (; n > 0; ++x, --n) {}
    } else {
      for (; n < 0; --x, ++n) {}
    }
  }
  else {
    if (n < 0) {
      throw "advance3.hpp advanceIter(): invalid iterator category for negative n";
    }
    while (n > 0) {
      ++x;
      --n;
    }
  }
}

}; // namespace typeoverload

#endif // ADVANCE3_HPP