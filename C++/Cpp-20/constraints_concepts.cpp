#include "constraints_concepts.hpp"

#include <iostream>
#include <set>

void constraintsConcepts()
{
  std::cout << "Constraints & Concepts \n" << std::endl;

  hashableFun("ABC");

  B b;
  C c;
  derivedFun(b);
  // derivedFun(c); c does not derive from A

  std::cout << "-----\n";
}