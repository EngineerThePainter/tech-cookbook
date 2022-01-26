#ifndef SORTING_INSERTION_SORT_HPP
#define SORTING_INSERTION_SORT_HPP

#include "sorting_algorithm.hpp"

namespace sorting
{
class InsertionSort : public SortingAlgorithm
{
public:
  ~InsertionSort() = default;
  void Sort(int* array_to_sort, int number_of_elements) override;
};
} // namespace sorting

#endif