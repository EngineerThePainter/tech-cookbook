#ifndef DEFINITIONS3_HPP
#define DEFINITIONS3_HPP

namespace details {

template<typename T>
class List {
  public:
  List() = default;

  /**
   * Member class template without definition
   */
  template<typename U>
  class Handle;

  /**
   * Member function template (constructor)
   */
  template<typename U>
  List (List<U> const&);

  /**
   * Member variable template (>=C++14)
   */
  template<typename U>
  static U zero;
};

/**
 * Out of class member class template definition
 */
template<typename T>
template<typename U>
class List<T>::Handle {
};

/**
 * Out of class member function template definition
 */
template<typename T>
template<typename T2>
List<T>::List (List<T2> const& b) {
}

/**
 * Out of class static data member template definition
 */
template<typename T>
template<typename U>
U List<T>::zero = 0;

} // details

#endif