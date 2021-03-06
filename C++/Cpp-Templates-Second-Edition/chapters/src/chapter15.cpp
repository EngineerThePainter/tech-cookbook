#include "chapters/chapter15.hpp"

#include <iostream>

#include <common/common_prints.hpp>
#include <details/fppm.hpp>
#include <details/initlist.hpp>

namespace chapters {

namespace {

void deducedContext() {
  common::printTitle("Deduced context");
  details::fppm(&details::X<33>::f); // N is successfuly deduced to be 33
  common::emptyLine();
}

void initializerList() {
  common::printTitle("Initializer list in the context of type deduction");
  details::f({2,3,4,5,6,7,8,9,0});
  common::emptyLine();
}

} // namespace

void runChapter15() {
    common::printTitle("C++ Templates Chapter 15");
    deducedContext();
    initializerList();
    common::emptyLine();
}

}