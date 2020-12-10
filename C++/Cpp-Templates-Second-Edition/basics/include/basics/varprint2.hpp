#ifndef VARPRINT2_HPP
#define VARPRINT2_HPP

#include <iostream>

namespace basics {

/**
 * This function is mandatory it is called when function parameter pack is empty.
 * Should be empty, but I'm leaving this cout to see the recursive path
 * when using a variadic template.
 */
template<typename T>
void print2(T args) {
    // std::cout << "Calling print2" << std::endl;
    std::cout << args << std::endl;
}

template<typename T, typename... Types>
void print2(T firstArg, Types... args) {
    print2(firstArg);
    print2(args...);
}

} // basics

#endif // VARPRINT2_HPP