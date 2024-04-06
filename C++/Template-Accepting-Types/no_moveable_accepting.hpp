#pragma once

#include <iostream>
#include <type_traits>

template <typename T>
void doNotAcceptTypeWithMoveSemanticsStaticAsserts(T t)
{
    static_assert(!std::is_move_assignable<T>::value, "Type should not be move assignable");
    static_assert(!std::is_move_constructible<T>::value, "Type should not be move constructible");
    std::cout << "doNotAcceptTypeWithMoveSemanticsStaticAsserts was called" << std::endl;
}

template <typename T>
void doNotAcceptTypeWithMoveSemanticsSfinae(T t,
                                            typename std::enable_if<!std::is_move_assignable<T>::value>::type * = nullptr,
                                            typename std::enable_if<!std::is_move_constructible<T>::value>::type * = nullptr)
{
    std::cout << "doNotAcceptTypeWithMoveSemanticsSfinae was called" << std::endl;
}
