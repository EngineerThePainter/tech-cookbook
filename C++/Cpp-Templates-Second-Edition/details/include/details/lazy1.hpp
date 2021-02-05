#ifndef LAZY1_HPP
#define LAZY1_HPP

#include <iostream>

namespace details {

template<typename T>
class Safe {
};

template<int N>
class Danger {
  int arr[N]; // OK here, BUT will fail for N <= 0 
};

template<typename T, int N>
class Tricky {
  public:
  void noBodyHere(Safe<T> = 3); // OK, until usage of default value results in an error

  void inclass() {
    Danger<N> noBoomYet; // OK, until inclass is with N<=0
  }

  struct Nested {
    Danger<N> phew; // OK, until Nested is with N<=0
  };

  /**
   * Due to anonymous union:
   * OK until Tricky is instantiated with N<=0
   */ 
  union {
    Danger<N> anonymous;
    int align;
  };

  void unsafe(T (*p)[N]); // OK until Tricky is instantiated with N<=0

  // void error() {
  //   Danger<-1> boom; // always ERROR (which not all compilers detect), GCC 7.5.0 found it
  // }
};

} // details

#endif