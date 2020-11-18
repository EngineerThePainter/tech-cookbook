#ifndef STACK3_HPP
#define STACK3_HPP

#include <cassert>
#include <iostream>
#include <vector>

namespace chapter {
namespace basics {

template<typename T, typename Cont = std::vector<T>>
class StackDefaultArg {
  public:
    void push(T const& elem);
    void pop();
    T const& top() const;
    bool empty() const {
        return elems.empty();
    }

    private:
    Cont elems;
};

template<typename T, typename Cont>
void StackDefaultArg<T, Cont>::push(T const& elem) {
    std::cout << "Calling push from default arguments" << std::endl;
    elems.push_back(elem);
}

template<typename T, typename Cont>
void StackDefaultArg<T, Cont>::pop() {
    std::cout << "Calling pop from default arguments" << std::endl;
    assert(!elems.empty());
    elems.pop_back();
}

template<typename T, typename Cont>
T const& StackDefaultArg<T, Cont>::top() const {
    std::cout << "Calling top from default arguments" << std::endl;
    assert(!elems.empty());
    return elems.back();
}

}
}

#endif