#ifndef SORTING_BUBBLE_SORT_HPP
#define SORTING_BUBBLE_SORT_HPP

#include "sorting_algorithm.hpp"

namespace sorting
{
class BubbleSort : public SortingAlgorithm
{
public:
  ~BubbleSort() = default;
  void Sort(int* array_to_sort, int number_of_elements) override;
};
} // namespace sorting

#endif