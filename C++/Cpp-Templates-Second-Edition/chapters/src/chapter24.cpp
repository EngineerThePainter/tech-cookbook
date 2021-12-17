#include "chapters/chapter24.hpp"

#include <typeinfo>

#include <common/common_prints.hpp>

#include <typelist/typelist.hpp>
#include <typelist/typelist_front.hpp>
#include <typelist/typelist_pop_front.hpp>
#include <typelist/typelist_push_front.hpp>

namespace chapters
{
namespace
{

template<typename T>
void printType() {
  T x;
  common::printMessage(typeid(x).name());
}

} // namespace

void runChapter24()
{
  common::printTitle("C++ Templates Chapter 24");
  using SignedIntegralTypes = typelist::TypeList<signed char, short, int, long, long long>;
  printType<SignedIntegralTypes>();
  
  using FrontSignedIntegralTypes = typelist::Front<SignedIntegralTypes>;
  printType<FrontSignedIntegralTypes>();

  using PopFrontSignedIntegralTypes = typelist::PopFront<SignedIntegralTypes>;
  printType<PopFrontSignedIntegralTypes>();

  using PushFrontSignedIntegralTypes = typelist::PushFront<SignedIntegralTypes, bool>;
  printType<PushFrontSignedIntegralTypes>();

  common::emptyLine();
}
}