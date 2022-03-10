#include "demo_sorting.hpp"

#include <functional>
#include <iostream>
#include <vector>

#include "time_tracker.hpp"

namespace sorting
{
void demo_sorting(SortingAlgorithm& algorithm)
{
  constexpr int nb_elements = 10000;
  std::vector<int> best_case{};
  best_case.resize(nb_elements);
  std::vector<int> worst_case{};
  worst_case.resize(nb_elements);
  for (int i = 0; i < nb_elements; ++i) {
    best_case[i] = i + 1;
    worst_case[i] = nb_elements - i;
  }
  std::function<void(std::vector<int>&)> sort = [&](std::vector<int>& array) { algorithm.Sort(array); };

  std::cout << "Best Case: " << utils::runWithTimeMeasure(sort, best_case).count() << " milliseconds"
            << std::endl;
  std::cout << "Best case comparisons: " << algorithm.NumberOfComparisons()
            << ", assignements: " << algorithm.NumberOfAssignements() << std::endl;
  std::cout << best_case[0] << " : " << best_case[nb_elements - 1] << std::endl;

  algorithm.ResetCounters();

  std::cout << "Worst Case: " << utils::runWithTimeMeasure(sort, worst_case).count() << " milliseconds"
            << std::endl;
  std::cout << "Worst case comparisons: " << algorithm.NumberOfComparisons()
            << ", assignements: " << algorithm.NumberOfAssignements() << std::endl;
  std::cout << worst_case[0] << " : " << worst_case[nb_elements - 1] << std::endl;
}
} // namespace sorting
