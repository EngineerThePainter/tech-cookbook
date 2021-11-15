#ifndef ADVANCE2_HPP
#define ADVANCE2_HPP

#include "enableif.hpp"

#include "traits/iterator_traits.hpp"

namespace typeoverload {

template<typename Iterator, typename Distance>
EnableIf<traits::IsRandomAccessIterator<Iterator>>
advanceIter(Iterator& x, Distance n) {
  x += n;
}

template<typename Iterator, typename Distance>
EnableIf<traits::IsBidirectionalIterator<Iterator> && !traits::IsRandomAccess<Iterator>>
advanceIter(Iterator& x, Distance n) {
  if (n > 0) {
    for (; n > 0; ++x, --n) {}
  } else {
    for (; n < 0; --x, ++n) {}
  }
}

// Implementation for other types of iterators
template<typename Iterator, typename Distance>
EnableIf<!traits::IsBidirectionalIterator<Iterator>>
advanceIter(Iterator& x, Distance n) {
  if (n < 0) {
    throw "advanceIter(): invalid iterator category for negative n";
  }
  while (n > 0) {
    ++x;
    --n;
  }
}

}; // namespace typeoverload

#endif // ADVANCE2_HPP