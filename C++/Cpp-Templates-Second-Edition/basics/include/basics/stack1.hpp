#ifndef STACK1_HPP
#define STACK1_HPP

#include <cassert>
#include <iostream>
#include <ostream>
#include <vector>

namespace basics {

/** Early declaration that will allow for operator<<
 *  to be declared and defined as a friend inside Stack<T>
 */
template<typename T>
class Stack;
template<typename T>
std::ostream& operator<< (std::ostream&, Stack<T>const&);

template<typename T>
class Stack {
    public:
    Stack() = default;
    Stack (T const& elem)
    : elems({elem})
    {
    }

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

    friend std::ostream& operator<< <T> (std::ostream& strm, Stack<T>const& s);

    private:
    std::vector<T> elems;
};

template<typename T>
std::ostream& operator<< (std::ostream& strm, Stack<T>const& s) {
        s.printOn(strm);
        return strm;
}

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

#endif
