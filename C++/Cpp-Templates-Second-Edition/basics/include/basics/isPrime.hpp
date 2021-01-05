#ifndef ISPRIME_HPP
#define ISPRIME_HPP

#include <iostream>
#include <string>

namespace basics {

template<unsigned p, unsigned d> // p - number to check, d - current divisor
struct DoIsPrime {
    static constexpr bool value = (p%d != 0) && DoIsPrime<p, d-1>::value;
};

template<unsigned p> // end recursion
struct DoIsPrime<p, 2> {
    static constexpr bool value = (p%2 != 0);
};

template<unsigned p> // primary template
struct IsPrime
{
    // Start recursion from divisor = p/2
    static constexpr bool value = DoIsPrime<p, p/2>::value;
};

// Special cases to avoid endless recursion when template is instatiated
template<>
struct IsPrime<0> {static constexpr bool value = false;};

template<>
struct IsPrime<1> {static constexpr bool value = false;};

template<>
struct IsPrime<2> {static constexpr bool value = true;};

template<>
struct IsPrime<3> {static constexpr bool value = true;};

} // basics

#endif