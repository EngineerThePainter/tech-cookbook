#ifndef MAX_RETURN_TYPE_HPP
#define MAX_RETURN_TYPE_HPP

#include <type_traits>

namespace basics {

template<typename T1, typename T2>
T1 maxWithT1ReturnType(T1 a, T2 b) {
    return b < a ? a : b;
}

template<typename T1, typename T2, typename RT>
RT maxWithRTReturnType(T1 a, T2 b) {
    return b < a ? a : b;
}

template<typename RT, typename T1, typename T2>
RT maxWithRTReturnTypeAsFirstArgument(T1 a, T2 b) {
    return b < a ? a : b;
}

template<typename T1, typename T2>
auto maxWithAuto(T1 a, T2 b) {
    return b < a ? a : b;
}

//Before C++14
template<typename T1, typename T2>
auto maxWithDecltype (T1 a, T2 b) -> decltype(b < a ? a : b) {
    return b < a ? a : b;
}

/**
 * This is the proper way for the thing from above
 * as sometimes you could e.g. unintendentely pass reference.
 * std::decay<typename T> decays type to the pure type.
 * Strips e.g. reference/const qualifiers so it's protecting 
 * the return type of the funtion that will not be anything unexpected.
 */
template<typename T1, typename T2>
auto maxWithDecltypeDecay (T1 a, T2 b) -> typename std::decay<decltype(b < a ? a : b)>::type {
    return b < a ? a : b;
}

/**
 * Since C++14
 * std::common_type_t returns type that will be common for both T1 and T2.
 * In C++11 you had to go with: typename std::common_type<T1, T2>::type.
 * Both std:common_type and std:common_type_t decays type.
 */
template<typename T1, typename T2>
std::common_type_t<T1, T2> maxWithCommonTypeT(T1 a, T2 b) {
    return b < a ? a : b;
}

/**
 * This way we ensure that by default decltype that RT type will be deduced,
 * as it is not deduced automatically like for T1 and T2.
 * 
 * std::decay_t<> is a C++14 suplement for std::decay<>::type. And it's here to ensure that 
 * no reference will be returned.
 * 
 * Requires that both T1 and T2 will be able to perform default constructor call.
 * 
 * This case and cases below allow to assign auto to the variable when passing there return value
 * from this function call.
 */
template<typename T1, typename T2,
        typename RT = std::decay_t<decltype(true ? T1() : T2())>>
RT maxDefaultArgumentDecayAndDecltype(T1 a, T2 b) {
    return b < a ? a : b;
}

template<typename T1, typename T2,
        typename RT = std::common_type_t<T1, T2>>
RT maxDefaultArgumentCommonType(T1 a, T2 b) {
    return b < a ? a : b;
}

}

#endif