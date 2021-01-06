#ifndef ISPRIME14_HPP
#define ISPRIME14_HPP

#include <iostream>
#include <string>

namespace basics {

constexpr bool IsPrime14(unsigned p) {
  for (unsigned int d = 2; d <= p/2; d++) {
    if (p % d == 0) {
      return false;
    }
  }

  return p > 1;
}

} // basics

#endif