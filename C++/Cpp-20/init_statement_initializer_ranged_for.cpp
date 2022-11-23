#include "init_statement_initializer_ranged_for.hpp"

#include <iostream>
#include <vector>

void showInitStatementAndInitializerForRangedFor()
{
  std::cout << "Init statement and initializers for ranged for loop\n";
  std::vector<int> vec{1, 3, 5, 6, 9, 7, 8, 5, 4, 6, 3, 4};

  for (size_t n = vec.size(); const auto& i : vec) {
    std::cout << n-- << " : " << i << std::endl;
  }
  std::cout << "-----\n";
  for (typedef decltype(vec)::value_type elem_t; const elem_t& i : vec) {
    std::cout << i << std::endl;
  }
  std::cout << "-----\n";
}