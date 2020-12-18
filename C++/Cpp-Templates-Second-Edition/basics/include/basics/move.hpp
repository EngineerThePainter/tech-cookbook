#ifndef MOVE_HPP
#define MOVE_HPP

#include <iostream>
#include <utility>

namespace basics {

struct X {
  int x{0};
};

void g(X&) {
  std::cout << "g() for variable" << std::endl;
}

void g(X const&) {
  std::cout << "g() for constant" << std::endl;
}

void g(X&&) {
  std::cout << "g() for moveable object" << std::endl;
}

template<typename T>
void f(T&& val) {
  g(std::forward<T>(val));
}

} // basics

#endif