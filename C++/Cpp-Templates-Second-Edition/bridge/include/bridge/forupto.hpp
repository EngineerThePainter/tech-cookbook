#ifndef BRIDGE_FORUPTO_HPP
#define BRIDGE_FORUPTO_HPP

#include <functional>
#include <iostream>

#include "functionptr.hpp"
#include "functionptr-cpinv.hpp"
#include "functionptr-init.hpp"

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

void forUpToFunctionPointer(int n, FunctionPtr<void(int)> f) {
  for (int i = 0; i != n; ++i) {
    f(i);
  }
}

void printInt(int i) {
  std::cout << i << ' ';
}

} // namespace poly

#endif // BRIDGE_FORUPTO_HPP