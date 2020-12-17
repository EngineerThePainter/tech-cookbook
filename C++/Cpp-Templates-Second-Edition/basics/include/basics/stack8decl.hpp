#ifndef STACK8DECL_HPP
#define STACK8DECL_HPP

#include <cassert>
#include <deque>

namespace basics {

/**
 * Please note: this approach might work only with C++17 code,
 * since the template template argument had to be a template with
 * parameters that match exactly the parameters of the template argument.
 * 
 * std::deque has default template parameter called allocator.
 * 
 * To see how it's omitted, please refer to the Stack9.
 * Will NOT work on the C++17 for clang10
 */
template<typename T,
  template<typename Elem> class Cont = std::deque>
class StackTemplateTemplateParameter {
  public:
  void push(T const&);
  void pop();
  T const& top() const;
  private:
  Cont<T> elems;
};


template<typename T,
  template<typename Elem> class Cont>
void StackTemplateTemplateParameter<T, Cont>::push(T const& elem) {
    elems.push_back(elem);
}

template<typename T,
  template<typename Elem> class Cont>
void StackTemplateTemplateParameter<T, Cont>::pop() {
    assert(!elems.empty());
    elems.pop_back();
}

template<typename T,
  template<typename Elem> class Cont>
T const& StackTemplateTemplateParameter<T, Cont>::top() const {
    assert(!elems.empty());
    return elems.back();
}

} // basics

#endif // STACK7DECL_HPP