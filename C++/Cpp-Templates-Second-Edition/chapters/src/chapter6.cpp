#include "chapters/chapter6.hpp"

#include <iostream>
#include <string>

#include <basics/move.hpp>

#include <common/common_prints.hpp>

namespace chapters {

namespace {

void perfectForwarding() {
  common::printTitle("Perfect forwarding");
  basics::X v;
  basics::X const c;

  basics::f(v);
  basics::f(c);
  basics::f(basics::X());
  basics::f(std::move(v));
  common::emptyLine();
}

} // namespace

void runChapter6() {
  perfectForwarding();
}

}