#include "sorting_algorithm.hpp"

#include <iostream>

#include "utils/time_tracker.hpp"

namespace sorting_algorithm
{
void SortingAlgorithm::Demo()
{
  constexpr int nb_elements = 1000000;
  int* best_case = new int[nb_elements];
  int* worst_case = new int[nb_elements];
  for (int i = 0; i < nb_elements; ++i) {
    best_case[i] = i;
    worst_case[i] = nb_elements - i;
  }

  std::cout << "Best Case: " << utils::runWithTimeMeasure(SortingAlgorithm::Sort, best_case, nb_elements).count()
            << std::endl;
  std::cout << "Best case comparisons: " << number_of_comparisons_ << ", moves: " << number_of_moves_ << std::endl;

  number_of_comparisons_ = 0;
  number_of_moves_ = 0;
  std::cout << "Worst Case: " << utils::runWithTimeMeasure(SortingAlgorithm::Sort, worst_case, nb_elements).count()
            << std::endl;
  std::cout << "Worst case comparisons: " << number_of_comparisons_ << ", moves: " << number_of_moves_ << std::endl;

  delete[] best_case;
  delete[] worst_case;
}
} // namespace sorting_algorithm