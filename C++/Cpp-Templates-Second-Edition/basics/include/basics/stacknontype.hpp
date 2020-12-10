#ifndef STACK_NON_TYPE_HPP
#define STACK_NON_TYPE_HPP

#include <array>
#include <cassert>

namespace basics {

template<typename T, std::size_t Maxsize>
class StackNonType {

public:
    StackNonType();
    void push(T const& elem);
    void pop();
    T const& top() const;
    bool empty() const {
        return numElems == 0;
    }
    std::size_t size() const {
        return numElems;
    }

private:
    std::array<T, Maxsize> elems;
    std::size_t numElems;
};

template<typename T, std::size_t Maxsize>
StackNonType<T, Maxsize>::StackNonType()
: numElems(0)
{
}

template<typename T, std::size_t Maxsize>
void StackNonType<T, Maxsize>::push(T const& elem) {
    assert(numElems < Maxsize);
    elems[numElems] = elem;
    ++numElems;
}

template<typename T, std::size_t Maxsize>
void StackNonType<T, Maxsize>::pop() {
    assert(!elems.empty());
    --numElems;
}

template<typename T, std::size_t Maxsize>
T const& StackNonType<T, Maxsize>::top() const {
    assert(!elems.empty());
    return elems[numElems - 1];
}

template<auto Val, typename T = decltype(Val)>
void printPassedX(T x) {
    std::cout << "It's " << x << " for Val: " << Val << std::endl;
}

}

#endif // STACK_NON_TYPE_HPP