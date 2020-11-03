#include <iostream>
#include <string>

#include "basics/max1.hpp"

void printTitle(const std::string& title) {
    std::cout << "********** " << title <<" **********" << std::endl;
}

void max1SimpleUsage() {
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
    std::cout << "max(s1, s2) = " << basics::max(s1, s2) << std::endl << std::endl;
}

void max1ReturnType() {
    printTitle("Using max1.hpp evaluation of different returns");

    const int a = 5;
    const double b = 6.66;
    std::cout << "maxWithT1ReturnType(a, b) = " << basics::maxWithT1ReturnType(a, b) << std::endl;
    std::cout << "maxWithT1ReturnType(b, a) = " << basics::maxWithT1ReturnType(b, a) << std::endl;

    /**
     * We HAVE TO specify the template types, as return type is not deduced.
     */
    std::cout << "Return type int for maxWithRTReturnType(a, b) = " <<
        basics::maxWithRTReturnType<int, double, int>(a, b) << std::endl;
    std::cout << "Return type double for maxWithRTReturnType(a, b) = " << 
        basics::maxWithRTReturnType<int, double, double>(a, b) << std::endl;

    /**
     * When return type is first on the list we can go with this approach 
     * and deduce rest of the types int and double.
     */ 
    std::cout << "Deduced double for maxWithRTReturnTypeAsFirstArgument(a, b) = " << 
        basics::maxWithRTReturnTypeAsFirstArgument<double>(a, b) << std::endl;

    std::cout << "Deduced int for maxWithRTReturnTypeAsFirstArgument(a, b) = " << 
        basics::maxWithRTReturnTypeAsFirstArgument<int>(a, b) << std::endl;

    // Auto is possible since C++14
    std::cout << "Return type for maxWithAuto(a, b) = " <<
        basics::maxWithAuto(a, b) << std::endl;

    std::cout << "Return type for maxWithAuto(b, a) = " << 
        basics::maxWithAuto(b, a) << std::endl;

}

int main() {
    std::cout << "C++ Templates Chapter 1" << std::endl;
    max1SimpleUsage();
    max1ReturnType();
    return 0;
}