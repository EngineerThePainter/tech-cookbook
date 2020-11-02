#include <iostream>
#include <string>

#include "basics/max1.hpp"

void printTitle(const std::string& title) {
    std::cout << "********** " << title <<" **********" << std::endl;
}

void useMax1Template() {
    /**
     * The basics::max() is calculated for each type separately. 
     * The only requirement for this function is support for operator '<' used inside function body.
     * 
     * Template is translated in two phases:
     * - At definition time when template is checked for the code corrected (type provided is ignored)
     * e.g. syntax, static assertions etc.
     * - At instantiation time whole template is checked to ensure that code is valid.
     */
    printTitle("Using max1.hpp");

    const int i = 404;
    std::cout << "max(7, i) = " << basics::max(7, i) << std::endl;

    const double f1 = 3.4;
    const double f2 = -6.3;
    std::cout << "max(f1, f2) = " << basics::max(f1, f2) << std::endl;

    const std::string s1 = "Math is fun";
    const std::string s2 = "Math";
    std::cout << "max(s1, s2) = " << basics::max(s1, s2) << std::endl;
}

int main() {
    std::cout << "C++ Templates Chapter 1" << std::endl;
    useMax1Template();

    return 0;
}