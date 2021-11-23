#include "chapters/chapter20.hpp"

#include <iostream>

#include <common/common_prints.hpp>
#include <typeoverload/advance2.hpp>
#include <typeoverload/advance3.hpp>
#include <typeoverload/container1.hpp>
#include <typeoverload/min2.hpp>

namespace chapters
{
namespace
{

struct X1 {};
bool operator< (X1 const&, X1 const&) {return true;}

struct X2 {};
bool operator< (X2, X2) {return true;}

struct X3 {};
bool operator< (X3&, X3&) {return true;}

struct X4 {};

struct BoolConvertible {
  operator bool() const {return true;}
};

struct X5 {};

BoolConvertible operator< (X5 const&, X5 const&){
  return BoolConvertible();
};

struct NotBoolConvertible {};

struct X6 {};

NotBoolConvertible operator< (X6 const&, X6 const&){
  return NotBoolConvertible();
};

struct BoolLike {
  explicit operator bool() const {return true;} // explicit conversion to bool
};

struct X7 {};
BoolLike operator< (X7 const&, X7 const&) {return BoolLike();}

void min_test() {
  common::printTitle("Less than operator trait testing with min() function");
  typeoverload::min(X1(), X1());
  typeoverload::min(X2(), X2());
  // typeoverload::min(X3(), X3()); // ERROR
  // typeoverload::min(X4(), X4()); // ERROR
  typeoverload::min(X5(), X5());
  // typeoverload::min(X6(), X6()); // ERROR
  // typeoverload::min(X7(), X7()); // UNEXPECTED ERROR
  common::emptyLine();
}
} // namespace

void runChapter20()
{
  common::printTitle("C++ Templates Chapter 20");
  common::printMessage("Parts of the functionalites are only meant to be build, so they are just included here.");
  min_test();
  common::emptyLine();
}
}