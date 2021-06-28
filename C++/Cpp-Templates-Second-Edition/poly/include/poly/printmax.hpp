#ifndef PRINT_MAX_HPP
#define PRINT_MAX_HPP

#include <algorithm>
#include <iostream>

namespace poly {

template <typename T>
void print_max(T const& coll) {
  auto pos = std::max_element(coll.begin(), coll.end());

  if (pos != coll.end()) {
    std::cout << *pos << "\n";
  } else {
    std::cout << "empty\n";
  }
}

} // namespace poly

#endif // PRINT_MAX_HPP