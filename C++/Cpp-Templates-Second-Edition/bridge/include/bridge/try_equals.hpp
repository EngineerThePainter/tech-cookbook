#ifndef BRIDGE_TRYEQUALS_HPP
#define BRIDGE_TRYEQUALS_HPP

#include <exception>
#include "is_equality_ comparable.hpp"

namespace bridge {

template<typename T, bool EqComparable = IsEqualityComparable<T>::value>
struct TryEquals
{
  static bool equals(T const& x1, T const& x2) {
    return x1 == x2;
  }
};

class NotEqualityComparable : public std::exception {

};

template<typename T>
struct TryEquals<T, false>
{
  static bool equals(T const&, T const&) {
    throw NotEqualityComparable();
  }
};


} // namespace bridge

#endif // BRIDGE_TRYEQUALS_HPP