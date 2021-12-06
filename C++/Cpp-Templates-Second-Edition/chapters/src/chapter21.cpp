#include "chapters/chapter21.hpp"

#include <common/common_prints.hpp>
#include <inherit/basememberpair.hpp>
#include <inherit/ebco1.hpp>
#include <inherit/equality_comparable.hpp>
#include <inherit/objectcounter.hpp>
#include <inherit/wrapper.hpp>
#include <inherit/virtual.hpp>

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

// Declaration of the foo available in the <inherit/wrapper.h>
template<typename T>
void foo(T const&);

void BartonNackmanTrick() {
  common::printTitle("Barton Nackman trick to overload functions in templates");
  inherit::WrapperExampleClass exampleClass;
  inherit::Wrapper<inherit::WrapperExampleClass> wrapper(exampleClass);
  foo(wrapper); // Wrapper<WrapperExampleClass> is friendly associated with wrapper
  // foo(exampleClass); // ERROR Wrapper<WrapperExampleClass> is not associated with exampleClass
  common::emptyLine();
}

void operatorImplementationCRTP() {
  common::printTitle("Operator Implementations");
  common::printMessage("Calling inequality operator on type which call equality which is injected over CRTP.");
  inherit::X x1(5), x2(7);
  if (x1 != x2) {
    common::printMessage("x1 and x2 are different");
  }
  common::emptyLine();
}

void virtualizationCRTP() {
  common::printTitle("Function virtualization with CRTP");
  inherit::Base<inherit::NotVirtual>* p1 = new inherit::Derived<inherit::NotVirtual>;
  p1->foo();
  delete p1;

  inherit::Base<inherit::Virtual>* p2 = new inherit::Derived<inherit::Virtual>;
  p2->foo();
  delete p2;
  common::emptyLine();
}

} // namespace

void runChapter21()
{
  common::printTitle("C++ Templates Chapter 21");
  emptyBaseClassOptimization();
  objectCounterCRTP();
  BartonNackmanTrick();
  operatorImplementationCRTP();
  virtualizationCRTP();
  common::emptyLine();
}
}