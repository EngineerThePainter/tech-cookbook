#include "consteval_and_constinit.hpp"

#include <iostream>

namespace
{
constexpr unsigned int factorial(unsigned int n) { return n < 2 ? 1 : n * factorial(n - 1); }

consteval unsigned int multiple_factorials(unsigned int m, unsigned int n) { return factorial(m) / factorial(n); }

constinit const unsigned int x = factorial(5);
} // namespace

void constevalAndConstinit()
{
  std::cout << "Consteval and constinit\n";
  std::cout << "Consteval factorials: " << multiple_factorials(10, 5) << std::endl;
  std::cout << "Constinit factorial: " << x << std::endl;
}