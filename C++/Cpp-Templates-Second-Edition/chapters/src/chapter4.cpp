#include "chapters/chapter4.hpp"

#include <iostream>
#include <string>

#include <basics/varprint1.hpp>
#include <basics/varprint2.hpp>

#include <common/common_prints.hpp>

namespace chapters {

namespace {
 void runVariadicPrint1() {
     common::printMessage("Print Variadic Template for three arguments");
     basics::print<double, std::string, int, std::string, int>(34.4, "Hello", 42, "Templates", 15);
     common::printMessage("Variadic Template for only one argument - the function parameter pack is empty");
     basics::print<std::string>("Only one parameter");
     common::emptyLine();
 }
 void runVariadicPrint2() {
     common::printMessage("Print2 Variadic Template for three arguments");
     basics::print2<double, std::string, int>(34.4, "Hello", 42);
     common::printMessage("Variadic Template for only one argument - the function parameter pack is empty");
     basics::print2<std::string>("Only one parameter");
     common::emptyLine();
 }
}

void runChapter4() {
    common::printTitle("C++ Templates Chapter 4");
    common::emptyLine();
    runVariadicPrint1();
    runVariadicPrint2();
}

} // namespace chapters