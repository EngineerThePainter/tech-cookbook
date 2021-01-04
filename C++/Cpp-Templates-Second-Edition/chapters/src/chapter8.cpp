#include "chapters/chapter8.hpp"

#include <iostream>
#include <string>

#include <basics/isprime.hpp>

#include <common/common_prints.hpp>

namespace chapters {

namespace {

void primeNumber() {
    common::printTitle("Prime number at compile time");
    std::cout<<std::boolalpha;
    std::cout << "9 is: " << (basics::IsPrime<9>::value ? "prime" : "not prime") << std::endl;
    std::cout << "17 is: " << (basics::IsPrime<17>::value ? "prime" : "not prime") << std::endl;
    std::cout << "111 is: " << (basics::IsPrime<111>::value ? "prime" : "not prime") << std::endl;
    std::cout << "53 is: " << (basics::IsPrime<53>::value ? "prime" : "not prime") << std::endl;
    common::emptyLine();
}

} // namespace

void runChapter8() {
    common::printTitle("C++ Templates Chapter 8");
    primeNumber();
    common::emptyLine();
}

}