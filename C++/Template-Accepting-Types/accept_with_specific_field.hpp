#pragma once

#include <iostream>

template <typename T>
void acceptTypeWithSpecificFieldStaticAssert(T t)
{
    static_assert(std::is_same<decltype(t.specific_field), int>::value, "Type does not have specific field");
    std::cout << "acceptTypeWithSpecificFieldStaticAssert was called" << std::endl;
}

template <typename T, typename std::enable_if<std::is_same<decltype(T::specific_field), int>::value>::type * = nullptr>
void acceptTypeWithSpecificFieldSfinae(T t)
{
    std::cout << "acceptTypeWithSpecificFieldSfinae was called" << std::endl;
}