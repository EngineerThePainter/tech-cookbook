#ifndef IS_SAME_DEMO_HPP
#define IS_SAME_DEMO_HPP

#include "issame.hpp"
#include <iostream>

namespace traits {
  template<typename T>
  void fooImpl(T, TrueType) {
    std::cout << "fooImpl(T, TrueType) for int called\n";
  }

  template<typename T>
  void fooImpl(T, FalseType) {
    std::cout << "fooImpl(T, FalseType) for other type called\n";
  }

  template<typename T>
  void fooImpl(T t) {
    fooImpl(t, IsSameT<T,int>{}); // choose impl, depending on whether T is int
  }
}

#endif // IS_SAME_DEMO_HPP