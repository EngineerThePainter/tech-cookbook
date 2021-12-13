#ifndef BRIDGE_FORUPTO1_HPP
#define BRIDGE_FORUPTO1_HPP

#include <functional>
#include <iostream>

namespace bridge {

template<typename F>
void forUpTo(int n, F f) {
  for (int i = 0; i != n; ++i) {
    f(i);
  }
}

void forUpToFunctional(int n, std::function<void(int)> f) {
  for (int i = 0; i != n; ++i) {
    f(i);
  }
}

void printInt(int i) {
  std::cout << i << ' ';
}

} // namespace poly

#endif // BRIDGE_FORUPTO1_HPP