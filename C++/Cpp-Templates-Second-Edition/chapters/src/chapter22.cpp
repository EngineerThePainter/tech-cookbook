#include "chapters/chapter22.hpp"

#include <iostream>

#include <bridge/forupto.hpp>

#include <common/common_prints.hpp>

namespace chapters
{
namespace
{

  void foreach1() {
    common::printTitle("Foreach 1");
    bridge::forUpTo(5, bridge::printInt);
    std::cout << std::endl;
    bridge::forUpToFunctional(5, bridge::printInt);
    std::cout << std::endl;
    common::printMessage("Custom function pointer implementation");
    bridge::forUpToFunctionPointer(5, bridge::printInt);
    std::cout << std::endl;
    common::emptyLine();
  }

} // namespace

void runChapter22()
{
  common::printTitle("C++ Templates Chapter 22");
  foreach1();
  common::emptyLine();
}
}