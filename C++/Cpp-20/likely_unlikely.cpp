#include "likely_unlikely.hpp"

#include <chrono>
#include <iostream>
#include <random>
#include <vector>

namespace
{

int getRandomInt()
{
  static std::random_device rd;
  static std::mt19937 gen(rd());
  static std::uniform_int_distribution<int> dis(0, 100);
  return dis(gen);
}

void funWithoutAttributes(int value)
{
  if (value % 6 == 0) {
    ++value;
  } else {
    value += 2;
  }
}

void funWithAttributes(int value)
{
  if (value % 6 == 0) [[unlikely]] {
    ++value;
  } else [[likely]] {
    value += 2;
  }
}

} // namespace

void likely_unlikely()
{
  std::cout << "Likely unlikely\n";

  auto benchmark = [](auto fun) {
    const auto start = std::chrono::high_resolution_clock::now();
    for (auto size{1ULL}; size != 10'000'000ULL; ++size) {
      fun(getRandomInt());
    }
    const std::chrono::duration<double> diff = std::chrono::high_resolution_clock::now() - start;
    std::cout << "Time: " << std::fixed << std::setprecision(6) << diff.count() << std::endl;
  };

  benchmark(funWithoutAttributes);
  benchmark(funWithAttributes);
}