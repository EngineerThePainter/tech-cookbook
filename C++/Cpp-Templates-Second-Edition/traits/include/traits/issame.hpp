#ifndef IS_SAME_HPP
#define IS_SAME_HPP

#include "boolconstant.hpp"

namespace traits {
  template<typename T1, typename T2>
  struct IsSameT : FalseType
  {
  };
  
  template<typename T>
  struct IsSameT<T, T> : TrueType
  {
  };
}

#endif //  IS_SAME_HPP