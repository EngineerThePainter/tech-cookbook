#ifndef STACKPARTSPEC_HPP
#define STACKPARTSPEC_HPP

#include <iostream>

#include "stack1.hpp"

namespace chapter {
namespace basics {

/**
 * Partial specialization of class Stack<> for pointers
 */ 
template<typename T>
class Stack<T*>
{
public:

    void push(T*);
    // Yes, specialization may provide a different interface.
    T* pop();
    T* top() const;
    bool empty() const {
        return elems.empty();
    }

private:
    std::vector<T*> elems;
};

template<typename T>
void Stack<T*>::push (T* elem) {
    std::cout << "Calling push() from pointer specialization" << std::endl;
    // Appending copy of passed elem
    elems.push_back(elem);
}

template<typename T>
T* Stack<T*>::pop() {
    std::cout << "Calling pop() from pointer specialization" << std::endl;
    assert(!elems.empty());
    T* p = elems.back();
    elems.pop_back();
    return p;
}

template<typename T>
T* Stack<T*>::top() const {
    std::cout << "Calling top() from pointer specialization" << std::endl;
    assert(!elems.empty());
    return elems.back();
}

} // namespace basics
} // namespace chapter

#endif