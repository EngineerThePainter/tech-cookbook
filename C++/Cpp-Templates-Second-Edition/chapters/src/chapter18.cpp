#include "chapters/chapter18.hpp"

#include <iostream>
#include <vector>

#include <common/common_prints.hpp>

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

} // namespace

void runChapter18()
{
  common::printTitle("C++ Templates Chapter 18");
  static_polymorphism();
  common::emptyLine();
}
}