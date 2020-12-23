#include "chapters/chapter7.hpp"

#include <iostream>
#include <string>

#include <basics/cref.hpp>

#include <common/common_prints.hpp>

namespace chapters {

namespace {

void crefExample() {
    common::printTitle("Cref example");
    std::string s = "hello";
    basics::printString(s);
    basics::printT(std::cref(s));
    common::emptyLine();
}

} // namespace

void runChapter7() {
    common::printTitle("C++ Templates Chapter 7");
    crefExample();
    common::emptyLine();
}

}