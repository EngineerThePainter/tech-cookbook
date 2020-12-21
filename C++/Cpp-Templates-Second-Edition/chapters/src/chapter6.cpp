#include "chapters/chapter6.hpp"

#include <iostream>
#include <string>

#include <basics/move.hpp>
#include <basics/specialMemTempl.hpp>

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

void specialMemberFunctionTemplates() {
  common::printTitle("Special Member Function Templates");
  std::string s = "s meaning name";
  basics::Person p1(s);
  basics::Person p2("tmp");
  basics::Person p3(p1);
  basics::Person p4(std::move(p1));

  basics::Person2 p21(s);
  basics::Person2 p22("tmp");
  const basics::Person2 p23("ctmp");
  basics::Person2 p24(p23);
  /* The following approaches will not work, due to fact that predefined template is better than
     implemented copy and move constructor. This will not be the case if passed Person object will be const. */
  // basics::Person2 r3(r1);
  // basics::Person2 r4(std::move(r1));

  common::emptyLine();
}

} // namespace

void runChapter6() {
  perfectForwarding();
  specialMemberFunctionTemplates();
}

}