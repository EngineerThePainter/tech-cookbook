#include "demo_sorting.hpp"

#include <functional>
#include <iostream>

#include "time_tracker.hpp"

namespace sorting
{
void demo_sorting(SortingAlgorithm& algorithm)
{
  constexpr int nb_elements = 10000;
  int* best_case = new int[nb_elements];
  int* worst_case = new int[nb_elements];
  for (int i = 0; i < nb_elements; ++i) {
    best_case[i] = i;
    worst_case[i] = nb_elements - i;
  }
  std::function<void(int*, int)> sort = [&](int* array, int nb_elements) { algorithm.Sort(array, nb_elements); };
  std::cout << "Best Case: " << utils::runWithTimeMeasure(sort, best_case, nb_elements).count() << " microseconds"
            << std::endl;
  std::cout << "Best case comparisons: " << algorithm.NumberOfComparisons() << ", moves: " << algorithm.NumberOfMoves()
            << std::endl;

  algorithm.ResetCounters();
  std::cout << "Worst Case: " << utils::runWithTimeMeasure(sort, worst_case, nb_elements).count() << " microseconds"
            << std::endl;
  std::cout << "Worst case comparisons: " << algorithm.NumberOfComparisons() << ", moves: " << algorithm.NumberOfMoves()
            << std::endl;

  delete[] best_case;
  delete[] worst_case;
}
} // namespace sorting