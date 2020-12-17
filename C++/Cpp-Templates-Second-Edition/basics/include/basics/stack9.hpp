#ifndef STACK9_HPP
#define STACK9_HPP

#include <cassert>
#include <deque>
#include <memory>

namespace basics {

/**
 * This is the final version of Stack template from the book.
 */

template<typename T,
  template<typename Elem,
    typename = std::allocator<Elem>> // Allocator omit mentioned in the stack8decl.hpp
    class Cont = std::deque>
class Stack9 {
  public:
  void push(T const&);
  void pop();
  T const& top() const;
  bool empty() const;

  template<typename T2,
    template<typename Elem2,
      typename = std::allocator<Elem2>>
      class Cont2>
  Stack9<T, Cont>& operator= (Stack9<T2, Cont2> const&);

  template<typename, template<typename, typename> class> friend class Stack9;

  private:
  Cont<T> elems;
};

template<typename T, template<typename,typename> class Cont>
void Stack9<T, Cont>::push(T const& elem) {
    elems.push_back(elem);
}

template<typename T, template<typename,typename> class Cont>
void Stack9<T, Cont>::pop() {
    assert(!elems.empty());
    elems.pop_back();
}

template<typename T, template<typename,typename> class Cont>
T const& Stack9<T, Cont>::top() const {
    assert(!elems.empty());
    return elems.back();
}

template<typename T, template<typename,typename> class Cont>
bool Stack9<T, Cont>::empty() const {
  return elems.empty();
}

template<typename T, template<typename,typename> class Cont>
  template<typename T2, template<typename,typename> class Cont2>
  Stack9<T, Cont>& Stack9<T, Cont>::operator= (Stack9<T2, Cont2> const& op2) {
    elems.clear();
    elems.insert(elems.begin(), op2.elems.begin(), op2.elems.end());
    return *this;
  }


} // basics

#endif // STACK7DECL_HPP