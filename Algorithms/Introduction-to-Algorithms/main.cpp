#include <functional>
#include <iostream>

#include "chapter2/chapter2.hpp"
#include "utils/time_tracker.hpp"

int main() {
  std::cout << "Introduction to Algorithms 3rd edition" << std::endl;
  std::cout << utils::runWithTimeMeasure(chapters::test, 0, 0).count() << std::endl;
  return 0;
}