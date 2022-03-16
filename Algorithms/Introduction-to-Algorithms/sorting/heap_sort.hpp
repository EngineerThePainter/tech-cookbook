#ifndef SORTING_HEAP_SORT_HPP
#define SORTING_HEAP_SORT_HPP

#include "sorting_algorithm.hpp"

namespace sorting
{
class HeapSort : public SortingAlgorithm
{
public:
  ~HeapSort() = default;
  void Sort(std::vector<int>& array_to_sort) override;
};
} // namespace sorting

#endif