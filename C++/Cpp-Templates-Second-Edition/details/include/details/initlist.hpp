#ifndef INITLIST_HPP
#define INITLIST_HPP

#include <initializer_list>
#include <iostream>
#include <typeinfo>

namespace details {

template<typename T> void f(std::initializer_list<T> list) {
  std::cout<< typeid(T).name();
}

} // namespace details

#endif // INITLIST_HPP