#include "three_way_comparison.hpp"

#include <iostream>

namespace
{
void useIt(int a, int b)
{
  auto result = a <=> b;
  if (result < 0) {
    std::cout << "a lesser than b" << std::endl;
  }
  if (result > 0) {
    std::cout << "a bigger than b" << std::endl;
  }
  if (result == 0) {
    std::cout << "a equal b" << std::endl;
  }
}
} // namespace

void showThreeWayComparison()
{
  std::cout << "Three way comparison\n";
  useIt(5, 10);
  useIt(10, 5);
  useIt(10, 10);
}