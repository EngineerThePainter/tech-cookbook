#include "demo_sorting.hpp"

#include <functional>
#include <iostream>

#include "time_tracker.hpp"

namespace sorting
{
void demo_sorting(SortingAlgorithm& algorithm)
{
  constexpr int nb_elements = 10;
  int* best_case = new int[nb_elements];
  int* worst_case = new int[nb_elements];
  for (int i = 0; i < nb_elements; ++i) {
    best_case[i] = i + 1;
    worst_case[i] = nb_elements - i;
  }
  std::function<void(int*, int)> sort = [&](int* array, int nb_elements) { algorithm.Sort(array, nb_elements); };
  std::cout << "Best Case: " << utils::runWithTimeMeasure(sort, best_case, nb_elements).count() << " milliseconds"
            << std::endl;
  std::cout << "Best case comparisons: " << algorithm.NumberOfComparisons()
            << ", assignements: " << algorithm.NumberOfAssignements() << std::endl;
  std::cout << best_case[0] << " : " << best_case[nb_elements - 1] << std::endl;
  for (int i = 0; i < nb_elements; ++i) {
    std::cout << best_case[i] << ", ";
  }
  std::cout << std::endl;

  algorithm.ResetCounters();
  std::cout << "Worst Case: " << utils::runWithTimeMeasure(sort, worst_case, nb_elements).count() << " milliseconds"
            << std::endl;
  std::cout << "Worst case comparisons: " << algorithm.NumberOfComparisons()
            << ", assignements: " << algorithm.NumberOfAssignements() << std::endl;
  std::cout << worst_case[0] << " : " << worst_case[nb_elements - 1] << std::endl;
  for (int i = 0; i < nb_elements; ++i) {
    std::cout << worst_case[i] << ", ";
  }
  std::cout << std::endl;
  delete[] best_case;
  delete[] worst_case;
}
} // namespace sorting