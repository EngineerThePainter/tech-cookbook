#include "chapters/chapter14.hpp"

#include <iostream>

#include <common/common_prints.hpp>

#include <details/lazy1.hpp>

namespace chapters {

namespace {

void lazyDemonstration() {
  common::printTitle("Demonstration of lazy initialization");
  details::Safe<int> ok;
  details::Danger<5> willNotBoom;
  details::Danger<0> boomForZero; // compiling with 'pednatic' (GCC) gives warning, but in general it's an error
  // details::Danger<-5> boomForMinus; // explicit error

  details::Tricky<int, 5> trickster;
  details::Tricky<int, 0> zeroTrickster; // Warnings again
  // details::Tricky<int, -5> joker; // Boom, boom, boom, boom
  common::emptyLine();
}

} // namespace

void runChapter14() {
    common::printTitle("C++ Templates Chapter 14");
    lazyDemonstration();
    common::emptyLine();
}

}