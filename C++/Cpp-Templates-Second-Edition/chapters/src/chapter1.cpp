#include "chapters/chapter1.hpp"

#include <iostream>
#include <string>

#include <basics/max.hpp>
#include <basics/max_overloads.hpp>
#include <basics/max_return_type.hpp>

#include <common/common_prints.hpp>

namespace chapters {

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
    common::printTitle("Using max.hpp");

    const int i = 404;
    common::printCallFunction("max(7, i)", basics::max(7, i));

    const double f1 = 3.4;
    const double f2 = -6.3;
    common::printCallFunction("max(f1, f2)", basics::max(f1, f2));

    const std::string s1 = "Math is fun";
    const std::string s2 = "Math";
    common::printCallFunction("max(s1, s2))", basics::max(s1, s2));
    common::emptyLine();
}

void maxReturnType() {
    common::printTitle("Using max.hpp evaluation of different returns");

    const int a = 5;
    const double b = 6.66;
    common::printCallFunction("maxWithT1ReturnType(a, b)", basics::maxWithT1ReturnType(a, b));
    common::printCallFunction("maxWithT1ReturnType(b, a)", basics::maxWithT1ReturnType(b, a));
    common::emptyLine();

    /**
     * We HAVE TO specify the template types, as return type is not deduced.
     */
    common::printCallFunction("maxWithRTReturnType(a, b)", basics::maxWithRTReturnType<int, double, int>(a, b));
    common::printCallFunction("maxWithRTReturnType(a, b)", basics::maxWithRTReturnType<int, double, double>(a, b));
    common::emptyLine();

    /**
     * When return type is first on the list we can go with this approach 
     * and deduce rest of the types int and double.
     */ 
    common::printCallFunction("maxWithRTReturnTypeAsFirstArgument(a, b)", basics::maxWithRTReturnTypeAsFirstArgument<double>(a, b));
    common::printCallFunction("maxWithRTReturnTypeAsFirstArgument(a, b)", basics::maxWithRTReturnTypeAsFirstArgument<int>(a, b));
    common::emptyLine();

    // Calling this one is possible since C++14
    common::printCallFunction("maxWithAuto(a, b)", basics::maxWithAuto(a, b));
    common::printCallFunction("maxWithAuto(b, a)", basics::maxWithAuto(b, a));
    common::emptyLine();

    // Decltype before C++14
    common::printCallFunction("maxWithDecltype(a, b)", basics::maxWithDecltype(a, b));
    common::printCallFunction("maxWithDecltype(b, a)", basics::maxWithDecltype(b, a));
    common::emptyLine();

    common::printCallFunction("maxWithDecltypeDecay(a, b)", basics::maxWithDecltypeDecay(a, b));
    common::printCallFunction("maxWithDecltypeDecay(b, a)", basics::maxWithDecltypeDecay(b, a));
    common::emptyLine();

    common::printCallFunction("maxWithCommonTypeT(a, b)", basics::maxWithCommonTypeT(a, b));
    common::printCallFunction("maxWithCommonTypeT(b, a)", basics::maxWithCommonTypeT(b, a));
    common::emptyLine();

    common::printCallFunction("maxDefaultArgumentDecayAndDecltype(a, b)", basics::maxDefaultArgumentDecayAndDecltype(a, b));
    common::printCallFunction("maxDefaultArgumentDecayAndDecltype(b, a)", basics::maxDefaultArgumentDecayAndDecltype(b, a));
    common::emptyLine();    
    
    common::printCallFunction("maxDefaultArgumentCommonType(a, b)", basics::maxDefaultArgumentCommonType(a, b));
    common::printCallFunction("maxDefaultArgumentCommonType(b, a)", basics::maxDefaultArgumentCommonType(b, a));
    common::emptyLine();    
}

void maxOverloadFunctionTemplate() {
    common::printTitle("Using max.hpp evaluation of function overload");

    common::printCallFunction("maxOverload(7, 42)", basics::maxOverload(7, 42));
    common::printCallFunction("maxOverload(7.0, 42.0)", basics::maxOverload(7.0, 42.0));
    common::printCallFunction("maxOverload('a', 'b')", basics::maxOverload('a', 'b'));
    // <> tells explicitly to call template
    common::printCallFunction("maxOverload<>(7, 42)", basics::maxOverload<>(7, 42));
    common::printCallFunction("maxOverload<double>(7, 42)", basics::maxOverload<double>(7, 42));
    // Calling this template may raise warning as there is implicit conversion from 'double' to 'int'.
    common::printCallFunction("maxOverload<double>('a', 42.7)", basics::maxOverload('a', 42.7));
    common::emptyLine();

    common::printCallFunction("maxOverloadReturnType(4, 7.2)", basics::maxOverloadReturnType(4, 7.2));
    common::printCallFunction("maxOverloadReturnType<long double>(4, 7.2)", basics::maxOverloadReturnType<long double>(4, 7.2));
    // Call below cause error as both implementations are good and compiler cannot deduce which template should be used
    // printCallFunction("maxOverloadReturnType<int>(4, 7.2)", basics::maxOverloadReturnType<int>(4, 7.2));
    common::emptyLine();

    int a = 7;
    int b = 42;
    common::printCallFunction("maxVal(a, b)", basics::maxVal(a, b));

    std::string s1 = "hey";
    std::string s2 = "guy";
    common::printCallFunction("maxVal(s1, s2)", basics::maxVal(s1, s2));

    int* p1 = &b;
    int* p2 = &a;
    common::printCallFunction("maxVal(p1, p1)", basics::maxVal(p1, p2));

    char const* x = "hello";
    char const* y = "donut";
    common::printCallFunction("maxVal(x, y)", basics::maxVal(x, y));
    common::emptyLine();

    /**
     * You can see what does it mean to put overloads in the right order:
     * the overload function with integers could be called and we could expect it, but instead
     * the version for any type is called.
     */
    common::printCallFunction("maxBadDeclarationOrder(47, 11, 33)", basics::maxBadDeclarationOrder(47, 11, 33));
    common::emptyLine();
}

void runChapter1() {
    common::printTitle("C++ Templates Chapter 1");
    common::emptyLine();
    maxSimpleUsage();
    maxReturnType();
    maxOverloadFunctionTemplate();
}

}