#pragma once

#include <iostream>
#include <type_traits>

template <typename T>
void doNotAcceptAssignableTypeStaticAssert(T t)
{
    static_assert(!std::is_assignable<T &, const T &>::value, "Type is assignable");
    std::cout << "doNotAcceptAssignableTypeStaticAssert was called" << std::endl;
}

template <typename T>
typename std::enable_if<!std::is_assignable<T &, const T &>::value>::type
doNotAcceptAssignableTypeSfinae(T t)
{
    std::cout << "doNotAcceptAssignableTypeSfinae was called" << std::endl;
}