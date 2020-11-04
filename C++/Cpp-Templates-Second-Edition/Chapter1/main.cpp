#include <iostream>
#include <string>

#include "basics/max1.hpp"

void printTitle(const std::string& title) {
    std::cout << "********** " << title <<" **********" << std::endl;
}

void emptyLine() {
    std::cout << std::endl;
}

/**
 * I know that T should be checked for operator<<, but currently I don't know how to ensure such thing :)
 */
template<typename T>
void printCallFunction(const std::string& functionHeader, T value) {
    std::cout<< "Call for " << functionHeader << " gives: " << value << std::endl;
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
    printCallFunction("max(7, i)", basics::max(7, i));

    const double f1 = 3.4;
    const double f2 = -6.3;
    printCallFunction("max(f1, f2)", basics::max(f1, f2));

    const std::string s1 = "Math is fun";
    const std::string s2 = "Math";
    printCallFunction("max(s1, s2))", basics::max(s1, s2));
    emptyLine();
}

void max1ReturnType() {
    printTitle("Using max1.hpp evaluation of different returns");

    const int a = 5;
    const double b = 6.66;
    printCallFunction("maxWithT1ReturnType(a, b)", basics::maxWithT1ReturnType(a, b));
    printCallFunction("maxWithT1ReturnType(b, a)", basics::maxWithT1ReturnType(b, a));
    emptyLine();

    /**
     * We HAVE TO specify the template types, as return type is not deduced.
     */
    printCallFunction("maxWithRTReturnType(a, b)", basics::maxWithRTReturnType<int, double, int>(a, b));
    printCallFunction("maxWithRTReturnType(a, b)", basics::maxWithRTReturnType<int, double, double>(a, b));
    emptyLine();

    /**
     * When return type is first on the list we can go with this approach 
     * and deduce rest of the types int and double.
     */ 
    printCallFunction("maxWithRTReturnTypeAsFirstArgument(a, b)", basics::maxWithRTReturnTypeAsFirstArgument<double>(a, b));
    printCallFunction("maxWithRTReturnTypeAsFirstArgument(a, b)", basics::maxWithRTReturnTypeAsFirstArgument<int>(a, b));
    emptyLine();

    // Calling this one is possible since C++14
    printCallFunction("maxWithAuto(a, b)", basics::maxWithAuto(a, b));
    printCallFunction("maxWithAuto(b, a)", basics::maxWithAuto(b, a));
    emptyLine();

    // Decltype before C++14
    printCallFunction("maxWithDecltype(a, b)", basics::maxWithDecltype(a, b));
    printCallFunction("maxWithDecltype(b, a)", basics::maxWithDecltype(b, a));
    emptyLine();

    printCallFunction("maxWithDecltypeDecay(a, b)", basics::maxWithDecltypeDecay(a, b));
    printCallFunction("maxWithDecltypeDecay(b, a)", basics::maxWithDecltypeDecay(b, a));
    emptyLine();

    printCallFunction("maxWithCommonTypeT(a, b)", basics::maxWithCommonTypeT(a, b));
    printCallFunction("maxWithCommonTypeT(b, a)", basics::maxWithCommonTypeT(b, a));
    emptyLine();
}

int main() {
    std::cout << "C++ Templates Chapter 1" << std::endl;
    max1SimpleUsage();
    max1ReturnType();
    return 0;
}