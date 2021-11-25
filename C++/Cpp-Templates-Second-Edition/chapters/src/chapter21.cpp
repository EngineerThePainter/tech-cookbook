#include "chapters/chapter21.hpp"

#include <common/common_prints.hpp>
#include <inherit/basememberpair.hpp>
#include <inherit/ebco1.hpp>
#include <inherit/objectcounter.hpp>

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

void objectCounterCRTP() {
  common::printTitle("CRTP Object counter demonstration");
  inherit::CustomNumber<int> cni(25), cni2(52);
  inherit::CustomNumber<double> cnd(46.5);
  common::printCallFunction("inherit::CustomNumber<int>::live()", inherit::CustomNumber<int>::live());
  common::printCallFunction("inherit::CustomNumber<double>::live()", inherit::CustomNumber<double>::live());
  common::emptyLine();
}

} // namespace

void runChapter21()
{
  common::printTitle("C++ Templates Chapter 21");
  emptyBaseClassOptimization();
  objectCounterCRTP();
  common::emptyLine();
}
}