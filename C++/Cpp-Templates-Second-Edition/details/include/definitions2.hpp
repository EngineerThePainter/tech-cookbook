#ifndef DEFINITIONS2_HPP
#define DEFINITIONS2_HPP

namespace details {

class Collection {
  public:

  // In class member class template definition
  template<typename T>
  class Node {

  };

  // In class (and implicitly inline) member function template definition
  template<typename T>
  T* alloc() {

  }

  // Member variable template (>=C++14)
  template<typename T>
  static T zero = 0;

  // Member alias template
  template<typename T>
  using NodePtr = Node<T>*;
};

} // details

#endif