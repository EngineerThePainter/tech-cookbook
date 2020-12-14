#include "chapters/chapter5.hpp"

#include <iostream>
#include <string>
#include <vector>

#include <basics/arrays.hpp>
#include <basics/printcoll.hpp>

#include <common/common_prints.hpp>

namespace chapters {

namespace {

void printingColls() {
    common::printTitle("Print container content");
    std::vector<std::string> container {"the good", "the bad", "the ugly"};
    basics::printcoll<std::vector<std::string>>(container);
    common::emptyLine();
}

template<typename T1, typename T2, typename T3>
void arraysFoo(int a1[7], int a2[], // pointers by language rules
               int (&a3)[42],       // reference to array of known bound
               int (&x0)[],         // reference to array of unknown bound
               T1 x1,               // passing by value decays
               T2& x2, T3&& x3)     // passing by reference
{
    basics::MyClass<decltype(a1)>::print();
    basics::MyClass<decltype(a2)>::print();
    basics::MyClass<decltype(a3)>::print();
    basics::MyClass<decltype(x0)>::print();
    basics::MyClass<decltype(x1)>::print();
    basics::MyClass<decltype(x2)>::print();
    basics::MyClass<decltype(x3)>::print();
}

void arraysUsage() {
    common::printTitle("Templates for raw arrays");
    int a[42];
    basics::MyClass<decltype(a)>::print();
    extern int x[];
    basics::MyClass<decltype(x)>::print();
    common::printMessage("Now let's call arraysFoo()");
    arraysFoo(a, a, a, x, x, x, x);
    common::emptyLine();
}

int x[] = {0, 8, 15};

}

void runChapter5() {
    common::printTitle("C++ Templates Chapter 5");
    printingColls();
    arraysUsage();
    common::emptyLine();
}

}