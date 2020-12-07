#include "chapters/chapter4.hpp"

#include <iostream>
#include <string>

#include <basics/varprint1.hpp>

#include <common/common_prints.hpp>

namespace chapters {

namespace {
 void runVariadicPrint() {
     basics::print<double, std::string, int>(34.4, "Hello", 42);
 }
}

void runChapter4() {
    common::printTitle("C++ Templates Chapter 4");
    common::emptyLine();
    runVariadicPrint();
}

} // namespace chapters