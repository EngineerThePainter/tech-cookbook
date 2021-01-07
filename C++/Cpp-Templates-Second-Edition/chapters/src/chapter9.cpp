#include "chapters/chapter9.hpp"

#include <iostream>
#include <string>

#include <basics/inclusionModel.hpp>

#include <common/common_prints.hpp>

namespace chapters {

namespace {

void inclusionModel() {
    common::printTitle("Inclusion model");
    const double x = 40.4;
    basics::printTypeof(x);
    common::emptyLine();
}

} // namespace

void runChapter9() {
    common::printTitle("C++ Templates Chapter 9");
    inclusionModel();
    common::emptyLine();
}

}