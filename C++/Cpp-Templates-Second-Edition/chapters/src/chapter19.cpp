#include "chapters/chapter19.hpp"

#include <iostream>

#include <common/common_prints.hpp>
#include <traits/accum1.hpp>
#include <traits/accum2.hpp>
#include <traits/accum3.hpp>
// There is no accum4 since there is showing some custom class that I don't want to work on it
#include <traits/accum5.hpp>

namespace chapters
{
namespace
{

void accumulationNoTrait() {
  common::printTitle("Accumulation without trait");
  int num[] = {1, 2, 3, 4, 5, 6, 7};
  std::cout << "The average value of the integer values is " << traits::accum(num, num+7)/7 << std::endl;
  char name[] = "templates";
  int length = sizeof(name)-1;

  // Try to print average character value
  std::cout << "The average value of the \"templates\" is " << traits::accum(name, name+length)/length << std::endl;
  common::emptyLine();
}

void accumulationTrait() {
  common::printTitle("Accumulation with trait");
  int num[] = {1, 2, 3, 4, 5, 6, 7};
  std::cout << "The average value of the integer values is " << traits::accum2(num, num+7)/7 << std::endl;

  char name[] = "templates";
  int length = sizeof(name)-1;

  // Try to print average character value
  std::cout << "The average value of the \"templates\" is " << traits::accum2(name, name+length)/length << std::endl;
  // There should be a trait for the char character as default instantiation for char
  common::emptyLine();
}

void accumulationTraitWithValue() {
  common::printTitle("Accumulation with trait for value");
  int num[] = {1, 2, 3, 4, 5, 6, 7};
  std::cout << "The average value of the integer values is " << traits::accum3(num, num+7)/7 << std::endl;

  char name[] = "templates";
  int length = sizeof(name)-1;

  // Try to print average character value
  std::cout << "The average value of the \"templates\" is " << traits::accum3(name, name+length)/length << std::endl;
  // There should be a trait for the char character as default instantiation for char
  common::emptyLine();
}

void accumulationTraitWithParameter() {
  common::printTitle("Accumulation with trait with parameter");
  int num[] = {1, 2, 3, 4, 5, 6, 7};
  std::cout << "The average value of the integer values is " << traits::accum3(num, num+7)/7 << std::endl;

  char name[] = "templates";
  int length = sizeof(name)-1;

  // Try to print average character value
  std::cout << "The average value of the \"templates\" is " << traits::accum3(name, name+length)/length << std::endl;
  // There should be a trait for the char character as default instantiation for char
  common::emptyLine();
}

} // namespace

void runChapter19()
{
  common::printTitle("C++ Templates Chapter 19");
  accumulationNoTrait();
  accumulationTrait();
  accumulationTraitWithValue();
  accumulationTraitWithParameter();
  common::emptyLine();
}
}