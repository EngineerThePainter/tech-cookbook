#ifndef STACK_TEMPLATE_PARAMETER_AUTO_HPP
#define STACK_TEMPLATE_PARAMETER_AUTO_HPP

#include <array>
#include <cassert>

namespace chapter {
namespace basics {

template<typename T, auto Maxsize>
class StackTemplateParameterAuto {

public:
    using size_type = decltype(Maxsize);

    StackTemplateParameterAuto();
    void push(T const& elem);
    void pop();
    T const& top() const;
    bool empty() const {
        return numElems == 0;
    }
    // Can be also auto size() since C++14
    size_type size() const {
        return numElems;
    }

private:
    std::array<T, Maxsize> elems;
    size_type numElems;
};

template<typename T, auto Maxsize>
StackTemplateParameterAuto<T, Maxsize>::StackTemplateParameterAuto()
: numElems(0)
{
}

template<typename T, auto Maxsize>
void StackTemplateParameterAuto<T, Maxsize>::push(T const& elem) {
    assert(numElems < Maxsize);
    elems[numElems] = elem;
    ++numElems;
}

template<typename T, auto Maxsize>
void StackTemplateParameterAuto<T, Maxsize>::pop() {
    assert(!elems.empty());
    --numElems;
}

template<typename T, auto Maxsize>
T const& StackTemplateParameterAuto<T, Maxsize>::top() const {
    assert(!elems.empty());
    return elems[numElems - 1];
}

}
}

#endif // STACK_TEMPLATE_PARAMETER_AUTO_HPP