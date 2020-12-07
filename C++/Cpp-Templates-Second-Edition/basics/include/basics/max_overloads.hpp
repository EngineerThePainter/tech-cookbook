#ifndef MAX_OVERLOADS_HPP
#define MAX_OVERLOADS_HPP

#include <cstring>
#include <iostream>
#include <string>

namespace basics {

int maxOverload(int a, int b) {
    std::cout << "Calling nontemplate ";
    return b < a ? a : b;
}

template<typename T>
T maxOverload(T a, T b) {
    std::cout << "Calling template ";
    return b < a ? a : b;
}

template<typename T1, typename T2>
auto maxOverloadReturnType(T1 a, T2 b) {
    std::cout << "Calling template auto return type ";
    return b < a ? a : b;
}

template<typename RT, typename T1, typename T2>
RT maxOverloadReturnType(T1 a, T2 b) {
    std::cout << "Calling template RT return type ";
    return b < a ? a : b;
}

template<typename T>
T maxVal(T a, T b) {
    std::cout << "Calling any type ";
    return b < a ? a : b;
}

template<typename T>
T* maxVal(T* a, T* b) {
    std::cout << "Calling pointer type ";
    return b < a ? a : b;
}

template<typename T>
char const* maxVal(char const* a, char const* b) {
    std::cout << "Calling char const* type ";
    return b < a ? a : b;
}

/**
 * You need to be sure that all overloads are declared before they are used.
 */

template<typename T>
T maxBadDeclarationOrder(T a, T b) {
    std::cout << "Calling any type ";
    return b < a ? a : b;
}

template<typename T>
T maxBadDeclarationOrder(T a, T b, T c) {
    std::cout << "Calling any type three arguments ";
    return maxBadDeclarationOrder(maxBadDeclarationOrder(a,b), c);
}

int maxBadDeclarationOrder(int a, int b) {
    std::cout << "Calling int type ";
    return b < a ? a : b;
}

} // basics

#endif