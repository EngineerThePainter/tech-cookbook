#include "chapters/chapter13.hpp"

#include <iostream>

#include <common/common_prints.hpp>

#include <details/adl.hpp>
#include <details/anglebrackethack.hpp>
#include <details/inject.hpp>

namespace chapters {

namespace {

void adl() {
    common::printTitle("ADL Example");
    ::f(details::N::e1); // qualified function name - no ADL
    f(details::N::e1); // Ordinaty lookup finds ::f() and ADL finds N::f(), the latter is preferred
    common::emptyLine();
}

void injectClassName() {
    common::printTitle("Inject Class Name Example");
    std::cout << "C::f() = " << details::C::f() << std::endl;
    std::cout << "::f() = " << ::details::f() << std::endl;
    common::emptyLine();
}

void angleBracketsHack() {
    common::printTitle("Angle brackets hack");
    /**
     * In C++98 it will be 0
     */
    std::cout << (details::YY<details::XX<1> > ::num >::details::num>::details::num) << std::endl;
    /**
     * In C++98 it will be 3 due to treating '>>' as a right shift token - was changed since C++ 11
     */
    std::cout << (details::YY<details::XX<1 >> ::num >::details::num>::details::num) << std::endl;
    common::emptyLine();
}

void dependentNamesOfTypes() {
    common::printTitle("Dependent names of types");
    common::printMessage("See details/evilSpecialization.hpp");
    common::emptyLine();
}

} // namespace

void runChapter13() {
    common::printTitle("C++ Templates Chapter 13");
    adl();
    injectClassName();
    angleBracketsHack();
    dependentNamesOfTypes();
    common::emptyLine();
}

}