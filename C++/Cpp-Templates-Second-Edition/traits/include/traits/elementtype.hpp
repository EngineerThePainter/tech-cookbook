#ifndef ELEMENT_TYPE_HPP
#define ELEMENT_TYPE_HPP

#include <iostream>
#include <list>
#include <typeinfo>
#include <vector>

namespace traits {

template<typename T>
struct ElementT;

template<typename T>
struct ElementT<std::vector<T>> {
  using Type = T;
};

template<typename T>
struct ElementT<std::list<T>> {
  using Type = T;
};

template<typename T, std::size_t N>
struct ElementT<T[N]> {
  using Type = T;
};

template<typename T>
struct ElementT<T[]> {
  using Type = T;
};

template<typename T>
void printElementType(T const& c) {
  std::cout << "Container of " << typeid(typename ElementT<T>::Type).name() << " elements.\n";
}

} // namespace traits

#endif // ELEMENT_TYPE_HPP