#include "chapters/chapter18.hpp"

#include <iostream>
#include <list>
#include <set>
#include <vector>

#include <common/common_prints.hpp>

#include <poly/printmax.hpp>
#include <poly/statichier.hpp>
#include <poly/staticpoly.hpp>

namespace chapters
{
namespace
{

void static_polymorphism() {
  common::printTitle("Static polymorphism demo");
  poly::Cat cat;
  poly::Dog dog1, dog2, dog3;
  poly::my_sound(cat);
  poly::my_sound(dog1);
  common::printCallFunction("poly::weight_difference(cat, dog1)", poly::weight_difference(cat, dog1));
  std::vector<poly::Dog> dogs;
  dogs.push_back(dog1);
  dogs.push_back(dog2);
  dogs.push_back(dog3);
  poly::sound_and_walk(dogs);
  common::emptyLine();
}

void generic_programming() {
  common::printTitle("Generic programming demo");
  std::vector<int> c1 {11,2,2,5,3,6,2,756,32,5435};
  std::list<int> c2 {1,2,3,4,5,6,7,8,9,10};
  std::set<int> c3;
  poly::print_max(c1);
  poly::print_max(c2);
  poly::print_max(c3);
  common::emptyLine();
}

} // namespace

void runChapter18()
{
  common::printTitle("C++ Templates Chapter 18");
  static_polymorphism();
  generic_programming();
  common::emptyLine();
}
}