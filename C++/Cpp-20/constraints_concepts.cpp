#include "constraints_concepts.hpp"

#include <iostream>
#include <set>

void constraintsConcepts()
{
  std::cout << "Constraints & Concepts \n" << std::endl;

  std::set<int> setOfInt{1, 2, 3, 4, 5};
  hashableFun(setOfInt);
  hashableFun("ABC");

  std::cout << "-----\n";
}