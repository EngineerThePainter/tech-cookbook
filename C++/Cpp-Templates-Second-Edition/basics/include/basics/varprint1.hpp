#ifndef VARPRINT1_HPP
#define VARPRINT1_HPP

#include <iostream>

namespace basics {

void print() {
    std::cout << "Normal print" << std::endl;
}

template<typename T, typename... Types>
void print(T firstArg, Types... args) {
    std::cout << firstArg << std::endl;
    print(args...);
}

} // basics

#endif // VARPRINT1_HPP