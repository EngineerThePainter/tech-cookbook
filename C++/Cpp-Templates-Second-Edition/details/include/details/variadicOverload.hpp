#ifndef VAR_OVERLOAD_HPP
#define VAR_OVERLOAD_HPP

#include <iostream>

namespace details
{

template<typename T>
int fVar(T*) {
  return 1;
}

template<typename... Ts>
int fVar(Ts...) {
  return 2;
}

template<typename... Ts>
int fVar(Ts*...) {
  return 3;
}

} // namespace details

#endif // VAR_OVERLOAD_HPP