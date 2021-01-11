#include "chapters/chapter11.hpp"

#include <iostream>
#include <string>
#include <vector>

#include <basics/foreach.hpp>

#include <common/common_prints.hpp>

namespace chapters {

namespace {

void func(int i) {
    common::printCallFunction("func", i);
}

class FuncObj {
    public:
    void operator() (int i) const {
        common::printCallFunction("FuncObj::operator()", i);
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
    common::emptyLine();
}

} // namespace

void runChapter11() {
    common::printTitle("C++ Templates Chapter 11");
    supportingFunctionObjects();
    common::emptyLine();
}

}