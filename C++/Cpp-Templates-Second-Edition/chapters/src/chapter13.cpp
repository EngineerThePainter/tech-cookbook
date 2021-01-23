#include "chapters/chapter13.hpp"

#include <iostream>

#include <common/common_prints.hpp>

#include <details/adl.hpp>
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

} // namespace

void runChapter13() {
    common::printTitle("C++ Templates Chapter 13");
    adl();
    injectClassName();
    common::emptyLine();
}

}