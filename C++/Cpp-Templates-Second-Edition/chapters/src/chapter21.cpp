#include "chapters/chapter21.hpp"

#include <common/common_prints.hpp>
#include <inherit/basememberpair.hpp>
#include <inherit/ebco1.hpp>

namespace chapters
{
namespace
{

void emptyBaseClassOptimization() {
  common::printTitle("Empty Base Class Optimization example - three classes inheriting one by one");
  common::printCallFunction("sizeof(Empty)", sizeof(inherit::Empty));
  common::printCallFunction("sizeof(EmptyToo)", sizeof(inherit::EmptyToo));
  common::printCallFunction("sizeof(EmptyThree)", sizeof(inherit::EmptyThree));
  common::printCallFunction("sizeof(NonEmpty)", sizeof(inherit::NonEmpty));
  common::emptyLine();
}

//Demo Base member pair

} // namespace

void runChapter21()
{
  common::printTitle("C++ Templates Chapter 21");
  emptyBaseClassOptimization();
  common::emptyLine();
}
}