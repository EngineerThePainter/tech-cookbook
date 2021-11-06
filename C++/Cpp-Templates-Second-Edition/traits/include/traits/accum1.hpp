#ifndef ACCUM_HPP
#define ACCUM_HPP

namespace traits {

template <typename T>
T accum(T const* beg, T const* end) {
  T total{}; // assume this actually creates a zero value
  while (beg != end) {
    total += *beg;
    ++beg;
  }
  return total;
}

} // namespace traits

#endif // ACCUM_HPP