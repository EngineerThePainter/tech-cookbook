#ifndef TUPLE_OVERLOAD_HPP
#define TUPLE_OVERLOAD_HPP

#include <iostream>

namespace details
{

template<typename... Ts> class Tuple
{
};

template<typename T>
int fTuple(Tuple<T*>) {
  return 1;
}

template<typename... Ts>
int fTuple(Tuple<Ts...>) {
  return 2;
}

template<typename... Ts>
int fTuple(Tuple<Ts*...>) {
  return 3;
}

} // namespace details

#endif // TUPLE_OVERLOAD_HPP