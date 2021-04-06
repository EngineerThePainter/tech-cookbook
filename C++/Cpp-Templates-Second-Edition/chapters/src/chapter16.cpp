#include "chapters/chapter16.hpp"

#include <iostream>

#include <common/common_prints.hpp>
#include <details/funcoverload1.hpp>
#include <details/nontmpl1.hpp>
#include <details/nontmpl2.hpp>
#include <details/tmplconstr.hpp>

namespace chapters
{
namespace
{

void simpleFunctionOverload() {
  common::printTitle("Simple overload");
  common::printCallFunction("details::fun(5)", details::fun(5));
  common::printCallFunction("details::fun((int*)(nullptr))", details::fun((int*)(nullptr)));
  common::emptyLine();
}

void nonTemplateOverload() {
  common::printTitle("Non template overload");
  int x = 5;
  // When passing instantiated variable the prefered value is function overload
  common::printCallFunction("details::f(x)", details::f(x));
  // When passing single value the prefered value is template overload
  common::printCallFunction("details::f(5)", details::f(5));
  common::emptyLine();
  common::printMessage("When reference and const meet the difference is visible");
  int y = 10;
  const int z = 15;
  // Now the favorable overload is template
  common::printCallFunction("details::f2(y)", details::f2(y));
  // And const variable calls the function overload
  common::printCallFunction("details::f2(z)", details::f2(z));
  common::emptyLine();
}

void templateConstructor() {
  common::printTitle("Template constructor inside class");
  details::C x;
  details::C x2{x};
  details::C x3{std::move(x)};
  const details::C c;
  details::C x4{c};
  details::C x5{std::move(c)};
  common::emptyLine();
}

} // namespace

void runChapter16()
{
  common::printTitle("C++ Templates Chapter 16");
  simpleFunctionOverload();
  nonTemplateOverload();
  templateConstructor();
  common::emptyLine();
}
}