#include <type_traits>

namespace basics {

template<typename T>
T max(T a, T b) {
    return b < a ? a : b;
}

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

}