#ifndef ANGLEBRACKETHACK_HPP
#define ANGLEBRACKETHACK_HPP

#include <iostream>

namespace details {

template<int I> struct XX {
  static int const num = 2;
};

template<> struct XX<0> {
  typedef int num;
};

template<typename T> struct YY {
  static int const num = 3;
};

static int const num = 4;

} // details

#endif