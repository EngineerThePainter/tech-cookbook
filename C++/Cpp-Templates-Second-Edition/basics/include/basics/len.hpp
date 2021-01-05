#ifndef LEN_HPP
#define LEN_HPP

#include <iostream>

namespace basics {

// Number of elements in a raw array
template<typename T, unsigned N>
std::size_t len(T(&)[N]) {
  std::cout << "Calling std::size_t len(T(&)[N])" << std::endl;
  return N;
}

// Number of elements for a type having size_type
template<typename T>
typename T::size_type len(T const& t) {
  std::cout << "Calling typename T::size_type len(T const& t)" << std::endl;
  return t.size();
}

// Fallback for the types that will not match any of the tempates above
// For production approach using some static assertion/throw exception might be more useful
std::size_t len(...) {
  std::cout << "Calling std::size_t len(...)" << std::endl;
  return 0;
}

} // basics

#endif