#ifndef SORTING_BUBBLE_SORT_HPP
#define SORTING_BUBBLE_SORT_HPP

#include "sorting_algorithm.hpp"

namespace sorting
{
class BubbleSort : public SortingAlgorithm
{
public:
  ~BubbleSort() = default;
  void Sort(std::vector<int>& array_to_sort) override;
};
} // namespace sorting

#endif