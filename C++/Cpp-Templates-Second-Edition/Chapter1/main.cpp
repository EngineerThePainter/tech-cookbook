#include <iostream>
#include <string>

#include "basics/max.hpp"
#include "basics/max_return_type.hpp"
#include "basics/max_overloads.hpp"

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

void maxSimpleUsage() {
    /**
     * The basics::max() is calculated for each type separately. 
     * The only requirement for this function is support for operator '<' used inside function body.
     * 
     * Template is translated in two phases:
     * - At definition time when template is checked for the code corrected (type provided is ignored)
     * e.g. syntax, static assertions etc.
     * - At instantiation time whole template is checked to ensure that code is valid.
     */
    printTitle("Using max.hpp");

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

void maxReturnType() {
    printTitle("Using max.hpp evaluation of different returns");

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

    printCallFunction("maxDefaultArgumentDecayAndDecltype(a, b)", basics::maxDefaultArgumentDecayAndDecltype(a, b));
    printCallFunction("maxDefaultArgumentDecayAndDecltype(b, a)", basics::maxDefaultArgumentDecayAndDecltype(b, a));
    emptyLine();    
    
    printCallFunction("maxDefaultArgumentCommonType(a, b)", basics::maxDefaultArgumentCommonType(a, b));
    printCallFunction("maxDefaultArgumentCommonType(b, a)", basics::maxDefaultArgumentCommonType(b, a));
    emptyLine();    
}

void maxOverloadFunctionTemplate() {
    printTitle("Using max.hpp evaluation of function overload");

    printCallFunction("maxOverload(7, 42)", basics::maxOverload(7, 42));
    printCallFunction("maxOverload(7.0, 42.0)", basics::maxOverload(7.0, 42.0));
    printCallFunction("maxOverload('a', 'b')", basics::maxOverload('a', 'b'));
    // <> tells explicitly to call template
    printCallFunction("maxOverload<>(7, 42)", basics::maxOverload<>(7, 42));
    printCallFunction("maxOverload<double>(7, 42)", basics::maxOverload<double>(7, 42));
    printCallFunction("maxOverload<double>('a', 42.7)", basics::maxOverload('a', 42.7));
    emptyLine();

    printCallFunction("maxOverloadReturnType(4, 7.2)", basics::maxOverloadReturnType(4, 7.2));
    printCallFunction("maxOverloadReturnType<long double>(4, 7.2)", basics::maxOverloadReturnType<long double>(4, 7.2));
    // Call below cause error as both implementations are good and compiler cannot deduce which template should be used
    // printCallFunction("maxOverloadReturnType<int>(4, 7.2)", basics::maxOverloadReturnType<int>(4, 7.2));
    emptyLine();

    int a = 7;
    int b = 42;
    printCallFunction("maxVal(a, b)", basics::maxVal(a, b));

    std::string s1 = "hey";
    std::string s2 = "guy";
    printCallFunction("maxVal(s1, s2)", basics::maxVal(s1, s2));

    int* p1 = &b;
    int* p2 = &a;
    printCallFunction("maxVal(p1, p1)", basics::maxVal(p1, p2));

    char const* x = "hello";
    char const* y = "donut";
    printCallFunction("maxVal(x, y)", basics::maxVal(x, y));
    emptyLine();

    /**
     * You can see what does it mean to put overloads in the right order:
     * the overload function with integers could be called and we could expect it, but instead
     * the version for any type is called.
     */
    printCallFunction("maxBadDeclarationOrder(47, 11, 33)", basics::maxBadDeclarationOrder(47, 11, 33));
    emptyLine();
}

int main() {
    std::cout << "C++ Templates Chapter 1" << std::endl;
    maxSimpleUsage();
    maxReturnType();
    maxOverloadFunctionTemplate();
    return 0;
}