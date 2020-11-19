#ifndef STACK2_HPP
#define STACK2_HPP

#include <cassert>
#include <deque>
#include <iostream>
#include <string>

#include "stack1.hpp"

namespace chapter {
namespace basics {

template<>
class Stack<std::string>;
template<>
std::ostream& operator<< (std::ostream&, Stack<std::string>const&);

/**
 * Specialized version of Stack meant to be used by the strings.
 */
template<>
class Stack<std::string> {
   public:
    void push(std::string const& elem);
    void pop();
    std::string const& top() const;
    bool empty() const {
        return elems.empty();
    }

    /**
     * E.g. if we would not implement this function but called it we would end up with undefined reference.
     * The version from Stack<T> would NOT be taken.
     */ 
    void printOn(std::ostream& strm) const {
        for (std::string const& elem: elems) {
            strm << elem << " ";
        }
    }

    private:

    friend std::ostream& operator<< <std::string> (std::ostream& strm, Stack<std::string>const& s) {
        s.printOn(strm);
        return strm;
    }

    std::deque<std::string> elems;
};

void Stack<std::string>::push(std::string const& elem) {
    std::cout << "Calling push from string specialization" << std::endl;
    elems.push_back(elem);
}

void Stack<std::string>::pop() {
    std::cout << "Calling pop from string specialization" << std::endl;
    assert(!elems.empty());
    elems.pop_back();
}

std::string const& Stack<std::string>::top() const {
    std::cout << "Calling top from string specialization" << std::endl;
    assert(!elems.empty());
    return elems.back();
}

} // basics
} // chapter

#endif