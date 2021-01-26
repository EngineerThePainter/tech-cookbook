#ifndef EVILSPECIALIZATION_HPP
#define EVILSPECIALIZATION_HPP

#include <iostream>

namespace details {

/**
 * Don't use this code it won't compile due to uncertain nature of x
 */ 
template<typename T>
class Trap {
  public:
  enum { x }; // x is not a type here
};

template<typename T>
class Victim {
  public:
  int y;
  void poof() {
    Trap<T>::x * y; // Declaration of multiplication?
  }
};

template<>
class Trap<void> {
  public:
  using x = int; // x is a type here
};

} // details

#endif