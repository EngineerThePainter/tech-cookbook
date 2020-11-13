#ifndef STACK1_HPP
#define STACK1_HPP

#include <cassert>
#include <iostream>
#include <ostream>
#include <vector>

namespace chapter {
namespace basics {

template<typename T>
class Stack {
    public:
    void push(T const& elem);
    void pop();
    T const& top() const;
    bool empty() const {
        return elems.empty();
    }
    
    void printOn(std::ostream& strm) const {
        for (T const& elem: elems) {
            strm << elem << " ";
        }
    }

    private:
    std::vector<T> elems;
};

template<typename T>
void Stack<T>::push(T const& elem) {
    elems.push_back(elem);
}

template<typename T>
void Stack<T>::pop() {
    assert(!elems.empty());
    elems.pop_back();
}

template<typename T>
T const& Stack<T>::top() const {
    assert(!elems.empty());
    return elems.back();
}

} // namespace basics
} // namespace chapter

#endif
