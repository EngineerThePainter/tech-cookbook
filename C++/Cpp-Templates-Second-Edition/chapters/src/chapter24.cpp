#include "chapters/chapter24.hpp"

#include <iostream>
#include <typeinfo>
#include <type_traits>

#include <common/common_prints.hpp>

#include <typelist/addconst.hpp>
#include <typelist/largesttype.hpp>
#include <typelist/nthelement.hpp>
#include <typelist/typelist.hpp>
#include <typelist/typelist_front.hpp>
#include <typelist/typelist_pop_front.hpp>
#include <typelist/typelist_push_back.hpp>
#include <typelist/typelist_push_front.hpp>
#include <typelist/typelist_reverse.hpp>
#include <typelist/transform.hpp>

namespace chapters
{
namespace
{

template<typename T>
void printType(const std::string& message = "") {
  T x;
  if (!message.empty()) {
    std::cout << message << ": ";
  }
  std::cout << typeid(x).name() << std::endl;
}

} // namespace

void runChapter24()
{
  common::printTitle("C++ Templates Chapter 24");
  using SignedIntegralTypes = typelist::TypeList<signed char, short, int, long, long long>;
  printType<SignedIntegralTypes>("SignedIntegralTypes");
  
  using FrontSignedIntegralTypes = typelist::Front<SignedIntegralTypes>;
  printType<FrontSignedIntegralTypes>("Front");

  using PopFrontSignedIntegralTypes = typelist::PopFront<SignedIntegralTypes>;
  printType<PopFrontSignedIntegralTypes>("PopFront");

  using PushFrontSignedIntegralTypes = typelist::PushFront<SignedIntegralTypes, bool>;
  printType<PushFrontSignedIntegralTypes>("PushFront");

  printType<typelist::NthElement<SignedIntegralTypes, 3>>("3rd element");
  printType<typelist::NthElement<SignedIntegralTypes, 1>>("1st element");

  printType<typelist::LargestType<SignedIntegralTypes>>("LargestType SignedIntegralTypes");
  printType<typelist::LargestType<typelist::TypeList<>>>("LargestType Empty");

  using PushBackSignedIntegralTypes = typelist::PushBack<SignedIntegralTypes, bool>;
  printType<PushBackSignedIntegralTypes>("PushBack");

  using ReverseSignedIntegralTypes = typelist::Reverse<SignedIntegralTypes>;
  printType<ReverseSignedIntegralTypes>("Reverse");

  using TranformedToConstSignedIntegralTypes = typelist::Transform<SignedIntegralTypes, typelist::AddConstT>;
  printType<TranformedToConstSignedIntegralTypes>("Const Transform");

  common::emptyLine();
}
}