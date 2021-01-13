#include "chapters/chapter11.hpp"

#include <iostream>
#include <string>
#include <vector>

#include <basics/foreach.hpp>
#include <basics/foreachInvoke.hpp>
#include <basics/invoke.hpp>
#include <basics/maxdefaultdeclval.hpp>
#include <basics/referror.hpp>
#include <basics/tmplparamref.hpp>

#include <common/common_prints.hpp>

namespace chapters {

namespace {

void func(int i) {
    common::printCallFunction("func", i);
}

double add(const int x, const double y) {
    std::cout << "Add " << x << " to " << y << " gives ";
    return x+y; 
}

class FuncObj {
    public:
    void operator() (int i) const {
        common::printCallFunction("FuncObj::operator()", i);
    }
};

class MyClass {
    public:
    void memfunc(int i) const {
        common::printCallFunction("MyClass::memfunc()", i);
    }
};

void supportingFunctionObjects() {
    common::printTitle("Supporting function objects");
    std::vector<int> primes = {2, 3, 5, 7, 11, 13, 17, 19};

    common::printMessage("Function as callable - decays to pointer");
    basics::foreach(primes.begin(), primes.end(), func);
    common::emptyLine();
    common::printMessage("Function pointer as callable");
    basics::foreach(primes.begin(), primes.end(), &func);
    common::emptyLine();
    common::printMessage("Function object as callable");
    basics::foreach(primes.begin(), primes.end(), FuncObj());
    common::emptyLine();
    common::printMessage("Lambda as callable");
    basics::foreach(primes.begin(), primes.end(), [](int i) {common::printCallFunction("lambda", i);});
    common::printMessage("Lambda as callable and additional argument");
    basics::foreachInvoke(primes.begin(), primes.end(), [](std::string const& prefix, int i) {
        std::cout << prefix << i << std::endl;
    }, "- value: ");
    common::emptyLine();
    common::printMessage("Class member function");
    MyClass obj;
    basics::foreachInvoke(primes.begin(), primes.end(), &MyClass::memfunc, obj);
    common::emptyLine();
}

void genericCalling() {
    common::printTitle("Generic calling");
    basics::call(func, 42);
    std::cout << basics::call(add, 3, 3.5) << std::endl;
    common::emptyLine();
}

void declvalExample() {
    common::printTitle("Max default declval");
    common::printCallFunction("basics::maxDefaultDeclval(6, 6.1)", basics::maxDefaultDeclval(6, 6.1));
    common::emptyLine();
}

void templateTypeParametersAsReferences() {
    common::printTitle("Template type parameters as references");
    std::cout << std::boolalpha;
    int i;
    int& r = i;
    basics::tmplParamIsReference(i);
    basics::tmplParamIsReference(r);
    basics::tmplParamIsReference<int&>(i);
    basics::tmplParamIsReference<int&>(r);
    common::emptyLine();
}

int null = 0;

void referror() {
    common::printTitle("Reference Errors");
    basics::RefMem<int> rm1, rm2;
    rm1 = rm2;

    // basics::RefMem<int&> rm3; // ERROR: invalid default value for Z
    // basics::RefMem<int&, 0> rm4; //ERROR: invalid default value for Z

    extern int null;
    basics::RefMem<int&, null> rm5, rm6;
    // rm5 = rm6; // ERROR: operator= is deleted due to reference member
    common::emptyLine();
}

} // namespace

void runChapter11() {
    common::printTitle("C++ Templates Chapter 11");
    supportingFunctionObjects();
    genericCalling();
    declvalExample();
    templateTypeParametersAsReferences();
    referror();
    common::emptyLine();
}

}