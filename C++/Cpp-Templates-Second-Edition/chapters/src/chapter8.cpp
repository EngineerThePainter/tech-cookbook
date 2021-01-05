#include "chapters/chapter8.hpp"

#include <iostream>
#include <string>
#include <vector>

#include <basics/isPrime.hpp>
#include <basics/isPrime11.hpp>
#include <basics/isPrime14.hpp>
#include <basics/len.hpp>

#include <common/common_prints.hpp>

namespace chapters {

namespace {

void primeNumber() {
    common::printTitle("Prime number at compile time");
    common::printMessage("Prime number calculation using templates");
    std::cout << "9 is: " << (basics::IsPrime<9>::value ? "prime" : "not prime") << std::endl;
    std::cout << "17 is: " << (basics::IsPrime<17>::value ? "prime" : "not prime") << std::endl;
    std::cout << "111 is: " << (basics::IsPrime<111>::value ? "prime" : "not prime") << std::endl;
    std::cout << "53 is: " << (basics::IsPrime<53>::value ? "prime" : "not prime") << std::endl;
    common::emptyLine();
    common::printMessage("Prime number calculation using constexpr from C++11");
    std::cout << "9 is: " << (basics::IsPrime11(9) ? "prime" : "not prime") << std::endl;
    std::cout << "17 is: " << (basics::IsPrime11(17) ? "prime" : "not prime") << std::endl;
    std::cout << "111 is: " << (basics::IsPrime11(111) ? "prime" : "not prime") << std::endl;
    std::cout << "53 is: " << (basics::IsPrime11(53) ? "prime" : "not prime") << std::endl;
    common::emptyLine();
    common::printMessage("Prime number calculation using constexpr from C++14");
    std::cout << "9 is: " << (basics::IsPrime14(9) ? "prime" : "not prime") << std::endl;
    std::cout << "17 is: " << (basics::IsPrime14(17) ? "prime" : "not prime") << std::endl;
    std::cout << "111 is: " << (basics::IsPrime14(111) ? "prime" : "not prime") << std::endl;
    std::cout << "53 is: " << (basics::IsPrime14(53) ? "prime" : "not prime") << std::endl;
    common::emptyLine();
}

void sfinae() {
    common::printTitle("SFINAE");
    int a[10];
    common::printMessage("Len for arrays");
    std::cout << basics::len(a) << std::endl;
    std::cout << basics::len("tmp") << std::endl;
    common::emptyLine();

    common::printMessage("Len for types with size_type");
    std::vector<int> v;
    std::cout << basics::len(v) << std::endl;
    common::emptyLine();
    
    common::printMessage("Fallback len");
    int* p = new int[5];
    std::cout << basics::len(p) << std::endl;
    delete[] p;
    /**
     * Error - best match is for len for size_type, but std::allocator does not contain size() member
     */
    // std::allocator<int> x;
    // std::cout << basics::len(x) << std::endl;
    common::emptyLine();
}

} // namespace

void runChapter8() {
    common::printTitle("C++ Templates Chapter 8");
    primeNumber();
    sfinae();
    common::emptyLine();
}

}