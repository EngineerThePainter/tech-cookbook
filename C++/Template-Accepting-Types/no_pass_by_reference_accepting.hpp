#ifndef NO_PASS_BY_REFERENCE_ACCEPTING_HPP
#define NO_PASS_BY_REFERENCE_ACCEPTING_HPP

#include <type_traits>
#include <iostream>

template <typename T>
void noPassByReferenceAcceptingStaticAssert(T t)
{
    static_assert(!std::is_reference<T>::value, "Type should not be a reference");
    std::cout << "noPassByReferenceAcceptingStaticAssert was called" << std::endl;
}

template <typename T>
typename std::enable_if<!std::is_reference<T>::value>::type noPassByReferenceAcceptingSfinae(T t)
{
    std::cout << "noPassByReferenceAcceptingSfinae was called" << std::endl;
}

#endif // NO_PASS_BY_REFERENCE_ACCEPTING_HPP