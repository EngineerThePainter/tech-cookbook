#ifndef ISPRIME11_HPP
#define ISPRIME11_HPP

#include <iostream>
#include <string>

namespace basics {

constexpr bool DoIsPrime11(unsigned p, unsigned d) {
  return d!=2 ? (p%d!=0) && DoIsPrime11(p, d-1) : (p%2!=0);
}

constexpr bool IsPrime11(unsigned p) {
  return p < 4 ? !(p<2) : DoIsPrime11(p, p/2);
}

} // basics

#endif