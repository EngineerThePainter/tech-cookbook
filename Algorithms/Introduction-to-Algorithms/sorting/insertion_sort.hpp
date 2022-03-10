#ifndef SORTING_INSERTION_SORT_HPP
#define SORTING_INSERTION_SORT_HPP

#include "sorting_algorithm.hpp"

namespace sorting
{
class InsertionSort : public SortingAlgorithm
{
public:
  ~InsertionSort() = default;
  void Sort(std::vector<int>& array_to_sort) override;
};
} // namespace sorting

#endif