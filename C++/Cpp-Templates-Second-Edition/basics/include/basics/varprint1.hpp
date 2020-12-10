#ifndef VARPRINT1_HPP
#define VARPRINT1_HPP

#include <iostream>

namespace basics {

/**
 * This function is mandatory it is called when function parameter pack is empty.
 * Should be empty, but I'm leaving this cout to see the recursive path
 * when using a variadic template.
 */
void print() {
    std::cout << "Normal print" << std::endl;
}

template<typename T, typename... Types>
void print(T firstArg, Types... args) {
    std::cout << "Remaining types apart of the current one: " << sizeof...(Types) << std::endl;
    std::cout << "Remaining args apart of the current one: " << sizeof...(args) << std::endl;
    std::cout << firstArg << std::endl;
    print(args...);
}

template<typename... T>
void printDoubled(T const&... args) {
    print(args + args...);
}

template<typename... T>
void printOneAdded(T const&... args) {
    print(args + 1 ...);
}

template<typename C, typename... Idx>
void printElems(C const& coll, Idx... idx) {
    print(coll[idx] ...);
}

template<std::size_t... Idx, typename C>
void printIdx(C const& coll) {
    print(coll[Idx] ...);
}

} // basics

#endif // VARPRINT1_HPP