#ifndef COMMON_PRINTS_HPP
#define COMMON_PRINTS_HPP

#include <iostream>
#include <string>

namespace chapter {

inline void printTitle(const std::string& title) {std::cout << "********** " << title <<" **********" << std::endl;}

inline void printMessage(const std::string& message) {std::cout << message << std::endl;}

inline void emptyLine() {std::cout << std::endl;}

/**
 * I know that T should be checked for operator<<, but currently I don't know how to ensure such thing :)
*/
template<typename T>
void printCallFunction(const std::string& functionHeader, T value) {
    std::cout<< "Call for " << functionHeader << " gives: " << value << std::endl;
}
}

#endif