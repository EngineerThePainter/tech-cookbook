#ifndef SIZEOF_HPP
#define SIZEOF_HPP

#include<cstddef>

namespace traits {

template<typename T>
struct TypeSize {
  static std::size_t const value = sizeof(T);
};

} // namespace traits

#endif // SIZEOF_HPP